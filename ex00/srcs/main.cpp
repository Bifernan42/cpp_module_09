#include "../includes/BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: could not read file." << std::endl;
		return (1);
	}
	BitcoinExchange software(argv[1]);
	return (0);
}
