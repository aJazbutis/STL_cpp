#include "RPN.hpp"

/*uncallable*/
Rpn::Rpn(void) {}
Rpn::Rpn(Rpn const & src): input(src.input), result(src.result){}
Rpn & Rpn::operator=(Rpn const & rhs)	{
	if (this == &rhs)
		return (*this);
	this->input = rhs.input;
	this->result = rhs.result;
	return *this;
}

/*real thing*/
Rpn::Rpn(std::string arg): input(arg)	{
	if (input.find_first_not_of("+-/* 0123456789") != std::string::npos)
		throw std::range_error("non valid symbols.");
	for (std::string::iterator it = input.begin(); it < input.end(); it++)	{
		if (*it == ' ')	{
			input.erase(it);
			it--;
		}
	}
	if (input.empty())
		throw std::range_error("empty input.");
}

Rpn::~Rpn(void) {}

int	Rpn::calculate(void)	{
	std::string::iterator	it = input.begin();	
	for (; it < input.end(); it++)	{
		if (result.size() < 2)	{
			if (isdigit(*it))	
				result.push((*it) - '0');
			else
				throw std::range_error("bad format.");
		}
		else	{
			char	c = *it;
			int b = result.top();
			result.pop();
			int a = result.top();
			result.pop();
			switch (c)	{
				case '+':
					result.push(a + b);
					break;
				case '-':
					result.push(a - b);
					break;
				case '*':
					result.push(a * b);
					break;
				case '/':
					if (!b)
						throw std::range_error("division by zero.");
					result.push(a / b);
					break;
				default:
					throw std::range_error("bad format.");
			}
		}
	}
	if (result.size() > 1)
		throw std::range_error("bad format.");
	return (result.top());
}
