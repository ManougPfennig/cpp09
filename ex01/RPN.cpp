#include "RPN.hpp"

RPN::~RPN( void ) {}

RPN::RPN( void ) {}

RPN::RPN( const RPN &r ): _pile(r._pile) {}

RPN	&RPN::operator=( const RPN &r ) {
	_pile = r._pile;
	return (*this);
}

std::stack<std::string> &RPN::getPile( void ){

	return (_pile);
}

void		RPN::reverse( std::stack<std::string> &pile ){

	// Copies pile.
	std::stack<std::string> cpy = pile;
	// Empties pile.
	while (pile.size() != 0)
		pile.pop();
	// Recopies all elements in the reverse order.
	while (cpy.size())
	{
		pile.push(cpy.top());
		cpy.pop();
	}
	return ;
}

std::string	RPN::pileToStr( void ) const{

	std::string				ret;
	std::stack<std::string> cpy = _pile;

	while (cpy.size())
	{
		ret = cpy.top() + ret;
		cpy.pop();
		if (cpy.size())
			ret = " " + ret;
	}
	return (ret);
}

int			RPN::isOperator( const int op ){

	int i = 0;
	int	_operator[4] = {'+', '-', '/', '*'};
	while (i < 4 && op != _operator[i])
		i++;
	switch (i)
	{
		// is [+]
		case 0:
			return (1);
		// is [-]
		case 1:
			return (2);
		// is [/]
		case 2:
			return (3);
		// is [*]
		case 3:
			return (4);
	}
	// No operator type found
	return (0);
}

bool		RPN::isValidExpression( const std::string exp ){

	if (!exp.length())
		return (false);
	int	i = 0;
	int	pos = 0;
	int	last = 0;
	int	operators = 0;
	int	operands = 0;
	while (exp[i])
	{
		// Skips spaces
		while(exp[i] == ' ')
			i++;
		// Exits the loop if at the end of string
		if (!exp[i])
			break;
		pos++;
		// Checks if the two first expressions are operands
		if (pos <= 2 && !isdigit(exp[i]))
			return (false);
		// Checks if there are only operands or operators and count them
		if (isdigit(exp[i]) && ++operands)
			last = OPERAND;
		else if (isOperator(exp[i]) && ++operators)
			last = OPERATOR;
		else
			return (false);
		// Checks if expressions are only one character long
		if (exp[i + 1] && exp[i + 1] != ' ')
			return (false);
		// Checks if the calculation will be possible
		if (operators == operands)
			return (false);
		i++;
	}
	// Checks if the last expression is an operator
	if (last != OPERATOR)
		return (false);
	// Checks if there are exactly one less operators than operands
	if (operators != operands - 1)
		return (false);
	return (true);
}

bool		RPN::getExpressionError( const std::string exp ){

	if (!exp.length())
		throw (RPN::EmptyExpressionException());
	int	i = 0;
	int	pos = 0;
	int	last = 0;
	int	operators = 0;
	int	operands = 0;
	while (exp[i])
	{
		// Skips spaces
		while(exp[i] == ' ')
			i++;
		// Exits the loop if at the end of string
		if (!exp[i])
			break;
		pos++;
		// Checks if there are only operands or operators and count them
		if (isdigit(exp[i]) && ++operands)
			last = OPERAND;
		else if (isOperator(exp[i]) && ++operators)
			last = OPERATOR;
		else
			throw (RPN::UnvalidCharacterException());
		// Checks if the two first expressions are operands
		if (pos <= 2 && !isdigit(exp[i]))
			throw (RPN::ImpossibleCalculationException());
		// Checks if expressions are only one character long
		if (exp[i + 1] && exp[i + 1] != ' ')
			throw (RPN::ConnectedExpressionException());
		// Checks if the calculation will be possible
		if (operators == operands)
			throw (RPN::ImpossibleCalculationException());
		i++;
	}
	// Checks if the last expression is an operator
	if (last != OPERATOR)
		throw (RPN::ImpossibleCalculationException());
	// Checks if there are exactly one less operators than operands
	if (operators != operands - 1)
		throw (RPN::ImpossibleCalculationException());
	return (false);
}

