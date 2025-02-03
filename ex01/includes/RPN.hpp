#ifndef RPN_HPP
# define RPN_HPP
# include "../../lib/includes/cpplib.hpp"
# ifndef DEBBUG
#  define DEBBUG false
#endif

class RPN
{
	private:
		std::stack<long> s_;
	public:
		RPN(const RPN &);
		RPN();
		RPN &operator=(const RPN &);
		RPN(int argc, char *argv[]);
		void compute(char c);
		void parser(const std::string &input);
		~RPN();
};

#endif
