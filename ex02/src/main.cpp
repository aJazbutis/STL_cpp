#include "PmergeMe.hpp"

static void	printInfo(int size, std::string name, std::time_t time)	{
	std::cout << "Time to process a range of ";
	std::cout << size << " elements with std::" + name;
	std::cout << " : " << time << " us" << std::endl;
}
static int	inputError(std::string msg = "")	{
	msg = msg.empty()? "Error" : "Error: " + msg;
	std::cout << msg << std::endl;
	return (1);
}
	
int	main(int argc, char **argv)	{
	std::vector<int>	v;
	std::deque<int>		d;

	if (argc < 2)
		return (0);
	while (*(++argv))	{
		int n = toPositiveInt(*argv);
		if (n < 0)
			//return inputError(*argv);
			return inputError();
		else	{
			v.push_back(n);
			d.push_back(n);
		}
	}
	std::cout << "Before: ";
	printOut(v);
	std::time_t	t1, t2;
	t1 = mergeInsertionSort(v, 0, v.size() - 1);
	t2 = mergeInsertionSort(d, 0, d.size() - 1);
	std::cout << "After: ";
	printOut(v);
	printInfo(v.size(), "vector", t1);
	printInfo(d.size(), "deque", t2);
	return (0);
}
