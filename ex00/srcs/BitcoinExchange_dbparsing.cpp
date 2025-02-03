#include "../includes/BitcoinExchange.hpp"

status_t BitcoinExchange::parse_inner_db(std::map<int, float> &inner_db)
{
	std::ifstream infile("data.csv", std::ios::in);
	if (!infile)
		return (PARSING_FAILURE);
	
	string header;
	string date;
	string value;
	string line;

	int d;
	float v;
	
	std::getline(infile, header);
	if (header != "date,exchange_rate")
	{
		infile.close();
		return (PARSING_FAILURE);
	}
	while (infile)
	{
		std::getline(infile, line);
		if (line.empty())
			continue;
		if (line.size() < 12)
		{
			infile.close();
			return (PARSING_FAILURE);
		}
		for (size_t i = 0; i < 10; ++i)
		{
			date += line[i];
		}
		d = this->convertDate(date.c_str());
		if (line[10] != ',' || status_ != PARSING_SUCCESS)
		{
			infile.close();
			return (PARSING_FAILURE);
		}
		for (size_t i = 11; i < line.size(); ++i)
		{
			value += line[i];
		}
		v = this->parseFloat(value.c_str());
		if (status_ == PARSING_SUCCESS)
			inner_db[d] = v;
		else
		{
			infile.close();
			return (PARSING_FAILURE);
		}
		date.erase();
		value.erase();
	}
	infile.close();
	return (PARSING_SUCCESS);
}

status_t BitcoinExchange::parse_outter_db(const char *filename, std::map<int, float> &db)
{
	std::ifstream infile(filename, std::ios::in);
	if (!infile)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (PARSING_FAILURE);
	}
	string header;
	string date;
	string value;
	string line;

	int d;
	float v;

	std::getline(infile, header);
	if (header != "date | value")
		std::cerr << "Error: bad header => " << header << std::endl;
	status_ = PARSING_SUCCESS;
	while (infile)
	{
		std::getline(infile, line);
		if (line.empty())
			continue;
		if (line.length() < 14 && status_ == PARSING_SUCCESS)
			status_ = BAD_INPUT;
		retrieve_date(line, date);		
		parse_date(date, d);
		if ((line[10] != ' ' || line[11] != '|' || line[12] != ' ') && status_ == PARSING_SUCCESS)
			status_ = BAD_INPUT;
		retrieve_value(line, value);
		parse_value(value, v);
		if (status_ != PARSING_SUCCESS)
			this->errMsg(line);
		else
		{
			if (!UNITS)
				std::cout << date << " => " << value << " = " << find_value(d, db) * v << std::endl; 
			else
				std::cout << date << " => " << "\033[38;5;226m" + value +  " btc\033[0m = " << "\033[5;32m" << find_value(d, db) * v << " $\033[m" << std::endl; 
				
		}
		date.erase();
		value.erase();
		status_ = PARSING_SUCCESS;
	}
	infile.close();
	return (PARSING_SUCCESS);
}
