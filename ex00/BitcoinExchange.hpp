#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <iostream>
# include <map>
# include <exception>
# include <fstream>
# include <string>
# include <cfloat>

class BitcoinExchange {

	private:
		std::map<std::string, double> _csv;

	public:
		~BitcoinExchange( void );
		BitcoinExchange( void );
		BitcoinExchange( const BitcoinExchange &be );
		BitcoinExchange	&operator=( const BitcoinExchange &be );


		// csv format: "YYYY-MM-DD,x.xf"
		// -> Will only return the date part of the line format
		std::string	keepDate( const std::string line ) const;
		// csv format: "YYYY-MM-DD,x.xf"
		// -> Will only return the stock rate of the line format
		double		keepStockRate( const std::string line ) const;
		// -> Checks if the string passed as parameter respects the "YYYY-MM-DD,x.xf" format for input.
		// - returns 'true' if no issue was found.
		// - Will throw an error message if the format is incorrect, the date doesn't exist on the calendar or the value is not in valid range. [-FLOAT_MAX; FLOAT_MAX]
		bool		CSVLineIsUsable( const std::string line ) const;
		// csv format: "YYYY-MM-DD,x.xf"
		// -> Reads the file 'data.csv' from the working directory to store it's values in _csv.
		// + If a line is in a invalid format, it will throw 'UnvalidFormatException'.
		// + If the file doesn't exist or is cannot be opened, it will throw 'CsvFileErrorException'.
		void		storeDataCSV( const std::string inputFile );
		// -> Reads and return a new line from the input file.
		std::string	getLineFromInput( const std::string inputFile );
		// date format: "YYYY-MM-DD"
		// -> Returns the rate from said date inside the _csv database.
		// - If no corresponding date was found, getStockRate() will return -1.
		double		getStockRate( const std::string date ) const;
		// -> Returns the closest anterior date found in the _csv database.
		// - If no date was found, will throw NoAnteriorDateException.
		std::string	getClosestAnteriorDate( const std::string data) const;
		// -> Checks if the string passed as parameter respects the "YYYY-MM-DD | x.xf" format for input.
		// - returns 'true' if no issue was found.
		// - Will throw a specific error message if the format is incorrect, the date doesn't exist on the calendar
		// or the value is not in valid range. [0; 1000]
		bool		inputLineIsUsable( const std::string line );
		// -> Checks if the date in YYYY-MM-DD format exist on the Gregorian calendar.
		// - Return 'true' if the date exists.
		// - Return 'false' if the date doesn't exist or is in the future.
		bool		isValidDate( const std::string date ) const;


	class UnvalidFormatException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Unvalid line inside CSV file");
		}
	};
	class CsvFileErrorException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Cannot open 'data.csv' file in working directory");
		}
	};
	class UnvalidInputException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Unusable line format in input file");
		}
	};
	class NoAnteriorDateException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Could not find a value for this date");
		}
	};
	class ValueTooLargeException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Too large a number.");
		}
	};
	class NegativeValueException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Not a positive number.");
		}
	};
};


#endif