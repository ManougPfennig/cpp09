#ifndef RPN_H
# define RPN_H


# include <iostream>
# include <iomanip>
# include <sstream>
# include <limits>
# include <string>
# include <exception>
# include <stack>

# define RESET   "\033[0m"
# define RED     "\033[31m"      
# define GREEN   "\033[32m"      
# define YELLOW  "\033[33m"      
# define BLUE    "\033[34m"      
# define MAGENTA "\033[35m"      
# define CYAN    "\033[36m"      
# define WHITE   "\033[37m"

# define OPERATOR 1
# define OPERAND 2

// Pile of elements usable in a Reverse Polish Notation.
// - Operator are stocked as single-characters strings
// - Values are stocked as any string
class	RPN {

	private:
		std::stack<std::string>	_pile;

	public:
		~RPN( void );
		RPN( void );
		RPN( const RPN &r );
		// -> Copies _pile's content from r.
		RPN &operator=( const RPN &r );

		// -> Checks if the character is an operator :
		// - Returns 1 for [+]
		// - Returns 2 for [-]
		// - Returns 3 for [/]
		// - Returns 4 for [*]
		// + Returns 0 otherwise.
		static int			isOperator( const int op );

		// Exemple: "8 9 + 4 *"
		//-> Reads the whole expression to check for errors such as:
		// - Invalid syntax
		// - Impossible expression
		// - Unvalid characters
		// -> Returns true if no issues were found, returns false otherwise.
		static bool			isValidExpression( const std::string exp );

		// -> Same as isValidExpression()
		// - throws custom error messages for each error type.
		// - Returns false if no error was found.
		bool				getExpressionError( const std::string exp );

		// -> Reads the whole expression and store each elements in _pile
		// in the same order as in the expression.
		// - Will throw an exception if the expression cannot be calculated.
		// - Will empty _pile before storing any new element.
		void				storeExpression( const std::string exp );

		// -> Operate X by Y using the given sign
		// - X and Y must be convertible to floating point value.
		// - Acceptable signs: [ + - / * ]
		// - Will throw an exception if an unvalid operator is used.
		// - x="5", y="2", sign="*"  -> becomes 5*2 -> operate returns 10
		long double			operate( const std::string x, const std::string y, const std::string sign) const;

		// -> Evaluate the Reverse Polish Notation stored in _pile.
		// - Will empty _pile by doing so
		// - Returns the result of the operation
		long double			calculateRPN( void );

		// -> Converts a long double value to a std::string representation
		static std::string	lDoubletoStr( long double ld );

		// -> Opens a prompt for the user to write an infix expression
		// - The expression will be converted to Reverse Polish Notation.
		// - The converted expression and it's result will be displayed.
		// + If an invalid expression is given, user will be reprompted.
		static void			shuntingYard( void );

		// -> Checks if the expression is in valid infix format
		// - Exemple: 2 + 3 * 8
		static	int			isValidInfix( const std::string exp );

		static std::string	getInfixInput( void );

	class	UnvalidExpressionException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Cannot store an invalid expression");
		}
	};
	class	EmptyExpressionException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Two first expressions must be numbers");
		}
	};
	class	ImpossibleCalculationException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Imposible to calculate this expression");
		}
	};
	class	UnvalidCharacterException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Unvalid character found");
		}
	};
	class	ConnectedExpressionException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Expressions must be separated by spaces");
		}
	};
	class	OperateErrorException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Operate: Unvalid expression used");
		}
	};
	class	InvalidPileException : public std::exception
	{
		const char *what() const throw()
		{
			return ("Cannot calculate an invalid pile");
		}
	};
};

#endif