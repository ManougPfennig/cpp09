#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange	be;

	be.storeDataCSV(av[1]);
	return 0;
}