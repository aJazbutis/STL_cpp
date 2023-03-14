#include "BitcoinExchange.hpp"

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
//		std::cout << s1<<"|s1; " << s2 <<"|s2" << std::endl;
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

static bool	numberFormatOk(std::string const &s)	{
	if (s.find_first_not_of(DIGITS) != std::string::npos)
		return false;
	if (s.find_first_of(".") != s.find_last_of("."))
		return false;
/* Linux doesn't recognize std::string::front ?? 
	if (s.front() == '+' || s.front() == '-')	{*/
	if (s[0] == '+' || s[0] == '-')	{
		if (s.find_first_of("+-") != s.find_last_of("+-"))
			return false;
	}
	return true;
}
static bool	dateFormatOk(std::string const &s)	{
	std::tm	timeinfo = {};
	strptime(s.c_str(), "%Y-%m-%d", &timeinfo);
	int year = timeinfo.tm_year + 1900;
	int month = timeinfo.tm_mon + 1;
	int day	= timeinfo.tm_mday;
	int days = 28;
	if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	//std::cout << year << " " << month << " " << day << std::endl;
	switch (month)	{
		case 2:
			/*1700, 1800, 1900, 2100, 2200, 2300, 2500, 2600 not leap years */
			if (!(year % 4) && (year % 100 || !(year % 400)))
				days = 29;
			break ;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break ;
		default:
			days = 31;	
	}
	return day <= days;
}
void	Btc::run(std::ifstream &ifs) const	{
	std::string line;
	std::getline(ifs, line);
std::cout << std::fixed;
	std::cout.precision(2);
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
		if (!numberFormatOk(s2))	{
			inputError(s2);
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
			if (dateFormatOk(s1))
				valueError("no information in database: " + s1);
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
