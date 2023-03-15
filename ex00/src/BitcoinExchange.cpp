#include "BitcoinExchange.hpp"

/*cannonical*/
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

Btc::Btc(char const *data)	{
	std::ifstream	ifs(data);
	if (!ifs.is_open())
		throw (std::range_error("Could not access the database"));
	std::string line;
	std::getline(ifs, line);
	while(std::getline(ifs, line))	{
		line = trim(line, " \t\r\v");
		if (line.empty())
			continue ;	
		std::size_t f = line.find(',');
		if (f == std::string::npos)	{
			ifs.close();
			throw (std::range_error("Database corrupted: " + line));
		}
		std::string s1 = line.substr(0, f);
		std::string s2 = line.substr(f + 1);
		s1 = trim(s1, " ,\t\r\v");
		s2 = trim(s2, " ,\t\r\v");
		if (!s1.empty() && !s2.empty() && dateFormatOk(s1) && numberFormatOk(s2))
			_data[s1] = s2;
		else	{
			ifs.close();
			throw (std::range_error("Database corrupted: " + line));
		}
	}
	ifs.close();
//std::cout << _data.size() << std::endl;
//printOutMap(_data);
}
static void inputError(std::string const &msg)	{
	std::cout << "Error: bad input => " + msg << std::endl;
}

static void valueError(std::string const &msg)	{
	std::cout << "Error: " + msg << std::endl;
}

bool	Btc::numberFormatOk(std::string const &s) const	{
	if (s.find_first_of(".") != s.find_last_of("."))
		return false;
	std::size_t f = s.find_first_not_of(DIGITS);
	if (f != 0 && f != std::string::npos)
		return false;
	if (!f)	{
		if (s[f] == '+' || s[f] == '-')
			return true;
		return false;
	}
	return true;
}
bool	Btc::dateFormatOk(std::string const &s)	const	{
	if (s.length() > 10 || s.length() < 7)
		return false;
	/*bit overkill*/
	int i = 0;
	std::string::const_reverse_iterator it = s.rbegin();
	for (; it < s.rend(); it++)	{
		switch (i)	{
			case 2:
			case 5:
				if (*it != '-')
					return false;
				break ;
			default:
				if (*it < '0' || *it > '9')
					return false;
		}
		i++;
	}
	std::tm	timeinfo = {};
	strptime(s.c_str(), "%Y-%m-%d", &timeinfo);
	int year = timeinfo.tm_year + 1900;
	int month = timeinfo.tm_mon + 1;
	int day	= timeinfo.tm_mday;
	int daysInMonth = 28;
//	std::cout << year << " " << month << " " << day << std::endl;
	if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	switch (month)	{
		case 2:
			/*1700, 1800, 1900, 2100, 2200, 2300, 2500, 2600 not leap years */
			if (!(year % 4) && (year % 100 || !(year % 400)))
				daysInMonth = 29;
			break ;
		case 4:
		case 6:
		case 9:
		case 11:
			daysInMonth = 30;
			break ;
		default:
			daysInMonth = 31;	
	}
	return day <= daysInMonth;
}
static std::string	removeTrailingZero(double n)	{
	std::stringstream	ss;
	ss << std::fixed << std::setprecision(2) << n;
	std::string 		s = ss.str();
	if (s.find('.') != std::string::npos)	{
		s = s.substr(0, s.find_last_not_of('0') + 1);
	}
	if (s[s.length() - 1] == '.')
		s = s.substr(0, s.length() - 1);
	return s;
}
void	Btc::run(std::ifstream &ifs)	const{
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
		s1 = trim(s1, " \t");
		s2 = trim(s2, " \t");
		if (s1.empty() || s2.empty())	{
			inputError(line);
			continue ;
		}
		if (!numberFormatOk(s2))	{
			inputError(s2);
			continue ;
		}
		double amount = atof(s2.c_str());
		if (amount < 0 || amount > 1000)	{
			if (amount < 0)
				valueError("not a positive number.");
			else
				valueError("too large number.");
			continue ;
		}
		try		{
			double price = atof(_data.at(s1).c_str());
			std::cout << s1 << " => " << s2 << " = ";
			std::cout << removeTrailingZero(amount * price) << std::endl;	
		}
		catch(...)		{
			if (dateFormatOk(s1))
				valueError("no information in database => " + s1);
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
