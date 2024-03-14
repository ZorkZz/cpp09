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

std::vector<int>	add_elements_vector(int const ac, char const **av)
{
	std::vector<int>	vector;

	for (int i = 1; i < ac; i++)
	{
		vector.push_back(std::atoi(av[i]));
	}
	return (vector);
}

std::deque<int>	add_elements_deque(int const ac, char const **av)
{
	std::deque<int>	deque;

	for (int i = 1; i < ac; i++)
	{
		deque.push_back(std::atoi(av[i]));
	}
	return (deque);
}

std::deque<int> DequeSort(std::deque<int> Deque)
{
	DequePair PairDeque;
	size_t	i = 0;
	int		nb0;
	int		nb1;

	for (std::deque<int>::iterator it = Deque.begin(); it != Deque.end(); it++)
	{
		if (Deque.size() == i + 1 && i % 2 == 0)
		{
			nb0 = -1;
			nb1 = *it;
		}
		else if (i % 2 != 0)
			nb1 = *it;
		else
			nb0 = *it;
		i++;
		if (i % 2 == 0 || i == Deque.size())
			PairDeque.push_back(std::pair<int, int>(nb0, nb1));
	}
	Deque.clear();
	for(DequePair::iterator it = PairDeque.begin(); it != PairDeque.end(); it++)
	{
		if (it->first > it->second)
		{
			std::pair<int, int> MyPair;
			int	save;
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
	for (DequePair::iterator it = PairDeque.begin(); it != PairDeque.end(); it++)
	{
		if (it->first != -1)
			Deque.push_back(it->second);
	}
	for (DequePair::iterator it = PairDeque.begin(); it != PairDeque.end(); it++)
	{
		if (it->first != -1)
		{
			std::deque<int>::iterator Dend = std::find(Deque.begin(), Deque.end(), it->second);
			std::deque<int>::iterator Dit = std::lower_bound(Deque.begin(), Dend, it->first);
			Deque.insert(Dit, it->first);
		}
		else
		{
			std::deque<int>::iterator Dit = std::lower_bound(Deque.begin(), Deque.end(), it->second);
			Deque.insert(Dit, it->second);
		}
	}
	return (Deque);
}

std::vector<int>	VectorSort(std::vector<int> Vector)
{
	VectorPair PairVector;
	size_t	i = 0;
	int		nb0;
	int		nb1;

	for (std::vector<int>::iterator it = Vector.begin(); it != Vector.end(); it++)
	{
		if (Vector.size() == i + 1 && i % 2 == 0)
		{
			nb0 = -1;
			nb1 = *it;
		}
		else if (i % 2 != 0)
			nb1 = *it;
		else
			nb0 = *it;
		i++;
		if (i % 2 == 0 || i == Vector.size())
			PairVector.push_back(std::pair<int, int>(nb0, nb1));
	}
	Vector.clear();
	for(VectorPair::iterator it = PairVector.begin(); it != PairVector.end(); it++)
	{
		if (it->first > it->second)
		{
			std::pair<int, int> MyPair;
			int	save;
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
	for (VectorPair::iterator it = PairVector.begin(); it != PairVector.end(); it++)
	{
		if (it->first != -1)
			Vector.push_back(it->second);
	}
	for (VectorPair::iterator it = PairVector.begin(); it != PairVector.end(); it++)
	{
		if (it->first != -1)
		{
			std::vector<int>::iterator Vend = std::find(Vector.begin(), Vector.end(), it->second);
			std::vector<int>::iterator Vit = std::lower_bound(Vector.begin(), Vend, it->first);
			Vector.insert(Vit, it->first);
		}
		else
		{
			std::vector<int>::iterator Vit = std::lower_bound(Vector.begin(), Vector.end(), it->second);
			Vector.insert(Vit, it->second);
		}
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
	std::vector<int>	vector;
	std::deque<int>		deque;
	double				VectorTime;
	double				DequeTime;
	Time				MyTime;

	vector = add_elements_vector(ac, av);
	deque = add_elements_deque(ac, av);

	std::cout << "Before: ";
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
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
	for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "time to process a range of " << ac - 1 << " elements  witch std::vector<int> " << VectorTime << " us" << std::endl;
	std::cout << "time to process a range of " << ac - 1 << " elements  witch std::deque<int> " << DequeTime << " us" << std::endl;
}
