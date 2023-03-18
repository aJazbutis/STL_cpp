#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <fstream>
# include <exception>
# include <map>
# include <stdlib.h>
# include <ctime>
# include <string>

#define DIGITS	"0123456789."
//#define DATABASE	"src/data.csv"
//#define DATABASE	"../cpp_09/data.csv"
#define DATABASE "data/data.csv"
class	Btc	{
	private:
		std::map<std::string, std::string>	_data;
		Btc(void);
		Btc(Btc const &src);
		Btc	& operator=(Btc const &rhs);
		bool	numberFormatOk(std::string const &s) const;
		bool	dateFormatOk(std::string const &s) const;
	public:
		Btc(char const *data);
		~Btc(void);
		void	run(std::ifstream & fs);
};

std::string trim(std::string &s, char const *c);
/*std::map printer*/
template <class T>
void	printOutMap(T &t)	{
	typename T::const_iterator it = t.begin();
	for (; it != t.end(); it++)	{
	 	std::cout << it->first << "->" << it->second << std::endl;
	}
}
#endif
