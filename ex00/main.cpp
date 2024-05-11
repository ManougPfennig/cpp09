#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange be;

	// std::cout << std::fixed << std::setprecision(2) << "StockRate: " << lol << std::endl;
	if (ac == 2)
	{
		try
		{
			be.readDataCSV("data.csv");
			be.convertInputList(av[1]);
		}
		catch (const std::exception &e){std::cout << RED << "Error: " << WHITE << e.what() << std::endl;}
	}
	else
		std::cout << RED << "Error: " << WHITE <<"Start BitcoinExchange with the input file as single argument." << RESET << std::endl;
	return (0);
}
