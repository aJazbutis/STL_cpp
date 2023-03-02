#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <exception>
# include <map>
# include <stdlib.h>
# include <ctime>

#define DATABASE	"src/data.csv"

class	Btc	{
	private:
		std::map<std::string, std::string>	_data;
		Btc(void);
		Btc(Btc const &src);
		Btc	& operator=(Btc const &rhs); 
	public:
		Btc(char const *data);
		~Btc(void);
		void	run(std::ifstream & fs) const;
};

std::string trim(std::string &s, char const *c);
#endif
