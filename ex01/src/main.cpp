#include "RPN.hpp"

/*static int	inputError(std::string msg)	{
	std::cerr << "Error: " + msg << std::endl;
	return 0;
}*/

int	main(int argc, char **argv){
	if (argc != 2)	{
		std::cout << "usage: ./RPN \"e x p r e s i o n\"\n";
		return 0;
	}
	try	{
		Rpn rpn(argv[1]);
		std::cout << rpn.calculate() << std::endl;
	}
	catch	(std::exception & e)	{
		std::cout << "Error" << std::endl;
		//return inputError(e.what());
	}
	return 0;
}
