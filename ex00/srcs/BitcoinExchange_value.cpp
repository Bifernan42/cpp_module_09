#include "../includes/BitcoinExchange.hpp"

void BitcoinExchange::retrieve_value(std::string &source, std::string &value)
{
	if (status_ != PARSING_SUCCESS || source.empty())
		return ;
	for (size_t i = 13; i < source.size(); ++i)
	{
		value += source[i];		
	}
}

void BitcoinExchange::parse_value(std::string &value, float &v)
{
	if (status_ != PARSING_SUCCESS || value.empty())
		return ;
	v = this->checkValue(value);
}

float BitcoinExchange::find_value(int key, std::map<int, float> &db)
{
	if (db.find(key) != db.end())
		return db[key];
	
	std::map<int, float>::iterator it;
	for (it = db.begin(); it != db.end(); ++it)
	{
		if (it->first > key)
		{
			if (it != db.begin())
				--it;
			break;
		}
	}
	if (it == db.end())
		it--;

	return it->second;
}

float BitcoinExchange::checkValue(const std::string &value)
{
	float val = this->parseFloat(value.c_str());
	if (val < 0)
		status_ = NEGATIVE; 
	if (val > 1000)
		status_ = OOB;	
	return val;
}

float BitcoinExchange::parseFloat(char const *str)
{
	double d;
	float rez;
	char *end;
	errno = 0;

	if (str == NULL)
		status_ = BAD_INPUT;
	d = std::strtod(str, &end);
	if (end == str)
		status_ = BAD_INPUT;
	if ((errno == ERANGE && d == HUGE_VALF))
		status_ = BAD_INPUT;
	if ((errno == ERANGE && d != HUGE_VALF))
		status_ = BAD_INPUT;
	if (*end != '\0')
		status_ = BAD_INPUT;
	rez = static_cast<float> (d);
	return rez;
}
