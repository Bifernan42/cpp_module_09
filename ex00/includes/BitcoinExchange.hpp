#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include "../../lib/includes/cpplib.hpp"
# include <iostream>
# include <deque>
# include <vector>
# include <map>
# include <list>
# include <time.h>
#include <sstream>
#include <string>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <climits>
#include <limits>

# ifndef UNITS
#  define UNITS false
# endif

# ifndef LIMIT
#  define LIMIT false
# endif


typedef std::string string;

typedef enum status_e
{
	PARSING_SUCCESS,
	PARSING_FAILURE,
	NEGATIVE,
	BAD_INPUT,
	OOB,
	OK,
	KO,
	EMPTYLINE
} status_t;

class BitcoinExchange
{
	private:
		std::map<int, float> db_;
		status_t status_;
	public:

		//____CONSTRUCTION/DESTRUCTION____//
		BitcoinExchange(char const *outter_db);
		~BitcoinExchange();
		BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &);
		BitcoinExchange(const BitcoinExchange &);

		//_____PARSING_____//
		float parseFloat(char const *str);
		void displayValue() const;
		float find_value(int key, std::map<int, float> &db);
		void retrieve_date(std::string &source, std::string &date);
		void retrieve_value(std::string &source, std::string &value);
		void parse_value(std::string &value, float &v);
		void parse_date(std::string &date, int &d);
		float checkValue(const std::string &value);
		void errMsg(const std::string &line);
		status_t parse_inner_db(std::map<int, float> &inner_db);
		status_t parse_outter_db(const char *filename, std::map<int, float> &db);

		//_____DATE_____//
		int parse_date(std::ifstream &infile, std::string &date);
		int convertDate(const char *date);
		bool isValidDate(const struct tm &tm);
		std::string encodedToString(int encoded_date);
		int encodeDate(const struct tm &tm);

		void printstatus();
};

bool separator_is_comma(const std::string &separator);
bool separator_is_pipe(const std::string &separator);
bool parse_separator(std::ifstream &infile, std::string &separator, bool (*f)(const std::string &));

int parse_date(std::ifstream &infile, std::string &date);
float parse_value(std::ifstream &infile, std::string &value);
int convertDate(const char *date);

/* 12/25/24 */

status_t parse_outter_db(const char *filename, std::map<int, float> &outter_db);
status_t parse_inner_db(std::map<int, float> &inner_db);

#endif
