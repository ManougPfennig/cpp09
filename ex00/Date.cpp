#include "Date.hpp"

Date::~Date( void ){}

Date::Date( void ){

	std::time_t currentTime = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&currentTime);

    _year = timeinfo->tm_year + 1900;
	_month = timeinfo->tm_mon + 1;
	_day = timeinfo->tm_mday;

	return ;
}

Date::Date( const Date &d ): _year(d.getYear()), _month(d.getMonth()), _day((d.getDay())) {}

Date::Date( const std::string date ){

	if (isDateFormat(date) == false)
		throw (UnvalidDateException());

	std::string tmp;
	
	tmp = date.substr(0, 4);
	_year = std::atoi(tmp.c_str());

	tmp = date.substr(5, 2);
	_month = std::atoi(tmp.c_str());

	tmp = date.substr(8, 2);
	_day = std::atoi(tmp.c_str());

	return ;
}

Date	&Date::operator=( const Date &d ){

	_year = d.getYear();
	_month = d.getMonth();
	_day = d.getDay();
	return (*this);
}

Date	&Date::operator--( void ){

	while (_year >= 0)
	{
		_day--;
		if (_day < 1)
		{
			_day = 31;
			_month--;
		}
		if (_month < 1)
		{
			_month = 12;
			_year--;
		}
		if (isValidDate())
			return (*this);
	}
	throw (Date::ImpossibleDateException());
}

Date	&Date::operator++( void ){

	while (_year < INT_MAX)
	{
		_day++;
		if (!isValidDate())
		{
			_day = 1;
			_month++;
		}
		if (!isValidDate())
		{
			_month = 1;
			_year++;
		}
		return (*this);
	}
	throw (Date::ImpossibleDateException());
}

std::ostream &operator<<( std::ostream &os, const Date &d){

	os << d.getYear() << "-" << d.getMonth() << "-" << d.getDay();
	return (os);
}

bool	Date::operator>( const Date &d ) const{

	// Checks the year difference first
	if (_year > d.getYear())
		return (true);
	else if (_year < d.getYear())
		return (false);

	// Checks the month difference
	if (_month > d.getMonth())
		return (true);
	else if (_month < d.getMonth())
		return (false);
	
	// Checks the day difference
	if (_day > d.getDay())
		return (true);
	else if (_day < d.getDay())
		return (false);

	// Returns false here, as they are the same
	return (false);
}

bool	Date::operator<( const Date &d ) const{

	// Checks the year difference first
	if (_year < d.getYear())
		return (true);
	else if (_year > d.getYear())
		return (false);

	// Checks the month difference
	if (_month < d.getMonth())
		return (true);
	else if (_month > d.getMonth())
		return (false);
	
	// Checks the day difference
	if (_day < d.getDay())
		return (true);
	else if (_day > d.getDay())
		return (false);

	// Returns false here, as they are the same
	return (false);
}

bool	Date::operator==( const Date &d ) const{

	if (_year != d.getYear() || _month != d.getMonth() || _day != d.getDay())
		return (false);
	return (true);
}

int		Date::getYear( void ) const {return (_year);}
void	Date::setYear( const int &val ) {_year = val;}

int		Date::getMonth( void ) const {return (_month);}
void	Date::setMonth( const int &val ) {_month = val;}

int		Date::getDay( void ) const {return (_day);}
void	Date::setDay( const int &val ) {_day = val;}

bool 	Date::isValidDate( void ) const {

	Date	today;

	// Check if the month is valid
	if (_month < 1 || _month > 12)
		return (false);

	// Check if the day is valid
	if (_day < 1 || _day > 31)
		return (false);

	// Check for specific month-day combinations that are invalid
	if ((_month == 4 || _month == 6 || _month == 9 || _month == 11) && _day > 30)
		return (false);

	if (_month == 2)
	{
		// Check for leap year
		if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0))
		{
		if (_day > 29)
			return (false);
		} 
		else
		{
		if (_day > 28)
			return (false);
		}
	}

	if (*this > today)
		return (false);
	return (true);
}

bool		Date::isDateFormat( const std::string date){

	int index = 0;

	if (date.length() != 10)
		return (false);

	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(date[index]))
			return(false);
		index++;
	}

	if (date[index] != '-')
		return(false);
	index++;

	for (int i = 0; i < 2; i++)
	{
		if (!isdigit(date[index]))
			return(false);
		index++;
	}

	if (date[index] != '-')
		return(false);
	index++;

	for (int i = 0; i < 2; i++)
	{
		if (!isdigit(date[index]))
			return(false);
		index++;
	}
	return (true);
}