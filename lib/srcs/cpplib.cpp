#include "cpplib.hpp"

// correction
void test(const std::string &testmsg)
{
    static int i;
    std::cout << "\n\033[34m #TEST [" << i << "] : " << testmsg << "\033[0m\n";
    i++;
}

void testOk(bool value)
{
    if (value)
        std::cout << "\033[32m[OK]\033[0m\n";
    else
        std::cout << "\033[31m[KO]\033[0m\n";
}

void cmsg(const std::string &msg)
{
    std::cout << std::endl << "\033[33m[INFO]: " << msg << "\033[0m" << std::endl;
}

// errors
void errLog(const std::string &msg)
{
    std::cerr << "Error: " + msg << std::endl;
}

void	criticalErr()
{
	std::cout << "Error" << std::endl;
	exit(1);
}

void print_argv(int argc, char *argv[], int nl = 0)
{
	for (int i = 1; i < argc; ++i)
	{
		std::cout << argv[i];
		if (i <  argc -1)
			std::cout << " ";
	}
	if (nl)
		std::cout << std::endl;
}
//Parsing
int parseInt(char const *str)
{
	long l;
	int rez;
	char *end;
	errno = 0;

	if (str == NULL)
		throw std::invalid_argument("Null pointer detected");
	l = std::strtol(str, &end, 10);
	if (end == str)
		throw std::invalid_argument("No digits detected");
	if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX || (errno != 0 && l == 0))
		throw std::invalid_argument("Overflow detected");
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN || (errno != 0 && l == 0))
		throw std::invalid_argument("Underflow detected");
	if (*end != '\0')
		throw std::invalid_argument("Non-digit character detected");
	rez = static_cast<int> (l);
	return rez;
}

float parseFloat(char const *str)
{
	double d;
	float rez;
	char *end;
	errno = 0;

	if (str == NULL)
		throw std::invalid_argument("Null pointer detected");
	d = std::strtod(str, &end);
	if (end == str)
		throw std::invalid_argument("No digits detected");
	if ((errno == ERANGE && d == HUGE_VALF))
		throw std::invalid_argument("Overflow detected");
	if ((errno == ERANGE && d != HUGE_VALF))
		throw std::invalid_argument("Underflow detected");
	if (*end != '\0')
		throw std::invalid_argument("Non-digit character detected");
	rez = static_cast<float> (d);
	return rez;
}
