#include "PmergeMe.hpp"

Time::Time()
{}

Time::~Time()
{}

void Time::start_clock()
{
	_start = std::clock();
}

void Time::vector_clock()
{
	_vector = std::clock();
}

void Time::deque_clock()
{
	_deque = std::clock();
}

clock_t Time::get_start() const
{
	return (_start);
}

clock_t Time::get_vector() const
{
	return (_vector);
}

clock_t Time::get_deque() const
{
	return (_deque);
}

bool	CheckNumbers(int const ac, char const **av)
{
	for (int i = 2; i < ac; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (false);
		}
		try
		{
			if (std::strtod(av[i], NULL) > 2147483647 || \
				std::strtod(av[i], NULL) < -2147483648)
					return (false);
		}
		catch (const std::invalid_argument &e)
		{
			return (false);
		}
		catch (const std::out_of_range &e)
		{
			return (false);
		}
	}
	return (true);
}

std::vector<int>	add_elements_vector(int const ac, char const **av)
{
	std::vector<int>	vector;

	for (int i = 2; i < ac; i++)
	{
		vector.push_back(std::atoi(av[i]));
	}
	return (vector);
}

std::deque<int>	add_elements_deque(int const ac, char const **av)
{
	std::deque<int>	deque;

	for (int i = 2; i < ac; i++)
	{
		deque.push_back(std::atoi(av[i]));
	}
	return (deque);
}

void	LaunchSorting(int const ac, char const **av)
{
	std::vector<int>	vector;
	std::deque<int>		deque;
	// Time				MyTime;

	vector = add_elements_vector(ac, av);
	deque = add_elements_deque(ac, av);
}