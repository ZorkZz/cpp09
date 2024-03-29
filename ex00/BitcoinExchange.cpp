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

std::map<std::string, double>	BitcoinExchange::get_data_map() const
{
	return (_data_map);
}



bool	BitcoinExchange::read_input(const std::string &input)
{
	std::ifstream	InputFile(input.c_str(), std::ios::binary);
	std::string		line, date, value;
	std::size_t		pos;
	double			number_of_bitcoin;

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
			if (value.size() > 1 && value[0] == ' ')
				value = value.substr(1);
			if (check_number(value) == true && check_date(date) == true && std::strtof(value.c_str(), NULL) > 0)
			{
				number_of_bitcoin = std::strtod(value.c_str(), NULL);
				if (number_of_bitcoin <= 1000 )
					std::cout << date << " => " << value << " = " << number_of_bitcoin * search_value_in_data(date) << std::endl;
				else
					std::cout << "Error: too large a number." << std::endl;
			}
			else if (std::strtof(value.c_str(), NULL) > 0)
				std::cout << "Error: bad input => " << date << std::endl;
			else
				std::cout << "Error: not a positive number." << std::endl;
		}
		else if (line != "date | value" && pos == std::string::npos)
		{
			date = line;
			std::cout << "Error: bad input => " << date << std::endl;

		}
	}
	return (true);
}

bool	BitcoinExchange::check_number(const std::string &value)
{
	try
	{
		std::strtof(value.c_str(), NULL);
		if (value.find_first_not_of("0123456789") != std::string::npos)
			return (false);
	}
	catch(const std::exception& e)
	{
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::check_date(const std::string &date)
{
	int					year, month, day;
	char				sep0, sep1;
	std::istringstream	date_to_sep(date);

	if (date.length() != 10)
		return (false);
	date_to_sep >> year >> sep0 >> month >> sep1 >> day;
	if (date_to_sep.fail() || sep0 != '-' || sep1 != '-' || year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	bool	is_leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 100 == 0);
	if ((month == 2 && (is_leap ? day > 29 : day > 28)) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
		return (false);
	return (true);
}

void	BitcoinExchange::read_data()
{
	std::ifstream	DataFile("data.csv", std::ios::binary);
	std::string		line;
	std::string		date;
	double			value;
	std::size_t		pos;

	if (!DataFile.is_open())
	{
		std::cout << "fail to open" << std::endl;
		throw (std::exception());
	}
	while (std::getline(DataFile, line, '\n'))
	{
		pos = line.find(',');
		if (line != "date,exchange_rate" && pos != std::string::npos)
		{
			date = line.substr(0, pos);
			value = std::strtod(line.substr(pos + 1).c_str(), NULL);
			_data_map.insert(std::make_pair(date, value));
		}
	}
	DataFile.close();
}

double	BitcoinExchange::search_value_in_data(const std::string &key)
{
	std::map<std::string, double>::iterator it = _data_map.find(key);
	if(it == _data_map.end())
	{
		std::string	prev_day = move_day(key);
		return (search_value_in_data(prev_day));
	}
	return (it->second);
}

std::string	BitcoinExchange::search_key_in_data(const std::string &key)
{
	std::map<std::string, double>::iterator it = _data_map.find(key);
	if(it == _data_map.end())
	{
		std::string	prev_day = move_day(key);
		return (search_key_in_data(prev_day));
	}
	return (it->first);
}

std::string	BitcoinExchange::move_day(const std::string &date)
{
	std::map<std::string, double>::iterator it = _data_map.lower_bound(date);
	if (it == _data_map.end())
		return ("2022-03-29");
	if (it != _data_map.end() && date.compare(it->first) != 0 && it != _data_map.begin())
		it--;
	return (it->first);
}
