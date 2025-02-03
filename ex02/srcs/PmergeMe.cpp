#include "PmergeMe.hpp"

std::vector<int> mergeSorted(const std::vector<int>& left, const std::vector<int>& right) 
{

    std::vector<int> merged;
    std::vector<int>::const_iterator itL = left.begin();
    std::vector<int>::const_iterator itR = right.begin();

    while (itL != left.end() && itR != right.end()) 
    {
        if (*itL < *itR) 
	{
            merged.push_back(*itL);
            ++itL;
        } else 
	{
            merged.push_back(*itR);
            ++itR;
        }
    }
    while (itL != left.end()) 
    {
        merged.push_back(*itL);
        ++itL;
    }
    while (itR != right.end()) 
    {
        merged.push_back(*itR);
        ++itR;
    }
    return merged;
}

std::vector<int> fordJohnson(std::vector<int>& data)
{
    if (data.size() <= 1) {
        return data;
    }
    if (data.size() == 2) {
        if (data[0] > data[1]) {
            std::swap(data[0], data[1]);
        }
        return data;
    }
    std::vector<int> left(data.begin(), data.begin() + data.size() / 2);
    std::vector<int> right(data.begin() + data.size() / 2, data.end());
    left = fordJohnson(left);
    right = fordJohnson(right);
    std::vector<int> merged = mergeSorted(left, right);
    return merged;
}

void sortVect(std::vector<int> &data)
{
	if (data.size() > 1) 
        data = fordJohnson(data);
}

std::list<int> lmergeSorted(const std::list<int>& left, const std::list<int>& right) 
{
    std::list<int> merged;
    std::list<int>::const_iterator itL = left.begin();
    std::list<int>::const_iterator itR = right.begin();

    while (itL != left.end() && itR != right.end())
    {
        if (*itL < *itR) {
            merged.push_back(*itL);
            ++itL;
        } else {
            merged.push_back(*itR);
            ++itR;
        }
    }

    while (itL != left.end()) 
    {
        merged.push_back(*itL);
        ++itL;
    }

    while (itR != right.end()) 
    {
        merged.push_back(*itR);
        ++itR;
    }

    return merged;
}

std::list<int> lfordJohnson(std::list<int>& data) 
{
    if (data.size() <= 1)
    {
        return data;
    }

    if (data.size() == 2) 
    {
        std::list<int>::iterator it = data.begin();
        int first = *it;
        ++it;
        int second = *it;
        if (first > second) {
            data.clear();
            data.push_back(second);
            data.push_back(first);
        }
        return data;
    }

    std::list<int> left, right;
    std::list<int>::iterator mid = data.begin();
    std::advance(mid, data.size() / 2);
    left.splice(left.begin(), data, data.begin(), mid);
    right.splice(right.begin(), data);

    left = lfordJohnson(left);
    right = lfordJohnson(right);

    std::list<int> merged = lmergeSorted(left, right);
    return merged;
}

void sortList(std::list<int> &data)
{
    if (data.size() > 1) 
        data = lfordJohnson(data);
}

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
		return *this;
	vdata_ = other.vdata_;
	ldata_ = other.ldata_;
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	vdata_ = other.vdata_;
	ldata_ = other.ldata_;
}

PmergeMe::PmergeMe(int argc, char *argv[])
{
	long l;
	int rez;
	char *end;
	errno = 0;
	if (argc < 2)
			criticalErr();
	startTime1_ = clock();
	for (int i = 1; i < argc; ++i)
	{
		l = std::strtol(argv[i], &end, 10);
		if (end == argv[i])
			criticalErr();
		if ((errno = ERANGE && l == LONG_MAX) || l > INT_MAX || (errno != 0 && l == 0))
			criticalErr();
		if ((errno = ERANGE && l == LONG_MIN) || l < INT_MIN || (errno != 0 && l == 0))
			criticalErr();
		if (argv[i] == '\0' || *end != '\0' || l < 0)
			criticalErr();
		rez = static_cast<int> (l);
		vdata_.push_back(rez);
	}
	this->sort1();
	endTime1_ = std::clock();
	this->setTime1();

	//part2
	startTime2_ = clock();
	for (int i = 1; i < argc; ++i)
	{
		l = std::strtol(argv[i], &end, 10);
		if (end == argv[i])
			criticalErr();
		if ((errno = ERANGE && l == LONG_MAX) || l > INT_MAX || (errno != 0 && l == 0))
			criticalErr();
		if ((errno = ERANGE && l == LONG_MIN) || l < INT_MIN || (errno != 0 && l == 0))
			criticalErr();
		if (argv[i] == '\0' || *end != '\0' || l < 0)
			criticalErr();
		rez = static_cast<int> (l);
		ldata_.push_back(rez);
	}
	this->sort2();
	endTime2_ = std::clock();
	this->setTime2();
	this->display(argc, argv);
}

void PmergeMe::sort1()
{
	sortVect(vdata_);
}

void PmergeMe::sort2()
{
	sortList(ldata_);
}

void PmergeMe::display(int argc, char **argv) const
{
	std::cout << "Before:  "; print_argv(argc, argv, 1);
	std::cout << "After:   "; print_container(vdata_, 1);
	std::cout << "Time to process a range of " << vdata_.size() << " elements with std::vector<int> :  " << time1_ << " us" << std::endl;
	std::cout << "Time to process a range of " << ldata_.size() << " elements with std::list<int> :    " << time2_ << " us" << std::endl;
}

void PmergeMe::setTime1()
{

	time1_ = (double)((double)(endTime1_ - startTime1_) / (double)CLOCKS_PER_SEC * (double)1e6);
}

void PmergeMe::setTime2()
{
	time2_ = (double)((double)(endTime2_ - startTime2_) / (double)CLOCKS_PER_SEC * (double)1e6);
}
