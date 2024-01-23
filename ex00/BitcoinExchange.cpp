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
			if (check_number(value) == true && check_date(date) == true && std::strtof(value.c_str(), NULL) > 0)
			{
				number_of_bitcoin = std::strtod(value.c_str(), NULL) * search_value_in_data(date);
				if (number_of_bitcoin < 2147483648 )
					std::cout << date << " => " << value << " = " << number_of_bitcoin << std::endl;
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
		std::cout << "fail to open" << std::endl;
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
	int					year, month, day, prev_year, prev_month, prev_day;
	char				sep0, sep1;
	std::istringstream	date_to_sep(date);
	std::stringstream	prev_date;

	date_to_sep >> year >> sep0 >> month >> sep1 >> day;
	prev_day = day - 1;
	prev_month = month;
	prev_year = year;
	if (prev_day == 0)
	{
		prev_month--;
		if (prev_month == 0)
		{
			prev_month = 12;
			prev_year--;
			if (prev_year < 2009)
				return ("2009-01-02");
		}
		switch (prev_month)
		{
			case 2:
				if (prev_year % 4 == 0 && (prev_year % 100 != 0 || prev_year % 400 == 0))
					prev_day = 29;
				else
					prev_day = 28;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				prev_day = 30;
				break;
			default:
				prev_day = 31;
		}
	}
	if (prev_year == 2009 && prev_month == 1 && prev_day == 1)
		return ("2009-01-01");
	prev_date << prev_year << "-";
	if (prev_month < 10)
		prev_date << "0";
	prev_date << prev_month << "-";
	if (prev_day)
		prev_date << "0";
	prev_date << prev_day;
	return (prev_date.str());
}
