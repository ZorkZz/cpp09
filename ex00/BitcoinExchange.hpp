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
		std::map<std::string, std::string>get_input_map() const;
		void	read_data();
		bool	read_input(std::string &input);
		void	search_in_data();

	private:
	//changer map par multimap
		std::map<std::string, std::string>	_data_map;
		std::map<std::string, std::string>	_input_map;
};

#endif