#include "RPN.hpp"

int	displayTutorial( void ){

	// Definition of the Reverse Polish Notation
	std::cout << YELLOW << "Definition:" << std::endl;
	std::cout << GREEN << "Reverse Polish Notation (RPN)" << WHITE << ", also known as postfixed notation,\n\
allows arithmetic formulas to be written unambiguously without the use of parentheses.\n";
	std::cout << WHITE << "In reverse Polish notation, the operators follow their operands.\n\n\
For example, to add 3 and 4 together, the expression is 3 4 + rather than 3 + 4.\n\
The conventional notation expression 3 - 4 + 5 becomes 3 4 - 5 + in reverse Polish notation:\n\
4 is first subtracted from 3, then 5 is added to it.\n" << RESET << std::endl;

	// Definition of the Shunting-Yard algorithm
	std::cout << YELLOW << "Shunting-Yard algorithm:" << std::endl;
	std::cout << WHITE << "The " << GREEN << "Shunting-Yard algorithm" << WHITE << ", is a method for parsing arithmetical or logical expressions,\n\
or a combination of both, specified in infix notation to produce a postfix notation string,\n\
also known as Reverse Polish notation (RPN).\n";
	std::cout << WHITE << "An expression such as 2 + 3 * 8 would be converted to 3 8 * 2 +\n" << RESET << std::endl;

	// More info about launch
	std::cout << YELLOW << "Starting " << GREEN << "RPN" << WHITE ":" << std::endl;
	std::cout << YELLOW << "- With a postfix expression will operate it and display the result." << std::endl;
	std::cout << YELLOW << "- With the " << BLUE << "convert" << YELLOW << " keyword will display a prompt to enter an infix expression" << std::endl;
	std::cout << YELLOW << "that will be converted to a postfix expression using the " << GREEN << "Shunting-Yard Algorithm" << YELLOW << "." << RESET << std::endl;

	return (1);
}

void	displayMenu( void ){

	// Display infos about launch
	std::cout << YELLOW << "Start " << GREEN << "RPN" << YELLOW << " with:" << RESET << std::endl;
	std::cout << YELLOW << "- keyword " << BLUE << "tutorial" << YELLOW << " for a quick explanation." << RESET << std::endl;
	std::cout << YELLOW << "- keyword " << BLUE << "convert" << YELLOW << " to try Shunting-yard algorithm." << RESET << std::endl;
	std::cout << YELLOW << "Or an expression in " << GREEN << "Reverse Polish Notation" << YELLOW << " to operate." << RESET << std::endl;
	return ;
}

int main(int ac, char **av)
{
	system("clear");
	if (ac == 2)
	{
		std::string	entry(av[1]);
		if (entry == "tutorial")
			displayTutorial();
		else if (entry == "convert")
			RPN::shuntingYard();
		else
		{
			try
			{
				RPN a;
				a.getExpressionError(av[1]);
				a.storeExpression(av[1]);
				std::cout << GREEN << "Result: " << WHITE << a.calculateRPN() << RESET << std::endl;
			}
			catch(const std::exception& e) {std::cout << RED << "Error: " << WHITE << e.what() << RESET << std::endl;}
		}
	}
	else if (ac == 1)
		displayMenu();
	else
		std::cout << YELLOW << "Start " << GREEN << "RPN" << YELLOW << " with a valid expression as first and only argument." << RESET << std::endl;
	return (0);
}