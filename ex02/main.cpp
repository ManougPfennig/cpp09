#include "PmergeMe.hpp"

void	displayTutorial( void )
{
	// Definition of the Ford-Johnson algorithm
	std::cout << YELLOW << "Definition:" << std::endl;
	std::cout << GREEN << "The Ford-Johnson Algorithm" << WHITE << ", also known as merge-insertion sort, \n\
is a sorting algorithm designed to perform as few comparisons as possible to sort a collection.\n\
Unfortunately, the algorithm needs some specific data structures to keep track of the order of the elements \n\
and is generally too slow to be practical. Anyway, it is an interesting algorithm from a computer science point of view;\n\
while not performing an optimal number of comparisons, it's still a reference and one of the best known \n\
comparison sorts when it comes to reducing the number of comparisons.\n" << std::endl;
	std::cout << GREEN << "A001768" << WHITE << ", is the name of the integer sequence containing the number of comparisons\n\
necessary for Ford-Johnson to sort a list of n elements in a worst-case scenario." << std::endl;
	std::cout << YELLOW << "\nHow to use:" << WHITE << std::endl;
	std::cout << "Start " << GREEN << "./PmergeMe" << WHITE << " with a string representation of a list of positive integers, \
ranging from " << CYAN << "0" << WHITE << " to " << CYAN << "2147483647" << WHITE << "." << std::endl;
	std::cout << "The list will be sorted using the " << GREEN << "The Ford-Johnson Algorithm" << WHITE << " using two different \
types of containers.\nIn this case, " << CYAN << "vector" << WHITE << " and " << CYAN << "deque" << WHITE << " are used. \
The execution time will be dsplayed alongside both sorted list." << std::endl;
	std::cout << YELLOW << "\nThis algorithm uses a combination of a recursive merge-sort and insertion-sort." << RESET << std::endl;

	// PENSER A AJOUTER UNE DEFINITION POUR MERGE-SORT ET INSERT-SORT
	return ;
}

void	displayMenu( void ){

	// Display infos about launch
	std::cout << YELLOW << "Start " << GREEN << "PmergeMe" << YELLOW << " with:" << RESET << std::endl;
	std::cout << YELLOW << "- keyword " << BLUE << "tutorial" << YELLOW << " for a quick explanation." << RESET << std::endl;
	std::cout << YELLOW << "Or a string represensation of a " << GREEN << "list of integers" << YELLOW << " to sort." << RESET << std::endl;
	return ;
}

int main(int ac, char **av)
{
	PmergeMe	pmm;

//	system("clear");
	if (ac == 2)
	{
		std::string	entry(av[1]);
		if (entry == "tutorial")
			displayTutorial();
		else
		{
			try
			{
				t_timer vecInfo;
				t_timer deqInfo;
				// Convert and store the values passed as parameter
				pmm.readInput(av[1]);
				// Checks if the list is already sorted
				if (PmergeMe::isListSorted(pmm.getDeque()))
				{
					std::cout << YELLOW << "List is already sorted" << RESET << std::endl;
					return (0);
				}
				std::cout << YELLOW << "before: " << CYAN << pmm.vectorToOs() << YELLOW << ".\n";
				pmm.FordJohnsonVector(&vecInfo);
				pmm.FordJohnsonDeque(&deqInfo);
				std::cout << YELLOW << "after : " << CYAN << pmm.vectorToOs() << YELLOW << ".\n";
				std::cout << YELLOW << "Time to process a range of " << CYAN << pmm.getVector().size() << YELLOW << " elements with " << GREEN << "std::vector " << YELLOW << ": " << CYAN << vecInfo.duration.count() << YELLOW << " μs\n";
				std::cout << YELLOW << "Time to process a range of " << CYAN << pmm.getDeque().size() << YELLOW <<" elements with " << GREEN << "std::deque " << YELLOW << ": " << CYAN <<deqInfo.duration.count() << YELLOW << " μs\n";
				std::cout << YELLOW << "(Worst case number of comparaisons: " << CYAN << pmm.A001768(-1) << YELLOW << ")" << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cout << RED << "Error: " << WHITE << e.what() << std::endl;
				return (1);
			}
		}
	}
	else if (ac == 1)
		displayMenu();
	else
		std::cout << YELLOW << "Start " << GREEN << "./PmergeMe" << YELLOW << " with only one argument." << std::endl;
	return (0);
}