#include "BitcoinExchange.hpp"

static int argError(std::string msg = "Could not open file.")	{
	std::cerr << "Error: " + msg << std::endl;
	return (1);
}

int	main(int argc, char **argv)	{
	if (argc == 1)
		return (argError());
	if (argc > 2)
		return argError("Too many arguments.");
	std::ifstream	ifs(argv[1]);
	if (!ifs.is_open())
		return argError();
	try	{
		Btc	btc(DATABASE);
		btc.run(ifs);
	}
	catch	(std::exception &e)	{
		std::cerr << e.what() << std::endl;
	}
	ifs.close();
	return (0);
}
