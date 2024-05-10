#include "RPN.hpp"

RPN::~RPN( void ) {}

RPN::RPN( void ) {}

RPN::RPN( const RPN &r ): _pile(r._pile) {}

RPN	&RPN::operator=( const RPN &r ) {
	_pile = r._pile;
	return (*this);
}

int		RPN::isOperator( const int op ){

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
	// No operator found
	return (0);
}

bool	RPN::isValidExpression( const std::string exp ){

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

bool	RPN::getExpressionError( const std::string exp ){

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
		// Checks if the two first expressions are operands
		if (pos <= 2 && !isdigit(exp[i]))
			throw (RPN::ImpossibleCalculationException());
		// Checks if there are only operands or operators and count them
		if (isdigit(exp[i]) && ++operands)
			last = OPERAND;
		else if (isOperator(exp[i]) && ++operators)
			last = OPERATOR;
		else
			throw (RPN::UnvalidCharacterException());
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
		throw (RPN::ImpossibleCalculationException);
	return (false);
}




