NAME = test

SRC_DIR = ../
BONUS_DIR = ../

MAIN_FILES = main.c \
			 utils/string.c \
			 utils/print_errors.c

SRCS_FILES = get_next_line.c \
			 get_next_line_utils.c

BONUS_SRCS_FILES = get_next_line_bonus.c \
				   get_next_line_utils_bonus.c

SRCS = ${addprefix ${SRC_DIR}, ${SRCS_FILES}}
BONUS_SRCS = ${addprefix ${SRC_DIR}, ${BONUS_SRCS_FILES}}

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BUFFER_SIZES = 32 9999 1 10000000 100000000

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

CC = gcc ${CFLAGS}

all: m

m: ${BUFFER_SIZES}

b: SRCS := ${BONUS_SRCS}
b: ${BUFFER_SIZES}

%.o: %.c
	${CC} -I${SRC_DIR} -c $< -o $@

${BUFFER_SIZES}: BUFFER_SIZE = $@
${BUFFER_SIZES}:
	@${CC} -I${SRC_DIR} -DBUFFER_SIZE=${BUFFER_SIZE} $% ${MAIN_FILES} ${SRCS} -o ${NAME}
	@echo ""
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME}
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 1
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 2
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 3
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 4
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 5
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 6
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 7
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 8
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 9
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 10
	@valgrind -q --leak-check=full --show-leak-kinds=all ./${NAME} 11

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: ${NAME}
