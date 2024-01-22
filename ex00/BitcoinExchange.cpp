#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &btc)
{
	*this = btc;
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &btc)
{
	if (this != &btc)
	{
		_data_map = btc.get_data_map();
	}
	return (*this);
}

std::map<std::string, std::string>	BitcoinExchange::get_data_map() const
{
	return (_data_map);
}



bool	BitcoinExchange::read_input(std::string &input)
{
	std::ifstream	InputFile(input.c_str(), std::ios::binary);
	std::string		line;
	std::string		date;
	std::string		value;
	std::size_t		pos;

	if (!InputFile.is_open())
	{
		std::cout << "Error: file don't exist" << std::endl;
		return (false);
	}
	while (std::getline(InputFile, line, '\n'))
	{
		pos = line.find('|');
		if (line != "date | value" && pos != std::string::npos)
		{
			date = line.substr(0, pos - 1);
			value = line.substr(pos + 1);

			std::cout << date << "=>" << value << std::endl;
			std::cout << search_key_in_data(date) << "=>" << search_value_in_data(date) << std::endl << std::endl;
		}
		else if (line != "date | value" && pos == std::string::npos)
		{
			date = line;
			std::cout << date << " =>" << " PARSE ERROR" << std::endl << std::endl;

		}
	}
	return (true);
}

void	BitcoinExchange::read_data()
{
	std::ifstream	DataFile("data.csv", std::ios::binary);
	std::string		line;
	std::string		date;
	std::string		value;
	std::size_t		pos;

	if (!DataFile.is_open())
		std::cout << "fail to open" << std::endl;
	while (std::getline(DataFile, line, '\n'))
	{
		pos = line.find(',');
		if (line != "date,exchange_rate" && pos != std::string::npos)
		{
			date = line.substr(0, pos);
			value = line.substr(pos + 1);
			_data_map.insert(std::make_pair(date, value));
		}
	}
	DataFile.close();
}

//ajouter les exception nb negaifs/overflow/erreurs de parsing style lettre/plusieurs points/mauvaises dates/etc
std::string	BitcoinExchange::search_value_in_data(std::string key)
{
	std::map<std::string, std::string>::iterator it = _data_map.find(key);
	if(it == _data_map.end())
	{
		it = _data_map.lower_bound(key);
	}
	std::cout << it->second << std::endl;
	return (it->second);
}

std::string	BitcoinExchange::search_key_in_data(std::string key)
{
	std::map<std::string, std::string>::iterator it = _data_map.find(key);
	if(it == _data_map.end())
	{
		it = _data_map.lower_bound(key);
	}
	std::cout << it->first << std::endl;
	return (it->first);
}