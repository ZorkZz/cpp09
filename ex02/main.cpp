#include "PmergeMe.hpp"

int	main(int const ac, char const **av)
{
	if (ac < 2 || CheckNumbers(ac, av) == false)
		return (1);
	LaunchSorting(ac, av);
	return (0);
}