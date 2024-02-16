#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <exception>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <deque>
#include <utility>
#include <algorithm>


typedef	std::vector<std::pair<int, int> > VectorPair;

struct ComparePairsBySecond {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    }
};

class Time
{
	public:
		Time();
		~Time();
		void	start_clock();
		void	vector_clock();
		void	deque_clock();
		clock_t	get_start() const;
		clock_t	get_vector() const;
		clock_t	get_deque() const;

	private:
		clock_t	_start;
		clock_t	_vector;
		clock_t	_deque;
};

void	VectorSort(std::vector<int> Vector);
void	DequeSort(std::deque<int> Deque);
void	LaunchSorting(int const ac, char const **av);
bool	CheckNumbers(int const ac, char const **av);

#endif