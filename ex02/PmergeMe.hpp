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
#include <cmath>
#include <algorithm>


typedef	std::vector<std::pair<unsigned int, unsigned int> > VectorPair;
typedef	std::deque<std::pair<unsigned int, unsigned int> > DequePair;

struct ComparePairsBySecond {
    bool operator()(const std::pair<unsigned int, unsigned int>& a, const std::pair<unsigned int, unsigned int>& b) {
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

template <typename T>
void MergeSort(T &arr, T &temp, int left, int right);

template <typename T>
void Merge(T& arr, T& temp, int left, int mid, int right);

template <typename T>
T	Recursiv(T Content);

std::vector<unsigned int>	VectorSort(std::vector<unsigned int> Vector);
std::deque<unsigned int>	DequeSort(std::deque<unsigned int> Deque);
void	LaunchSorting(int const ac, char const **av);
bool	CheckNumbers(int const ac, char const **av);

#endif