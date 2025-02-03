#include "../includes/BitcoinExchange.hpp"

int BitcoinExchange::encodeDate(const struct tm &tm)
{
	int encoded_date;
	encoded_date = (tm.tm_year << 9) | (tm.tm_mon << 5) | tm.tm_mday;
	return encoded_date;
}

std::string BitcoinExchange::encodedToString(int encoded_date)
{
	std::ostringstream oss;
	oss << std::setw(4) << std::setfill('0') << numToString((encoded_date >> 9) + 1900) << "-" << std::setw(2) << std::setfill('0') << numToString(((encoded_date & (15 << 5)) >> 5) + 1) << "-" << std::setw(2) << std::setfill('0') << numToString((encoded_date & 31));
	return oss.str();
}

bool BitcoinExchange::isValidDate(const struct tm &tm)
{
	if (LIMIT)
		return (!(tm.tm_year < 0 || tm.tm_year > 1099 || tm.tm_mon < 0 || tm.tm_mon > 11 || tm.tm_mday < 1 || tm.tm_mday > 31));
	else
		return (!(tm.tm_mon < 0 || tm.tm_mon > 11 || tm.tm_mday < 1 || tm.tm_mday > 31));
		
}

int BitcoinExchange::convertDate(const char *date)
{
	if (!date)
		status_ = BAD_INPUT;
	struct tm tm;
	char *rez;
	rez = strptime(date, "%Y-%m-%d", &tm);
	if (rez == NULL || *rez != '\0' || !isValidDate(tm))
		status_ = BAD_INPUT;
	return (encodeDate(tm));
}

int BitcoinExchange::parse_date(std::ifstream &infile, std::string &date)
{
	date.clear();
	if (!infile || !(infile >> std::setw(10) >> date))
		return -1;
	std::cout << date << std::endl;
	return (convertDate(date.c_str()));
}

void BitcoinExchange::retrieve_date(std::string &source, std::string &date)
{
	if (status_ != PARSING_SUCCESS || source.empty())
		return ;
	for (size_t i = 0; i < 10; ++i)
	{
		date += source[i];		
	}
}


void BitcoinExchange::parse_date(std::string &date, int &d)
{
	if (status_ != PARSING_SUCCESS || date.empty())
		return ;
	d = this->convertDate(date.c_str());
}
