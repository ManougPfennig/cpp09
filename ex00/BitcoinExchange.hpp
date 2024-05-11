#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <string>
# include <cmath>
# include <cfloat>
# include <cstdlib>
# include <exception>
# include <map>
# include <vector>
# include "Date.hpp"


# define RESET   "\033[0m"
# define RED     "\033[31m"      
# define GREEN   "\033[32m"      
# define YELLOW  "\033[33m"      
# define BLUE    "\033[34m"      
# define MAGENTA "\033[35m"      
# define CYAN    "\033[36m"      
# define WHITE   "\033[37m"


class BitcoinExchange {

	private:
		// Map of all CSV entries, by Date and Rate
		std::map<Date, double>		_csv;
		std::vector<std::string>	_output;
		// User variable will alsways be set to false when constructing
		bool					_askUserEntry;

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
		std::string	keepStockRate( const std::string line ) const;

		// string format: "x.x", x being any numeric values
		// -> Converts the string representation of a float to a floating point variable
		double		strToFloat( std::string str) const;

		// -> Checks if the string passed as parameter respects the "YYYY-MM-DD,x.x" format for input, x being any numeric values.
		// - returns 'true' if no issue was found.
		// - Will throw an error message if the format is incorrect, the date doesn't exist on the calendar or the value is not in valid range. [-FLOAT_MAX; FLOAT_MAX]
		bool		CSVLineIsUsable( const std::string line ) const;

		// string format: "x.x" or "x", x being any numeric values
		// -> Checks if str is a valid string representation of a floating point number'
		// - Returns 'true' if no issues was found.
		// - Returns 'false' otherwise.
		bool		isFloatFormat( const std::string str ) const;

		// csv format: "YYYY-MM-DD,x.xf"
		// -> Reads the file 'data.csv' from the working directory to store it's values in _csv.
		// + If a line is in a invalid format, it will throw 'UnvalidFormatException'.
		// + If the file doesn't exist or is cannot be opened, it will throw 'CsvFileErrorException'.
		void		readDataCSV( const std::string inputFile );

		// date format: "YYYY-MM-DD"
		// -> Returns the rate from said date inside the _csv database.
		// - If no corresponding date was found, getStockRate() will return -1.
		double		getStockRate( const std::string date ) const;

		// -> Returns the closest anterior rate found in the _csv database.
		// - If no rate was found, will throw NoAnteriorRateException.
		double		getClosestAnteriorRate( const std::string date ) const;

		// -> Checks if the string passed as parameter respects the "YYYY-MM-DD | x.x" format for input, x being any numeric values.
		// - returns 'true' if no issue was found.
		// - Will throw a specific error message if the format is incorrect, the date doesn't exist on the calendar or if the value is not in the valid range. [0; 1000]
		bool		inputLineIsUsable( const std::string line ) const;

		// -> Will match each entry in inputFile to the _csv database and multiply each value
		// to it's corresponding rate
		// - Will ask if the user wants to add missing entries manually 
		void		convertInputList( const std::string inputFile );

		// -> Will ask the user if he wants to be prompted to enter missing entries manually or for convertInputList() to treat them by default
		void		setUserEntry( void );

		// -> If set with setUserEntry(), when a missing entry case occurs, user can write a new entry in the _csv database for the corresponding date
		// - User can leave the entry empty to treat the case as default
		// - Entry written in an incorrect format will be reprompted
		double		askUserEntry( const std::string date );

	class EmptyLineException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Empty line in file");
		}
	};
	class UnvalidValueFormatException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Unvalid value format");
		}
	};
	class UnvalidValueSizeException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Value outside of float scope");
		}
	};
	class CsvFileErrorException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Cannot open CSV file in working directory");
		}
	};
	class InputFileErrorException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Cannot open Input file in working directory");
		}
	};
	class ImpossibleDateException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Date prior to ₿itcoin creation");
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