#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange	btc;

	if (ac != 2)
	{
		std::cout << "usage ./btc 'arg 1'" << std::endl;
		return (1);
	}
	std::string	input(av[1]);
	try
	{
		btc.read_data();
		btc.read_input(input);
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR" << std::endl;
	}
	
	return (0);
}