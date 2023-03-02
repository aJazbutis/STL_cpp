#pragma once

# include <iostream>
# include <stack> 
# include <cctype>

class	Rpn	{
	private:
		std::string	input;
		std::stack<int>	result;
		Rpn(void);
		Rpn(Rpn const & src);
		Rpn & operator=(Rpn const & rhs);
	public:
		Rpn(std::string input);
		~Rpn(void);
		int	calculate(void);
};
