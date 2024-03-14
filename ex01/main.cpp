#include "RPN.hpp"

int	main(int ac, char **av)
{
	RPN	rpn;
	RPN	rpn2(rpn);

	if (ac != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	const std::string	param(av[1]);
	if (rpn.set_list(param) == false)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		rpn.operate(param);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	if (rpn.get_numbers().size() == 1)
		std::cout << rpn.get_numbers().top() << std::endl;
	else
		std::cout << "Error" << std::endl;
	return (0);
}