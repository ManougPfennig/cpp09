#ifndef PMERGEME_H
# define PMERGEME_H

# define RESET   "\033[0m"
# define RED     "\033[31m"      
# define GREEN   "\033[32m"      
# define YELLOW  "\033[33m"      
# define BLUE    "\033[34m"      
# define MAGENTA "\033[35m"      
# define CYAN    "\033[36m"      
# define WHITE   "\033[37m"

# include <iostream>
# include <list>
# include <vector>
# include <chrono>
# include <exception>
# include <climits>

// -> Structure used to facilitate the storing of a time duration
typedef struct	s_pmm
{
	std::chrono::system_clock::time_point	chronoStart;
	std::chrono::system_clock::duration		chronoDuration;
	long									duration;
	std::string								containerUsed;
}				t_pmm;


class PmergeMe {

	private:
		std::vector<int>	_vector;
		std::list<int>		_list;

	public:
		~PmergeMe( void );
		PmergeMe( void );
		PmergeMe( const PmergeMe &p );
		PmergeMe &operator=( const PmergeMe &p );

	// -> Takes a string representation of a list of positive integers
	// Valid input: [0 ; INT_MAX]
	// - Will store a copy of all inputs in _vector and _list respectively.
	// - Will throw an error message in case of invalid input
	void				readInput( const std::string exp );

	// -> Will sort all values inside _vector using the Ford-Johnson algorithm
	// - Duration time will be stored in the timer struct if non-null
	// - Container type will be stored in the t_pmm struct
	void				FordJohnsonVector( t_pmm *timer );

	// -> Will sort all values inside _list using the Ford-Johnson algorithm
	// - Duration time will be stored in the timer struct if non-null
	// - Container type will be stored in the t_pmm struct
	void				FordJohnsonList( t_pmm *timer );

	// -> Checks if a std::list of int is sorted
	// - Returns true if sorted or empty
	// - Returns false otherwise
	static bool			isListSorted( const std::list<int> &lst );

	// Merges and sort two vectors in a new one and returns it
	std::vector<int>	mergeVector( std::vector<int> left, std::vector<int> right);

	// -> Sorts the vector recursively using the Merge-Sort algorithm
	std::vector<int>	mergeSortVector( std::vector<int> vec );

	// -> Sorts the list recursively using the Merge-Sort algorithm
	void				mergeSortList( std::list<int> lst );

	// -> Returns a reference to private container _vector
	std::vector<int>	&getVector( void );

	// -> Returns a reference to private container _list
	std::list<int>		&getList( void );

	class UnvalidCharacterException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Unvalid character in expression");
		}
	};
	class ValueTooHighException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Value higher than INT_MAX in expression");
		}
	};
	class EmptyInputException: public std::exception
	{
		const char *what() const throw()
		{
			return ("Empty expression");
		}
	};
};

#endif
