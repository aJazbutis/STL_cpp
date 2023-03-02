CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = RPN

SRC = main.cpp RPN.cpp

OBJ = ${patsubst ${S_D}%.cpp, ${O_D}%.o, ${addprefix ${S_D}, ${SRC}}}

S_D = src/

O_D = obj/

INC = inc/

all: ${NAME}

${O_D}%.o: ${S_D}%.cpp
	@mkdir -p ./obj
	${CC} -I${INC} ${CFLAGS} $^ -c -o $@

${NAME}: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm -fr ${O_D}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean fclean all re
