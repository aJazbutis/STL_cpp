#include "PmergeMe.hpp"

static void	printInfo(int size, std::string name, std::time_t time)	{
	std::cout << "Time to process a range of ";
	std::cout << size << " elements with std::" + name;
	std::cout << " : " << time << " us" << std::endl;
}
static int	inputError(std::string msg = "")	{
	msg = msg.empty()? "Error" : "Error: " + msg;
	std::cerr << msg << std::endl;
	return (1);
}
	
int	main(int argc, char **argv)	{
	std::vector<int>	input1;
	std::deque<int>		input2;

	if (argc < 2)
		return (0);
	while (*(++argv))	{
		int n = toPositiveInt(*argv);
		if (n < 0)
			return inputError(*argv);
		else	{
			input1.push_back(n);
			input2.push_back(n);
		}
//		std::cout << n << std::endl;
	}
	std::cout << "Before: ";
	printOut(input1);
	std::time_t	t1, t2;
//	t1 = mergeInsertionSort(input1, 0, input1.size() - 1);
	t2 = mergeInsertionSort(input2, 0, input2.size() - 1);
t1 = mergeInsertionSort(input1, 0, input1.size() - 1);
	std::cout << "After: ";
	printOut(input1);
	printInfo(input1.size(), "vector", t1);
	printInfo(input2.size(), "deque", t2);
	return (0);
}
