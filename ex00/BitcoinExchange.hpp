#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &btc);
		BitcoinExchange	&operator=(BitcoinExchange const &btc);
		std::map<std::string, std::string>get_data_map() const;
		void	read_data();
		bool	read_input(std::string &input);
		std::string	search_value_in_data(std::string key);
		std::string	search_key_in_data(std::string key);

	private:
		std::map<std::string, std::string>	_data_map;
};

#endif