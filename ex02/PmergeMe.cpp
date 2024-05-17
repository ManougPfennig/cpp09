#include "PmergeMe.hpp"

PmergeMe::~PmergeMe( void ) {}
PmergeMe::PmergeMe( void ) {}
PmergeMe::PmergeMe( const PmergeMe &p ): _vector(p._vector), _deque(p._deque) {}

PmergeMe &PmergeMe::operator=( const PmergeMe &p ) {

	this->_vector = p._vector;
	this->_deque = p._deque;
	return (*this);
}

void	PmergeMe::readInput( const std::string exp ) {

	// Looks for invalid characters inside the input string
	for (int i = 0; exp[i]; i++){
		
		if (exp[i] != ' ' && !isdigit(exp[i]))
			throw (PmergeMe::UnvalidCharacterException());
	}
	// Checks if the string is not empty
	if (!exp.size())
		throw (PmergeMe::EmptyInputException());
	// Checks if the string is not only made of spaces
	int	i = 0;
	while (exp[i])
	{
		if (exp[i] != ' ')
			break;
		i++;
	}
	if (!exp[i])
		throw (PmergeMe::EmptyInputException());
	std::string	valStr;
	long		val = 0;
	i = 0;
	// Iterate over the value list
	while (exp[i])
	{
		// skips spaces
		while (exp[i] == ' ')
			i++;
		// checks if the string is over
		if (!exp[i])
			break;
		// stores the number as a substring
		valStr = exp.substr(i);
		valStr = valStr.substr(0, valStr.find(' '));
		// converts to long
		val = atol(valStr.c_str());
		// looks for values too big
		if (val > INT_MAX)
			throw (PmergeMe::ValueTooHighException());
		// adds the new value to _vector and _deque
		_vector.push_back((int)val);
		_deque.push_back((int)val);
		// skips to the end of the number
		while(exp[i] && exp[i] != ' ')
			i++;
	}
	return ;
}

std::vector<int>	&PmergeMe::getVector( void ) {

	return (_vector);
}

std::deque<int>	&PmergeMe::getDeque( void ) {

	return (_deque);
}

bool	PmergeMe::isListSorted( const std::deque<int> &list ) {

	std::deque<int>::const_iterator it = list.begin();
	int	i = 0;
	int y = *it;
	while (it != list.end())
	{
		i = y;
		y = *it;
		if (i != y && i > y)
			return (false);
		it++;
	}
	return (true);
}

std::vector<int>	PmergeMe::mergeVector( std::vector<int> left, std::vector<int> right ) {

	std::vector<int> result;
	int i = 0;
	int j = 0;

	// Moves on both halves to find the lowest values and merge them in 'result'
	while (i < left.size() && j < right.size())
	{
		if (*(left.begin() + i) < *(right.begin() + j))
		{
			result.push_back(*(left.begin() + i));
			i++;
		}
		else
		{
			result.push_back(*(right.begin() + j));
			j++;
		}
	}

	// Puts any remaining values in 'result'
	while (i < left.size())
	{
		result.push_back(*(left.begin() + i));
		i++;
	}
	while (j < right.size())
	{
		result.push_back(*(right.begin() + j));
		j++;
	}
	return (result);
}

std::vector<int>	PmergeMe::mergeSortVector( std::vector<int> vec ) {

	if (vec.size() <= 1)
		return (vec);

	// Find the middle of the vector
	std::vector<int>::iterator middle = vec.begin() + (vec.size() / 2);

	// Splits the vector in half in the middle and copies both halves in left and right
	std::vector<int> leftHalf(vec.begin(), middle);
	std::vector<int> rightHalf(middle, vec.end());

	// Sorts each halves recursively by merging them
	std::vector<int> sortedLeft = mergeSortVector(leftHalf);
	std::vector<int> sortedRight = mergeSortVector(rightHalf);

	// Merges the halves
    return (mergeVector(sortedLeft, sortedRight));
}

std::vector<int>::const_iterator	PmergeMe::binarySearchVector( std::vector<int> &hayStack, int val, int low, int high ) const{

	std::vector<int>::const_iterator it = hayStack.begin();

	// If the search range is lower than one, returns the iterator to the found location.
	if (high <= low)
	{
		if (val > *(it + low))
			return (it + (low + 1));
		else
			return (it + low);
	}

	int mid = (low + high) / 2;

	// If the value is in the middle of the range, returns the iterator to the found location.
	if (val == *(it + mid))
		return (it + mid);

	// If the value is higher than the middle of the range, look inside the higher half.
	// Else, look inside the lower half
	if (val > *(it + mid))
		return (binarySearchVector(hayStack, val, mid + 1, high));
	else
		return (binarySearchVector(hayStack, val, low, mid - 1));
}

std::vector<int>	PmergeMe::insertionSortVector( std::vector<int> toFill, std::vector<int> input) const{

	int selected;
	std::vector<int>::const_iterator loc;
	int low, high;
	while (!input.empty())
	{
		selected = input.back();

		low = 0;
		high = toFill.size() - 1;

		// find location where selected should be inserted
		loc = binarySearchVector(toFill, selected, low, high);

		// Insert the value in the found location
		toFill.insert(loc, selected);
		input.pop_back();
	}
	return (toFill);
}

void	PmergeMe::FordJohnsonVector( t_pmm *info) {

	// Saves starting time if a timer is passed as parameter
	if (info)
		info->start = std::chrono::high_resolution_clock::now();

	std::vector<int>					vMin;
	std::vector<int>					vMax;
	std::vector<std::pair<int, int>>	vPair;
	int									val1;
	int									val2;

	// Stores the list of values by pairs in vPair
	while (_vector.size() >= 2)
	{
		val1 = _vector.back();
		_vector.pop_back();
		val2 = _vector.back();
		_vector.pop_back();
		vPair.push_back(std::make_pair(val1, val2));
	}

	// If the list's size is an odd number, the remaining value is pushed to vMax by default
	if (_vector.size())
	{
		vMax.push_back(_vector.back());
		_vector.pop_back();
	}

	// The highest number of each pair is pushed to vMax and the lowest to vMin
	while (vPair.size())
	{
		if(vPair.back().first >= vPair.back().second)
		{
			vMax.push_back(vPair.back().first);
			vMin.push_back(vPair.back().second);
			vPair.pop_back();
		}
		else
		{
			vMax.push_back(vPair.back().second);
			vMin.push_back(vPair.back().first);
			vPair.pop_back();
		}
	}

	// The values of vMax are the sorted recursively using the Merge-Sort algorithm
	vMax = mergeSortVector(vMax);

	// The remaining values of VMin are the inserted in vMax using Insertion-Sort (Binary-Search) algorithm
	_vector = insertionSortVector(vMax, vMin);

	// Saves ending time if a timer is passed as parameter
	if (info)
	{
		info->end = std::chrono::high_resolution_clock::now();
		info->duration = info->end - info->start;
	}
	return ;
}





