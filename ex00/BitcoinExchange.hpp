#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map>
#include <fstream>
#include <exception>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &btc);
		BitcoinExchange	&operator=(BitcoinExchange const &btc);
		std::map<std::string, double>get_data_map() const;
		bool	check_number(const std::string &value);
		bool	check_date(const std::string &date);
		void	read_data();
		bool	read_input(const std::string &input);
		double	search_value_in_data(const std::string &key);
		std::string	search_key_in_data(const std::string &key);
		std::string	move_day(const std::string &date);

	private:
		std::map<std::string, double>	_data_map;
};

#endif