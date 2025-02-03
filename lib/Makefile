NAME = libcpplib.a
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iincludes -MMD -MP
SRCS = srcs/cpplib.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS) $(DEPS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
