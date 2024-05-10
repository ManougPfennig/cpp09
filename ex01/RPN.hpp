#ifndef RPN_H
# define RPN_H

/*Un chiffre est un signe d'écriture utilisé seul ou en combinaison pour représenter des
nombres entiers. Dans un système de numération positionnel comme le système décimal,
un petit nombre de chiffres suffit pour exprimer n'importe quelle valeur.
Le nombre de chiffres du système est la base. Le système décimal, le plus courant des
systèmes de numération, comporte dix chiffres représentant les nombres de zéro à neuf.*/

# include <iostream>
# include <exception>
# include <stack>

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

		// -> Checks if the string is an operator :
		// - Returns 1 for [+]
		// - Returns 2 for [-]
		// - Returns 3 for [/]
		// - Returns 4 for [*]
		// + Returns 0 otherwise.
		static int	isOperator( const int op );

		// Exemple: "8 9 + 4 *"
		//-> Reads the whole expression to check for errors such as:
		// - Invalid syntax
		// - Impossible expression
		// - Unvalid characters
		// -> Returns true if no issues were found, returns false otherwise.
		static bool	isValidExpression( const std::string exp );

		// -> Same as isValidExpression()
		// - throws custom error messages for each error type.
		// - Returns false if no error was found.
		bool	getExpressionError( const std::string exp );

		// -> Reads the whole expression and store each elements in _pile
		// in the same order as in the expression.
		// - Will throw an exception if the expression cannot be calculated
		void		storeExpression( const std::string exp );

		// -> Operate X by Y using the given sign.
		// Exemple:
		// - For x=5, y=2, sign=* operate returns 5*2 (10)
		long		operate( long x, long y, std::string sign);

		// -> Evaluate the Reverse Polish Notation stored in _pile.
		// - Will empty _pile by doing so
		// - Returns the result of the operation
		long		calculate( void );

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
	
};

#endif