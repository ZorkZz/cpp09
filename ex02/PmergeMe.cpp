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
	for (int i = 1; i < ac; i++)
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

std::vector<unsigned int>	add_elements_vector(int const ac, char const **av)
{
	std::vector<unsigned int>	vector;

	for (int i = 1; i < ac; i++)
	{
		vector.push_back(std::atoi(av[i]));
	}
	return (vector);
}

std::deque<unsigned int>	add_elements_deque(int const ac, char const **av)
{
	std::deque<unsigned int>	deque;

	for (int i = 1; i < ac; i++)
	{
		deque.push_back(std::atoi(av[i]));
	}
	return (deque);
}

std::deque<unsigned int> DequeSort(std::deque<unsigned int> Deque)
{
	DequePair PairDeque;
	size_t	i = 0;
	unsigned int		nb0;
	unsigned int		nb1;
	bool	isodd = false;

	for (std::deque<unsigned int>::iterator it = Deque.begin(); it != Deque.end(); it++)
	{
		if (Deque.size() == i + 1 && i % 2 == 0)
		{
			isodd = true;
			nb1 = *it;
		}
		else if (i % 2 != 0)
			nb1 = *it;
		else
			nb0 = *it;
		i++;
		if ((i % 2 == 0 || i == Deque.size()) || (i % 2 == 0 && Deque.size() != i && isodd == false))
			PairDeque.push_back(std::pair<unsigned int, unsigned int>(nb0, nb1));
	}
	Deque.clear();
	for(DequePair::iterator it = PairDeque.begin(); it != PairDeque.end(); it++)
	{
		if (it->first > it->second)
		{
			std::pair<unsigned int, unsigned int> MyPair;
			unsigned int	save;
			MyPair = *it;
			save = MyPair.first;
			MyPair.first = MyPair.second;
			MyPair.second = save;
			PairDeque.erase(it);
			PairDeque.push_back(MyPair);
			it = PairDeque.begin();
		}
	}
	PairDeque = Recursiv(PairDeque);
	Deque.push_back(PairDeque[0].first);
	for (DequePair::iterator it = PairDeque.begin(); it != PairDeque.end(); it++)
		Deque.push_back(it->second);
	size_t	index = 2;
	size_t	nb = 2;
	size_t	temp = index;
	unsigned int		count = index;

	for (size_t	i = 1; i < PairDeque.size(); i++)
	{
		std::deque<unsigned int>::iterator it = Deque.begin();
		if (count == 0)
		{
			index = pow(2, nb) - index;
			nb++;
			count = index;
		}
		else
			count--;
		if (index > Deque.size())
			index = Deque.size() - 1;
		temp = index;
		while (temp < Deque.size() && temp != 0)
		{
			if (PairDeque[i].second <= Deque[temp] && PairDeque[i].second >= Deque[temp - 1])
			{
				Deque.insert(it + (temp), PairDeque[i].second);
				break;
			}
			else if (PairDeque[i]. second <= Deque[temp - 1])
				temp--;
			else
				temp++;
			if (temp == 0)
				Deque.insert(it, PairDeque[i].second);
		}
	}
	if (isodd == true)
	{
		std::deque<unsigned int>::iterator it = std::lower_bound(Deque.begin(), Deque.end(), nb1);
		Deque.insert(it, nb1);
	}
	return (Deque);
}

