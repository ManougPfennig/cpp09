#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange( void ) {}
BitcoinExchange::BitcoinExchange( void ) {}
BitcoinExchange::BitcoinExchange( const BitcoinExchange &be ): _csv(be._csv) {}

BitcoinExchange	&BitcoinExchange::operator=( const BitcoinExchange &be) {

	this->_csv = be._csv;
	return (*this);
}

std::string	BitcoinExchange::keepDate( const std::string line ) const{

	return(line.substr(0, 10));
}

double	BitcoinExchange::keepStockRate( const std::string line ) const{

	std::string rateStr;
	rateStr = line.substr(11);

	return ((atof(rateStr.c_str())));
}

void	BitcoinExchange::storeDataCSV( const std::string inputFile ){

	std::string		line;
    std::ifstream	file(inputFile);
	std::string		date;
	double			rate = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
			if (CSVLineIsUsable(line) == true)
			{
				date = keepDate(line);
				rate = keepStockRate(line);
				_csv.insert(std::make_pair(date, rate));
			}
			std::cout << "from: " << line << " date: " << keepDate(line) << " - rate: " << keepStockRate(line) << std::endl;
        }
        file.close();
    }
	return ;
}

bool		BitcoinExchange::CSVLineIsUsable( const std::string line ) const{

	// std::string rateStr;
	// rateStr = line.substr(11);

	// double temp = atof(line.c_str());
	// if (temp > FLT_MAX || temp < -FLT_MAX)
	// 	throw (BitcoinExchange::UnvalidFormatException());
//	return (static_cast<float>(atof(literal.c_str())));
	return (true);
}