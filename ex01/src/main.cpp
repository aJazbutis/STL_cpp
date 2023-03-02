#include "RPN.hpp"

static int	inputError(std::string msg)	{
	std::cerr << "Error: " + msg << std::endl;
	return 1;
}

int	main(int argc, char **argv){
	if (argc != 2)
		return inputError("argument count");
/*int a = 5;
int b = 0;
		std::cout << a/b;*/
/*	std::string	input = argv[1];
	if (input.find_first_not_of("+/-* 0123456789") != std::string::npos)
		return inputError();
	for (std::string::iterator it = input.begin(); it < input.end(); it++)	{
		if (*it == ' ')	{
			input.erase(it);
			it--;
		}
	}
	std::cout << input << std::endl;*/
	try	{
		Rpn rpn(argv[1]);
		std::cout << rpn.calculate() << std::endl;

		return 0;
	}
	catch	(std::exception & e)	{
		return inputError(e.what());
	}
}
