#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange be;

	// std::cout << std::fixed << std::setprecision(2) << "StockRate: " << lol << std::endl;
	try
	{
		be.readDataCSV("data.csv");
		be.convertInputList("input.txt");
	}
	catch (const std::exception &e){std::cout << "Error: " << e.what() << std::endl;}
	return (0);
}
