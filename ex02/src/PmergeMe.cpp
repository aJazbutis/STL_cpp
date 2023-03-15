# include "PmergeMe.hpp"

int	toPositiveInt(std::string s)	{
	s = trim(s, " \t\r\n\v");
	if (s.empty())
		return (-1);
	std::size_t f = s.find_first_not_of(DIGITS);
	if (f != std::string::npos && f != 0)
		return (-1);
	else if (f == 0 && s[f] != '+')
		return (-1);
	double n = atof(s.c_str());
	double m = INT_MAX;
	if (n > m)
		return (-1);
	return (atoi(s.c_str()));
}

std::string	trim(std::string &s, char const *c)	{
	std::size_t	first = s.find_first_not_of(c);
	if (first == std::string::npos)
		return("");
	std::size_t last = s.find_last_not_of(c);
	return (s.substr(first, last - first + 1));
}

std::time_t	getTime(void)	{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
//	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); //mili
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec); //micro
}
