NAME = PmergeMe
SRCS = srcs/main.cpp srcs/PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iincludes -MMD -MP
SCRIPT= ../scripts/create_class.sh
LIBDIR = ../lib
SLIB = libcpplib.a
LIBFLAGS = -L$(LIBDIR) -lcpplib
LIBPATH = $(LIBDIR)/$(SLIB)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME) : $(OBJS) $(LIBPATH) 
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

-include $(DEPS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBDIR) clean 	
	@rm -f $(OBJS) $(DEPS)

$(LIBPATH) :
	$(MAKE) -C $(LIBDIR)

fclean : clean
	@$(MAKE) -C $(LIBDIR) fclean 	
	@rm -f $(NAME)

re : fclean all

class :
	chmod +x $(SCRIPT)
	$(SCRIPT)

.PHONY: all clean fclean re class
