#include "PmergeMe.hpp"

void	displayTutorial( void )
{
	// Definition of the Ford-Johnson algorithm
	std::cout << YELLOW << "Definition:" << std::endl;
	std::cout << GREEN << "The Ford-Johnson Algorithm" << WHITE << ", also known as merge-insertion sort, \n\
is an in-place sorting algorithm designed to perform as few comparisons as possible to sort a collection.\n\
Unfortunately, the algorithm needs some specific data structures to keep track of the order of the elements \n\
and is generally too slow to be practical. Anyway, it is an interesting algorithm from a computer science point of view;\n\
while not performing an optimal number of comparisons, it's still a reference and one of the best known \n\
comparison sorts when it comes to reducing the number of comparisons." << std::endl;
	std::cout << YELLOW << "\nHow to use:" << WHITE << std::endl;
	std::cout << "Start " << GREEN << "./PmergeMe" << WHITE << " with a string representation of a list of positive integers, \
ranging from " << CYAN << "0" << WHITE << " to " << CYAN << "2147483647" << WHITE << "." << std::endl;
	std::cout << "The list will be sorted using the " << GREEN << "The Ford-Johnson Algorithm" << WHITE << " using two different \
types of containers.\nIn this case, " << CYAN << "vector" << WHITE << " and " << CYAN << "list" << WHITE << " are used. \
The execution time will be dsplayed alongside both sorted list." << std::endl;

	// PENSER A AJOUTER UNE DEFINITION POUR MERGE-SORT ET INSERT-SORT
	return ;
}

int main(int ac, char **av)
{
	PmergeMe	ouga;

//	system("clear");
	if (ac == 2)
	{
		try
		{
			t_pmm vectorTimer;
			t_pmm listTimer;
			// Convert and store the values passed as parameter
			ouga.readInput(av[1]);
			// Checks if the list is already sorted
			if (PmergeMe::isListSorted(ouga.getList()))
			{
				std::cout << YELLOW << "List is already sorted" << RESET << std::endl;
				return (0);
			}
			ouga.FordJohnsonVector(&vectorTimer);
			// ouga.FordJohnsonList(&listTimer);
		}
		catch (const std::exception &e)
		{
			std::cout << RED << "Error: " << WHITE << e.what() << std::endl;
			return (1);
		}
	}
	else if (ac == 1)
		displayTutorial();
	else
		std::cout << YELLOW << "Start " << GREEN << "./PmergeMe" << YELLOW << " with only one argument." << std::endl;
	return (0);
}