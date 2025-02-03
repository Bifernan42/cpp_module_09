#ifndef CPPLIB_HPP
# define CPPLIB_HPP
# include <iostream>
# include <map>
# include <vector>
# include <list>
# include <stack>
# include <deque>
# include <ctime>
# include <cstdlib>
# include <cerrno>
# include <unistd.h>
# include <cmath>
# include <time.h>
# include <climits>
# include <sstream>
# include <cstring>
# include <algorithm>

#define ERRMSG(x) std::cout << "\033[1;97;41m" << x << "\033[0m" << std::endl;

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#define PUTS( x ) std::cout << x << std::endl;

void test(const std::string &testmsg);

void testOk(bool value);

void cmsg(const std::string &msg);

void errLog(const std::string &msg);

void	criticalErr();

//Parse char * to numerics
int parseInt(char const *str);
float  parseFloat(char const *str);

template <class T> void print_container(const T &c, int nl = 0)
{
	for (typename T::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != c.end())
			std::cout << " ";
	}
	if (nl)
		std::cout << std::endl;
}

template <class T> std::string numToString(const T& value)
{
	std::ostringstream oss;
	oss << std::dec << value;
	return oss.str();
}

void print_argv(int argc, char *argv[], int nl);

#endif
