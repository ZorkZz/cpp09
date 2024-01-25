#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN &rpn)
{
	*this = rpn;
}

RPN &RPN::operator=(const RPN &rpn)
{
	if (this != &rpn)
	{
		_numbers = rpn.get_numbers();
		_operators = rpn.get_operators();
	}
	return (*this);
}

bool	RPN::set_list(const std::string &param)
{
	size_t	j = 0;

	for (size_t i = 0; i < param.length(); i++)
	{
		if ((param[i] < '0' || param[i] > '9') && (param[i] != ' ' && param[i] != '+' && param[i] != '-' && param[i] != '*' && param[i] != '/'))
			return (false);
	}
	for (size_t i = 0; i < param.length(); i++)
	{
		if (param[i] >= '0' && param[i] <= '9')
		{
			if (j % 2 == 0 && j != 0)
					return (false);
			_numbers.push_back(std::atoi(&param[i]));
			j++;
		}
		else if (param[i] == '+' || param[i] == '-' || param[i] == '*' || param[i] == '/')
		{
			if (j % 2 != 0 || j == 0)
				return (false);
			_operators.push_back(param[i]);
			j++;
		}
	}
	return (true);
}

void RPN::operate()
{
	int	nb0;
	int	nb1;
	int	op;

	while (_numbers.size() != 0)
	{
		nb0 = _numbers.front();
		_numbers.pop_front();
		if (_numbers.size() == 0)
			op = '?';
		if (_numbers.size() != 0)
		{
			nb1 = _numbers.front();
			_numbers.pop_front();
			op = _operators.front();
			_operators.pop_front();
		}
		switch (op)
		{
			case '+':
				_numbers.push_front(nb0 + nb1);
				break;
			case '-':
				_numbers.push_front(nb0 - nb1);
				break;
			case '/':
				_numbers.push_front(nb0 / nb1);
				break;
			case '*':
				_numbers.push_front(nb0 * nb1);
				break;
			default:
				_numbers.push_front(nb0);
				return ;
		}
	}
}

bool RPN::verif_input()
{
	std::list<int>	numbers_check(_numbers);
	std::list<char>	operators_check(_operators);
	size_t			nb_numbers = 0;
	size_t			nb_operators = 0;

	while (nb_numbers < _numbers.size())
	{
		if (numbers_check.front() > 10 || numbers_check.front() < 0)
			return (false);
		numbers_check.pop_front();
		nb_numbers++;
	}
	while (nb_operators < _operators.size())
	{
		operators_check.pop_front();
		nb_operators++;
	}
	if (nb_numbers - 1 != nb_operators)
		return (false);
	return (true);
}


std::list<int> RPN::get_numbers() const
{
	return (_numbers);
}

std::list<char> RPN::get_operators() const
{
	return (_operators);
}
