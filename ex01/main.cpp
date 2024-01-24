#include "RPN.hpp"

int	main(int ac, char **av)
{
	RPN	rpn;
	RPN	rpn2(rpn);

	if (ac != 2)
			return (1);
	const std::string	param(av[1]);
	if (rpn.set_list(param) == false)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	if (rpn.verif_input() == false)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	rpn.operate();
	std::cout << rpn.get_numbers().front() << std::endl;
	return (0);
}