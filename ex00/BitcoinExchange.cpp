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
		_input_map = btc.get_input_map();
	}
	return (*this);
}

std::map<std::string, std::string>	BitcoinExchange::get_data_map() const
{
	return (_data_map);
}

std::map<std::string, std::string>	BitcoinExchange::get_input_map() const
{
	return (_input_map);
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
			date = line.substr(0, pos);
			value = line.substr(pos + 1);
			_input_map.insert(std::make_pair(date, value));
			std::cout << date << "=>" << value << std::endl;
		}
		else if (line != "date | value" && pos == std::string::npos)
		{
			date = line;
			_input_map.insert(std::make_pair(date, "Error: bad input"));
			std::cout << date << "=>" << "value" << std::endl;

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
void	BitcoinExchange::search_in_data()
{
	// std::map<std::string, std::string>	save_data(_data_map);
	std::map<std::string, std::string>	save_input = _input_map;
	size_t	i = 0;

	for(std::map<std::string, std::string>::iterator it = save_input.begin(); it != save_input.end(); ++it)
	{
		std::cout << it->first << "=> " << save_input[it->first] << " " << i++ << std::endl;
	}
}