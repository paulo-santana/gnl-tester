NAME = test

SRC_DIR = ../
BONUS_DIR = ../

MAIN_FILES = main.c \
			 libtest/string.c \
			 libtest/print_errors.c \
			 libtest/diff.c

SRCS_FILES = get_next_line.c \
			 get_next_line_utils.c

BONUS_SRCS_FILES = get_next_line_bonus.c \
				   get_next_line_utils_bonus.c

SRCS = ${addprefix ${SRC_DIR}, ${SRCS_FILES}}
BONUS_SRCS = ${addprefix ${SRC_DIR}, ${BONUS_SRCS_FILES}}

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BUFFER_SIZES = 32 9999 1 10000000

VALGRIND = #valgrind -q --leak-check=full --show-leak-kinds=all

CFLAGS = -Wall -Werror -Wextra #-g #-fsanitize=address

CC = gcc ${CFLAGS}

all: m

m: TEST = Mandatory
m: print_test ${BUFFER_SIZES}

b: TEST = Bonus
b: SRCS := ${BONUS_SRCS}
b: print_test ${BUFFER_SIZES}

%.o: %.c
	${CC} -I${SRC_DIR} -c $< -o $@

print_test:
	@echo ""
	@echo Test: ${TEST}

${BUFFER_SIZES}: BUFFER_SIZE = $@
${BUFFER_SIZES}:
	@echo ""
	@${CC} -I${SRC_DIR} -DBUFFER_SIZE=${BUFFER_SIZE} $% ${MAIN_FILES} ${SRCS} -o ${NAME}
	@ ./${NAME}
	@${VALGRIND} ./${NAME} 1
	@${VALGRIND} ./${NAME} 2
	@${VALGRIND} ./${NAME} 3
	@${VALGRIND} ./${NAME} 4
	@${VALGRIND} ./${NAME} 5
	@${VALGRIND} ./${NAME} 6
	@${VALGRIND} ./${NAME} 7
	@${VALGRIND} ./${NAME} 8
	@${VALGRIND} ./${NAME} 9
	@${VALGRIND} ./${NAME} 10
	@${VALGRIND} ./${NAME} 11

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: ${NAME} ${BUFFER_SIZES} print_test
