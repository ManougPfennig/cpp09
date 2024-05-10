#include "RPN.hpp"

int main(int ac, char **av)
{
	std::cout << RPN::isValidExpression(av[1]) << std::endl;
	return (0);
}