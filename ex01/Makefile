NAME = RPN
SRCS = main.cpp RPN.cpp
FLAGS = -std=c++98 -pedantic -Wall -Wextra -Werror
OBJS = ${SRCS:.cpp=.o}

${NAME}: ${OBJS}
	c++ ${OBJS} ${FLAGS} -o ${NAME}

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
