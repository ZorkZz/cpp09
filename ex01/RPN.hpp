#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN &rpn);
		RPN	&operator=(const RPN &rpn);
		std::list<int>	get_numbers() const;
		std::list<char>	get_operators() const;
		void	operate();
		bool	set_list(const std::string &param);
		bool	verif_input();

	private:
		std::list<int>	_numbers;
		std::list<char>	_operators;
};

#endif