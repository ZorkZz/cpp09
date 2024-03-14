#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>
#include <stack>
#include <exception>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &rpn);
		RPN	&operator=(const RPN &rpn);
		std::stack<int>	get_numbers() const;
		bool	set_list(const std::string &param);
		void	operate(const std::string &param);

	private:
		std::stack<int>		_toOperate;
};

#endif