std::vector<unsigned int>	VectorSort(std::vector<unsigned int> Vector)
{
	VectorPair PairVector;
	size_t	i = 0;
	unsigned int		nb0;
	unsigned int		nb1;
	bool				isodd = false;

	for (std::vector<unsigned int>::iterator it = Vector.begin(); it != Vector.end(); it++)
	{
		if (Vector.size() == i + 1 && i % 2 == 0)
		{
			isodd = true;
			nb1 = *it;
		}
		else if (i % 2 != 0)
			nb1 = *it;
		else
			nb0 = *it;
		i++;
		if ((i % 2 == 0 || i == Vector.size()) || ( i % 2 == 0 && Vector.size() != i && isodd == false))
			PairVector.push_back(std::pair<unsigned int, unsigned int>(nb0, nb1));
	}
	Vector.clear();
	for(VectorPair::iterator it = PairVector.begin(); it != PairVector.end(); it++)
	{
		if (it->first > it->second)
		{
			std::pair<unsigned int, unsigned int> MyPair;
			unsigned int	save;
			MyPair = *it;
			save = MyPair.first;
			MyPair.first = MyPair.second;
			MyPair.second = save;
			PairVector.erase(it);
			PairVector.push_back(MyPair);
			it = PairVector.begin();
		}
	}
	PairVector = Recursiv(PairVector);
	Vector.push_back(PairVector[0].first);
	for (VectorPair::iterator it = PairVector.begin(); it != PairVector.end(); it++)
		Vector.push_back(it->second);
	size_t	index = 2;
	size_t	nb = 2;
	size_t	temp = index;
	unsigned int		count = index;

	for (size_t	i = 1; i < PairVector.size(); i++)
	{
		std::vector<unsigned int>::iterator it = Vector.begin();
		if (count == 0)
		{
			index = pow(2, nb) - index;
			nb++;
			count = index;
		}
		else
			count--;
		if (index > Vector.size())
			index = Vector.size() - 1;
		temp = index;
		while (temp < Vector.size() && temp != 0)
		{
			if (PairVector[i].second <= Vector[temp] && PairVector[i].second >= Vector[temp - 1])
			{
				Vector.insert(it + (temp), PairVector[i].second);
				break;
			}
			else if (PairVector[i]. second <= Vector[temp - 1])
				temp--;
			else
				temp++;
			if (temp == 0)
				Vector.insert(it, PairVector[i].second);
		}
	}
	if (isodd == true)
	{
		std::vector<unsigned int>::iterator it = std::lower_bound(Vector.begin(), Vector.end(), nb1);
		Vector.insert(it, nb1);
	}
	return (Vector);
}

template <typename T>
void MergeSort(T &arr, T &temp, int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		MergeSort(arr, temp, left, mid);
		MergeSort(arr, temp, mid + 1, right);
		Merge(arr, temp, left, mid, right);
	}
}

template <typename T>
void Merge(T& arr, T& temp, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {
		if (arr[i].second <= arr[j].second) {
			temp[k++] = arr[i++];
		} else {
			temp[k++] = arr[j++];
		}
	}

	while (i <= mid) {
		temp[k++] = arr[i++];
	}

	while (j <= right) {
		temp[k++] = arr[j++];
	}

	for (int l = left; l <= right; ++l) {
		arr[l] = temp[l];
	}
}

template <typename T>
T	Recursiv(T Content)
{
	if (Content.size() <= 1)
		return Content;

	T temp(Content.size());
	MergeSort(Content, temp, 0, Content.size() - 1);
	return (Content);
}


void	LaunchSorting(int const ac, char const **av)
{
	std::vector<unsigned int>	vector;
	std::deque<unsigned int>		deque;
	double				VectorTime;
	double				DequeTime;
	Time				MyTime;

	vector = add_elements_vector(ac, av);
	deque = add_elements_deque(ac, av);

	std::cout << "Before: ";
	for (std::vector<unsigned int>::iterator it = vector.begin(); it != vector.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	MyTime.vector_clock();
	vector = VectorSort(vector);
	MyTime.start_clock();
	VectorTime = (MyTime.get_start() - MyTime.get_vector());

	MyTime.deque_clock();
	deque = DequeSort(deque);
	MyTime.start_clock();
	DequeTime = (MyTime.get_start() - MyTime.get_deque());

	std::cout << "After: ";
	for (std::deque<unsigned int>::iterator it = deque.begin(); it != deque.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "time to process a range of " << ac - 1 << " elements  witch std::vector<unsigned int> " << VectorTime << " us" << std::endl;
	std::cout << "time to process a range of " << ac - 1 << " elements  witch std::deque<unsigned int> " << DequeTime << " us" << std::endl;
}
