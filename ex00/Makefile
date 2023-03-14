CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = btc

SRC = main.cpp BitcoinExchange.cpp

OBJ = ${patsubst ${S_D}%.cpp, ${O_D}%.o, ${addprefix ${S_D}, ${SRC}}}

S_D = src/

O_D = obj/

INC = inc/

all: ${NAME}

${O_D}%.o: ${S_D}%.cpp
	@mkdir -p ./obj
	@${CC} -I${INC} ${CFLAGS} $^ -c -o $@

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} $^ -o $@
	@echo "\033[1;36m${NAME} ready\033[1;0m"

clean:
	@rm -fr ${O_D}
	@echo "\033[1;36m${O_D} removed\033[1;0m"

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[1;36m${NAME} removed\033[1;0m"

re: fclean all

.PHONY: clean fclean all re