void		RPN::storeExpression( const std::string exp, std::stack<std::string> &pile ){

	// Empties _pile before storing new elements.
	while(pile.empty() == false)
		pile.pop();
	// Find elements and store them in reverse order for easier RPN calculation.
	for (int i = exp.length() - 1; i >= 0; i--)
	{
		if (exp[i] != ' ')
			pile.push(exp.substr(i, 1));
	}
	return ;
}

long double	RPN::operate( const std::string x, const std::string y, const std::string sign) const{

	// Checks if sign is a valid expression.
	if (sign.length() != 1 || !RPN::isOperator(sign[0]))
		throw (RPN::OperateErrorException());

	// Convert each values to long double for precision.
	long double	db_x = atof(x.c_str());
	long double	db_y = atof(y.c_str());

	// Finds the operator type and returns the result.
	switch (RPN::isOperator(sign[0]))
	{
		case 1:
			return (db_x + db_y);
		case 2:
			return (db_x - db_y);
		case 3:
			return (db_x / db_y);
		case 4:
			return (db_x * db_y);
	}
	// This case cannot happen but compilation sends a warning otherwise :]
	throw (RPN::OperateErrorException());
}

long double	RPN::calculateRPN( void ){

	// Checks if the pile has at least three elements to start calculation.
	if (_pile.size() < 3)
		throw (RPN::InvalidPileException());

	std::stack<std::string> tmp;
	std::string				x;
	std::string				y;
	std::string				sign;
	// Will keep operating as long as the pile has expressions.
	while(_pile.size() != 1)
	{
		while (!isOperator(_pile.top()[0]))
		{
			tmp.push(_pile.top());
			_pile.pop();
		}
		// Store the sign and the X and Y value for operating
		sign = _pile.top();
		_pile.pop();
		y = tmp.top();
		tmp.pop();
		x = tmp.top();
		tmp.pop();
		_pile.push(lDoubletoStr(operate(x, y, sign)));
	}
	// Returns the last converted value.
	return (atof(_pile.top().c_str()));
}

std::string	RPN::lDoubletoStr( long double ld ){

	std::stringstream ss;
    ss << std::setprecision(std::numeric_limits<long double>::digits10 + 1); // Set precision
	ss << ld;
    std::string result = ss.str();
	return (result);
}

std::string	RPN::getInfixInput( void ){

	std::string	input;
	while (1)
	{
		std::cout << YELLOW << "Enter infix expression: " << RESET;
		input.clear();
		std::getline(std::cin, input);
		// Checks if stdin has been closed and returns empty input (error)
		if (feof(stdin) != 0)
		{
			std::cout << RED << "Closed stdin: Exiting" << RESET << std::endl;
			return ("");
		}
		// Doesn't check entry if it is empty
		if (input.length() == 0)
			continue;
		// Checks if the entry is a valid input
		if (!RPN::isValidInfix(input))
			std::cout << YELLOW << "Unvalid entry." << RESET << std::endl;
		else
			break;
	}
	return (input);
}

// Function to get the precedence of an operator
int	getPrecedence(char op) {

	if (op == '+' || op == '-')
		return (1);
	if (op == '*' || op == '/')
		return (2);
	return (0);
}

// void		RPN::shuntingYard( void ){

// 	// Get user entry for converting
// 	std::string input = getInfixInput();
// 	// Checks for stdin error
// 	if (!input.length())
// 		return ;
// 	// Operators temporary pile
// 	std::stack<std::string> opeStack;
// 	// Primary expression pile
// 	std::stack<std::string> inStack;
// 	// Result expression pile
// 	RPN						outStack;

// 	// Transform the entry string to elements in a pile
// 	RPN::storeExpression(input, inStack);

