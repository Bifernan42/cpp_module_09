#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}
RPN &RPN::operator=(const RPN &other)
{
	if (this == &other)
		return *this;
	s_ = other.s_;
	return *this;
}

RPN::RPN(const RPN &other)
{
	s_ = other.s_;
}


void RPN::parser(const std::string &input)
{	
	std::string num;
	bool space_switch = false;
	if (input.empty())
	{
		criticalErr();
	}
	for (size_t i = 0; i < input.size() ; ++i)
	{
		if (space_switch && !std::isspace(input[i]))
			criticalErr();
		if (std::isdigit(input[i]) || ( i + 1 < input.size() && (input[i] == '+' || input[i] == '-') && std::isdigit(input[i + 1])))
		{
			while (!std::isspace(input[i]) && i < input.size())
			{
				num += input[i];
				i++;
			}
			i--;
			try {
				s_.push(static_cast<long> (parseInt(num.c_str())));
			}
			catch (std::exception &e)
			{
				criticalErr();
			}
			num.erase();
			space_switch = true;
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '/'|| input[i] == '*')
		{	
			compute(input[i]);
			space_switch = true;
		}
		else if (std::isspace(input[i]))
		{
			space_switch = false;
			continue;
		}
		else
			criticalErr();
	}
}

RPN::RPN(int argc, char *argv[])
{
	if (argc != 2)
		criticalErr();
	parser(argv[1]);
	if (s_.size() > 1)
		criticalErr();
	std::cout << s_.top() << std::endl;
}

void RPN::compute(char c)
{
	if (s_.empty() || s_.size() < 2)
	{
		criticalErr();
	}
	long expr1 = s_.top();
	s_.pop();
	long expr2 = s_.top();
	s_.pop();
	if (c == '+')
		s_.push(expr1 + expr2);
	if (c == '-')
		s_.push(expr2 - expr1);
	if (c == '*')
		s_.push(expr1 * expr2);
	if (c == '/')
		s_.push(expr2 / expr1);
}
