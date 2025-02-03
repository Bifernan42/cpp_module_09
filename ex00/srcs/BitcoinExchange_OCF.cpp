#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this == &other)
		return *this;
	db_ = other.db_;
	return *this;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	db_ = other.db_;
}

BitcoinExchange::BitcoinExchange(char const *outter_db)
{
	status_ = PARSING_SUCCESS;
	if ((status_ = this->parse_inner_db(db_)) == PARSING_FAILURE)
	{
		std::cerr << "Error: Fatal: corrupted or missing database" << std::endl;
		exit(1);
	}
	this->parse_outter_db(outter_db, db_);
}
