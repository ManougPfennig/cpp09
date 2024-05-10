#ifndef DATE_H
# define DATE_H

# include <iostream>
# include <exception>
# include <ctime>
# include <climits>

class Date {

	private:

		int	_year;
		int	_month;
		int	_day;

	public:

		~Date( void );
		// Default constructor will set the date to current time
		Date( void );
		// Copy constructor will set the date to d's date
		Date( const Date &d );
		// Format: "YYYY-MM-DD"
		// String date constructor will convert from string format
		Date( std::string date );
		// Operator '=' override
		// - Copies all values from one to the other
		Date 	&operator=( const Date &d );
		// Operator '--' override
		// - Makes the date go one day in the past
		Date	&operator--( void );
		// Operator '--' override
		// - Makes the date go one day in the futur
		Date	&operator++( void );
		// Operator '>' override
		// - Returns true if the date is more recent than the other
		// - Returns false otherwise or if they are the same date
		bool 	operator>( const Date &d ) const;
		// Operator '<' override
		// - Returns true if the date is less recent than the other
		// - Returns false otherwise or if they are the same date
		bool 	operator<( const Date &d ) const;
		// Operator '==' override
		// - Returns true if they are the same date
		// - Returns false otherwise
		bool 	operator==( const Date &d ) const;


		// Returns the value of private variable _year
		int		getYear( void ) const;
		// Returns the value of private variable _month
		int		getMonth( void ) const;
		// Returns the value of private variable _day
		int		getDay( void ) const;

		// Sets the value of private variable _year to val
		void	setYear( const int &val );
		// Sets the value of private variable _month to val
		void	setMonth( const int &val );
		// Sets the value of private variable _day to val
		void	setDay( const int &val );

		// -> Checks if the specified date is valid
		// - Returns true if the date existed and isn't in the futur
		// - Returns false otherwise
		bool	isValidDate( void ) const;

		// Date format "YYYY-MM-DD"
		// - Returns false if the string does not correspond to the date format
		// - Returns true otherwise
		static bool	isDateFormat( const std::string date);

	class UnvalidDateException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Unvalid date format");
		}
	};
	class NonExistantDateException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Specified date does not exist");
		}
	};
	class ImpossibleDateException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Reached Date limits");
		}
	};
};

std::ostream &operator<<( std::ostream &os, const Date &d);

#endif