# include "BitcoinExchange.hpp"

Btc::Btc(void){};
Btc::Btc(Btc const &src)	{
	this->_data = src._data;
}
Btc &	Btc::operator=(Btc const &rhs)	{
	if (this == &rhs)
		return (*this);
	this->_data = rhs._data;
	return (*this);
}
Btc::~Btc(void)	{}

/*could use line variable instead of second s(s2), left for readability*/
Btc::Btc(char const *data)	{
	std::ifstream	ifs(data);
	if (!ifs.is_open())
		throw (std::range_error("Could not access the database"));
	std::string line;
	while(std::getline(ifs, line))	{
		if (line.empty())
			continue ;	
		std::size_t f = line.find(',');
		if (f == std::string::npos)	{
			ifs.close();
			throw (std::range_error("Database corrupted"));
		}
		std::string s1 = line.substr(0, f);
		std::string s2 = line.substr(f + 1);
//		std::cout << s1<<"|s1 ;" << s2 <<"|s2" << std::endl;
//if (!s1.empty() && !s2.empty())	{
		s1 = trim(s1, " ,");
		s2 = trim(s2, " ,");
//}
		if (!s1.empty() && !s2.empty())
			_data[s1] = s2;
		else	{
			ifs.close();
			throw (std::range_error("Database corrupted"));
		}
	}
	ifs.close();
//	std::map<std::string, std::string>::iterator it = _data.begin();
	// for (; it != _data.end(); it++)	{
	// 	std::cout << it->first << ": " << it->second << std::endl;
	// }
}
static void inputError(std::string const &msg)	{
	std::cerr << "Error: bad input => " + msg << std::endl;
}

static void valueError(std::string const &msg)	{
	std::cerr << "Error: " + msg << std::endl;
}
static bool	formatOk(std::string const &s)	{
	if (s.length() != 10)
		return false;
	if (s[4] != '-' || s[7] != '-')
		return false;
	for (int i = 0; i < 10; i++)	{
		if (i == 4 || i == 7)
			continue ;
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	struct tm *timeinfo;
	time_t	rawtime;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = atoi(s.substr(0, 4).c_str()) - 1900;
	timeinfo->tm_mon = atoi(s.substr(5, 7).c_str()) - 1;
	timeinfo->tm_mday = atoi(s.substr(8).c_str());
	if (mktime(timeinfo) == -1)
		return false;
	return true;
}
void	Btc::run(std::ifstream &ifs) const	{
	std::string line;
	std::getline(ifs, line);
	while(std::getline(ifs, line))	{
		if (line.empty())
			continue ;	
		std::size_t f = line.find('|');
		if (f == std::string::npos)	{
			inputError(line);
			continue ;
		}
		std::string s1 = line.substr(0, f);
		std::string s2 = line.substr(f + 1);
//		std::cout << s1<<"|s1 ;" << s2 <<"|s2" << std::endl;
//if (!s1.empty() && !s2.empty())	{
		s1 = trim(s1, " ");
		s2 = trim(s2, " ");
//}
		if (s1.empty() || s2.empty())	{
			inputError(line);
			continue ;
		}
		double amount = atof(s2.c_str());
//		std::cout << amount << std::endl;
		if (amount < 0 || amount > 1000)	{
			if (amount < 0)
				valueError("not a positive number");
			else
				valueError("number larger than 1000");
			continue ;
		}
		try		{
			double price = atof(_data.at(s1).c_str());
			std::cout << s1 << " => " << s2 << " = ";
			std::cout << amount * price << std::endl;
		}
		catch(...)		{
			if (formatOk(s1))
				valueError("no information in database");
			else
				inputError(s1);
		}
	}

}
	
std::string trim(std::string &s, char const *c)	{
	std::size_t	first = s.find_first_not_of(c);
	if (first == std::string::npos)
		return("");
	std::size_t last = s.find_last_not_of(c);
	return (s.substr(first, last - first + 1));
}
