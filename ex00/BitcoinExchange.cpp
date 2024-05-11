#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange( void ) {}
BitcoinExchange::BitcoinExchange( void ):  _askUserEntry(false) {}
BitcoinExchange::BitcoinExchange( const BitcoinExchange &be ): _csv(be._csv), _askUserEntry(false) {}

BitcoinExchange	&BitcoinExchange::operator=( const BitcoinExchange &be) {

	this->_csv = be._csv;
	return (*this);
}

std::string	BitcoinExchange::keepDate( const std::string line ) const{

	return(line.substr(0, 10));
}

std::string	BitcoinExchange::keepStockRate( const std::string line ) const{

	return (line.substr(11));
}

double	BitcoinExchange::strToFloat( std::string str) const{
    
	double		value;

	value = atof(str.c_str());
	return (value);
}

bool	BitcoinExchange::isFloatFormat( const std::string str) const{

	if (!str.length())
		return (false);
	
	int i = 0;
	if (!isdigit(str[i]))
		return (false);

	while (isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	if (str[i] != '.')
		return (false);
	i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!isdigit(str[i]))
			break;
		i++;
	}
	while (str[i])
	{
		if (!iswspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	BitcoinExchange::readDataCSV( const std::string inputFile ){

	std::ifstream	file(inputFile);
	std::string		line;
	size_t			lineNb = 0;

	if (file.is_open()) {
		while (getline(file, line))
		{
			lineNb++;
			// Check if there is a header for the first line
			if (lineNb == 1 && line != "date,exchange_rate")
				std::cout << MAGENTA << "CSV Note: " << CYAN << "no header in CSV file" << RESET << std::endl;
			else if (lineNb == 1)
				continue;
			try
			{
				// If the line is in the correct format, it's date and value will be added to _csv
				// Otherwise, an appropriate error message will be displayed
				CSVLineIsUsable(line);
				Date	date(keepDate(line));
				double	val = strToFloat(keepStockRate(line));
				_csv.insert(std::make_pair(date, val));
			}
			catch (const std::exception &e)
			{
				std::cout << BLUE << "CSV Error: "<< CYAN <<"line " << lineNb << BLUE << ": " << WHITE << e.what() << RESET << std::endl;
			}
        }
        file.close();
    }
	else
		throw(BitcoinExchange::CsvFileErrorException());
	return ;
}

bool	BitcoinExchange::CSVLineIsUsable( const std::string line ) const{

	if (line.length() == 0)
		throw(BitcoinExchange::EmptyLineException());
	std::string date = line.substr(0, 10);
	Date lineDate(date);
	if (!lineDate.isValidDate())
		throw (Date::NonExistantDateException());
	Date CreationDate("2009-01-03");
	if (lineDate < CreationDate)
		throw(BitcoinExchange::ImpossibleDateException());
	if (line[10] != ',')
		throw (BitcoinExchange::UnvalidValueFormatException());
	std::string valStr = line.substr(11);
	if (valStr[0] == '-' && isdigit(valStr[1]))
		throw (BitcoinExchange::NegativeValueException());
	if (!isFloatFormat(valStr))
		throw (BitcoinExchange::UnvalidValueFormatException());
	double val = atof(valStr.c_str());
	if (val > FLT_MAX || val < -FLT_MAX)
		throw (BitcoinExchange::UnvalidValueSizeException());
	return (true);
}

double	BitcoinExchange::getStockRate( const std::string date ) const{

	Date	d(date);

	std::map<Date, double>::const_iterator it = _csv.find(d);
	if (it != _csv.end())
		return (it->second);
	else
		return (-1);
}

bool	BitcoinExchange::inputLineIsUsable( const std::string line ) const{

	if (line.length() == 0)
		throw(BitcoinExchange::EmptyLineException());
	std::string date = line.substr(0, 10);
	Date lineDate(date);
	if (!lineDate.isValidDate())
		throw (Date::NonExistantDateException());
	Date CreationDate("2009-01-03");
	if (lineDate < CreationDate)
		throw(BitcoinExchange::ImpossibleDateException());
	if (line.substr(10, 3) != " | ")
		throw (BitcoinExchange::UnvalidValueFormatException());
	std::string valStr = line.substr(13);
	if (valStr[0] == '-' && isdigit(valStr[1]))
		throw (BitcoinExchange::NegativeValueException());
	if (!isFloatFormat(valStr))
		throw (BitcoinExchange::UnvalidValueFormatException());
	double val = atof(valStr.c_str());
	if (val > 1000)
		throw (BitcoinExchange::ValueTooLargeException());
	return (true);
}

void	BitcoinExchange::setUserEntry( void ){

	std::string input = ".";
	while (input != "y" && input != "n" && feof(stdin) == 0)
	{
		std::cout << YELLOW << "Do you wish to set missing entries manually ? (y/n) :\n" << RESET;
		input.clear();
		std::getline(std::cin, input);
	}
	if (input == "y")
	{
		_askUserEntry = true;
		std::cout << YELLOW << "Missing entries set to manual." << RESET << std::endl;
		return ;
	}
	std::cout << YELLOW << "Missing entries set to default." << RESET << std::endl;
	_askUserEntry = false;
	return ;
}

double	BitcoinExchange::askUserEntry( const std::string date ){

	std::string input = ".";
	while (!isFloatFormat(input) && feof(stdin) == 0)
	{
		std::cout << YELLOW << "Enter a new rate for " << CYAN << date << YELLOW << ": " << CYAN;
		input.clear();
		std::getline(std::cin, input);
	}
	if (feof(stdin) != 0)
	{
		std::cout << YELLOW << "Closed stdin: Missing entries set to default" << RESET << std::endl;
		_askUserEntry = false;
		return (-1);
	}
	Date	d(date);
	double	rate = atof(input.c_str());
	_csv.insert(std::make_pair(d, rate));
	return (rate);
}

void	BitcoinExchange::convertInputList( const std::string inputFile ){

	std::ifstream	file(inputFile);
	std::string		line;
	size_t			lineNb = 0;

	if (file.is_open()) {
		setUserEntry();
		while (getline(file, line))
		{
			lineNb++;
			// Check if there is a header for the first line
			if (lineNb == 1 && line != "date | value")
				std::cout << MAGENTA << "Conversion Note: " << WHITE << "no header in input file" << RESET << std::endl;
			else if (lineNb == 1)
				continue;
			try
			{
				inputLineIsUsable(line);
				double rate = getStockRate(keepDate(line));
				if (rate == -1 && _askUserEntry == true)
					rate = askUserEntry(keepDate(line));
				if (rate == -1)
					rate = getClosestAnteriorRate(keepDate(line));
				double	balance = strToFloat(line.substr(13));
				std::cout << GREEN << keepDate(line) << " => " << balance << " = " << rate * balance << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cout << BLUE << "Conversion Error: "<< CYAN <<"line " << lineNb << BLUE << ": " << WHITE << e.what() << RESET << std::endl;
			}
		}
		file.close();
	}
	else
		throw(BitcoinExchange::InputFileErrorException());
	return ;
}

double	BitcoinExchange::getClosestAnteriorRate( const std::string date ) const{

	Date d(date);
	Date creationDate("2009-01-03");
	std::map<Date, double>::const_iterator it;

	while (d > creationDate)
	{
		it = _csv.find(d);
		if (it != _csv.end())
		{
			std::cout << BLUE << "(Anterior) " << RESET;
			return (it->second);
		}
		--d;
	}
	throw (BitcoinExchange::NoAnteriorDateException());
}
