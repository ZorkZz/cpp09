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
	btc.read_data();
	btc.read_input(input);
	btc.search_in_data();
	return (0);
}