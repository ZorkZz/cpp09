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
		_toOperate = rpn.get_numbers();
	return (*this);
}

bool	RPN::set_list(const std::string &param)
{
	for (size_t i = 0; i < param.length(); i++)
	{
		if ((param[i] < '0' || param[i] > '9') && (param[i] != ' ' && param[i] != '+' && param[i] != '-' && param[i] != '*' && param[i] != '/'))
			return (false);
	}
	for (size_t i = 0; i < param.length(); i++)
	{
		if ((param[i] >= '0' && param[i] <= '9') || param[i] == '+' || param[i] == '-' || param[i] == '*' || param[i] == '/')
		{
			if (std::atoi(&param[i]) < 0 || std::atoi(&param[i]) > 9)
				return (false);
		}
	}
	return (true);
}

void RPN::operate(const std::string &param)
{
	int	nb0 = 0;
	int	nb1 = 0;

	for (size_t	i = 0; i < param.length(); i++)
	{
		if (param[i] >= '0' && param[i] <= '9')
			_toOperate.push(std::atoi(&param[i]));
		else if (param[i] != ' ')
		{
			if (_toOperate.size() < 2)
				throw (std::exception());
			switch (param[i])
			{
				case '+':
					nb0 = _toOperate.top();
					_toOperate.pop();
					nb1 = _toOperate.top();
					_toOperate.pop();
					_toOperate.push(nb1 + nb0);
					break;
				case '-':
					nb0 = _toOperate.top();
					_toOperate.pop();
					nb1 = _toOperate.top();
					_toOperate.pop();
					_toOperate.push(nb1 - nb0);
					break;
				case '*':
					nb0 = _toOperate.top();
					_toOperate.pop();
					nb1 = _toOperate.top();
					_toOperate.pop();
					_toOperate.push(nb1 * nb0);
					break;
				case '/':
					nb0 = _toOperate.top();
					_toOperate.pop();
					nb1 = _toOperate.top();
					_toOperate.pop();
					if (nb0 == 0)
						throw (std::exception());
					_toOperate.push(nb1 / nb0);
					break;
				default:
					throw (std::exception());
			}
		}
	}
}


std::stack<int> RPN::get_numbers() const
{
	return (_toOperate);
}

