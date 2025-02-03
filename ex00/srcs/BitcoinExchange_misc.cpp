#include "../includes/BitcoinExchange.hpp"

void BitcoinExchange::errMsg(const std::string &line)
{
	if (status_ == PARSING_SUCCESS)
		return ;
	if (status_ == NEGATIVE)
		ERRMSG("Error: not a positive number.")
	if (status_ == BAD_INPUT)
		ERRMSG("Error: bad input => " + line)
	if (status_ == OOB) 
		ERRMSG("Error: too large a number.") 
	if (status_ == EMPTYLINE) 
		std::cerr << "Error: empty line." << std::endl; 
	
}

void	BitcoinExchange::printstatus()
{
	std::string msg;

	if (status_ == PARSING_SUCCESS)
		msg = "PARSING SUCCESS";
	if (status_ == PARSING_FAILURE)
		msg = "PARSING FAILURE";
	if (status_ == NEGATIVE)
		msg = "NEGATIVE FLOAT";
	if (status_ == BAD_INPUT)
		msg = "BAD INPUT";
	if (status_ == OOB)
		msg = "FLOAT TOO LARGE";
	std::cout << "[STATUS] : '" << msg << "'" << std::endl;
}
