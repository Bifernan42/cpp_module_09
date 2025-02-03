#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include "../../lib/includes/cpplib.hpp"

class PmergeMe
{
	private:
		std::vector<int> vdata_;
		std::list<int> ldata_;
		clock_t startTime1_;
		clock_t startTime2_;
		clock_t endTime1_;
		clock_t endTime2_;
		double time1_;
		double time2_;
	public:
        	PmergeMe();
		PmergeMe &operator=(const PmergeMe &);
		PmergeMe(const PmergeMe &);
		void display(int argc, char *argv[]) const;
		PmergeMe(int argc, char *argv[]);
		void setTime1();
		void setTime2();
		void sort1();
		void sort2();
		~PmergeMe();
};

#endif