// 	// Repeats sorting until two elements are left in the pile
// 	while (inStack.size() > 2)
// 	{
// 		if (isdigit(inStack.top()[0]))
// 		{
// 			// Put all operands elements in outStack
// 			outStack.getPile().push(inStack.top());
// 			inStack.pop();
// 		}
// 		else if (isOperator(inStack.top()[0]))
// 		{
// 			// Put all operator elements in opeStack
// 			opeStack.push(inStack.top());
// 			inStack.pop();
// 		}
// 	}
// 	// Moves all operators form their pile to the outStack
// 	while (opeStack.size())
// 	{
// 		outStack.getPile().push(opeStack.top());
// 		opeStack.pop();
// 	}
// 	// Moves the last operator the operator pile
// 	opeStack.push(inStack.top());
// 	inStack.pop();
// 	// Moves the last operand to the outStack
// 	outStack.getPile().push(inStack.top());
// 	inStack.pop();
// 	// Moves the last operator from the operator pile to outStack
// 	outStack.getPile().push(opeStack.top());
// 	opeStack.pop();
// 	std::cout << BLUE << "Converted expression: " << WHITE << outStack.pileToStr() << std::endl;
// 	// Reverse elements order so they can be used in calculateRPN()
// 	RPN::reverse(outStack.getPile());
// 	std::cout << GREEN << "Result: " << WHITE << outStack.calculateRPN() << RESET << std::endl;
// 	return ;
// }

void		RPN::shuntingYard( void ){

	// Get user entry for converting
	std::string input = getInfixInput();
	// Checks for stdin error
	if (!input.length())
		return ;
	// Operators temporary pile
	std::stack<std::string> opeStack;
	// Primary expression pile
	std::stack<std::string> inStack;
	// Result expression pile
	RPN						outStack;

	// Transform the entry string to elements in a pile
	RPN::storeExpression(input, inStack);

	// Shunting-Yard algorithm
	while (inStack.size())
	{
		if (isdigit(inStack.top()[0]))
		{
			// Pop operands to outStack
			outStack.getPile().push(inStack.top());
			inStack.pop();
		}
		else if (isOperator(inStack.top()[0]))
		{
			// Store operators on opeStack and pop them to inStack depending on their precedence
			while (!opeStack.empty() && getPrecedence(opeStack.top()[0]) >= getPrecedence(inStack.top()[0]))
			{
				outStack.getPile().push(opeStack.top());
				opeStack.pop();
			}
			opeStack.push(inStack.top());
			inStack.pop();
		}
	}

	// Pop remaining operators from stack to postfix
	while (!opeStack.empty()) 
	{
		outStack.getPile().push(opeStack.top());
		opeStack.pop();
	}
	std::cout << BLUE << "Converted expression: " << WHITE << outStack.pileToStr() << std::endl;
	// Reverse elements order so they can be used in calculateRPN()
	RPN::reverse(outStack.getPile());
	std::cout << GREEN << "Result: " << WHITE << outStack.calculateRPN() << RESET << std::endl;
	return ;
}


int			RPN::isValidInfix( const std::string exp ){

	if (!exp.length())
		return (false);
	int	i = 0;
	int	last = 0;
	int	pos = 0;
	while (exp[i])
	{
		// Skips spaces
		while(exp[i] == ' ')
			i++;
		// Exits the loop if at the end of string
		if (!exp[i])
			break;
		pos++;
		// Checks if there aren't two expressions of the same type in a row
		if (pos > 1)
		{
			if (isdigit(exp[i]) && last == OPERAND)
				return (false);
			if (isOperator(exp[i]) && last == OPERATOR)
				return (false);
		}
		// Checks if there are only operands or operators
		if (isdigit(exp[i]))
			last = OPERAND;
		else if (isOperator(exp[i]))
			last = OPERATOR;
		else
			return (false);
		// Checks if expressions are only one character long
		if (exp[i + 1] && exp[i + 1] != ' ')
			return (false);
		i++;
	}
	// Checks if the last expression is an operand
	if (last != OPERAND)
		return (false);
	// Checks if there is minimum of 3 expressions
	if (pos < 3)
		return (false);
	return (true);
}



