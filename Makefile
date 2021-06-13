NAME = test

SRC_DIR = ../
BONUS_SRCS_DIR = ../

MAIN_FILES = main.c utils/string.c utils/print_errors.c

SRCS_FILES = get_next_line.c get_next_line_utils.c
BONUS_SRCS_FILES = get_next_line_bonus.c get_next_line_utils_bonus.c

SRCS = ${MAIN_FILES} ${addprefix ${SRC_DIR}, ${SRCS_FILES}}

BONUS_SRCS = ${MAIN_FILES} ${addprefix ${BONUS_SRCS_DIR}, ${BONUS_SRCS_FILES}}

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BUFFER_SIZE = 42

CFLAGS = -Wall -Werror -Wextra -g# -fsanitize=address

CC = gcc ${CFLAGS}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -I${SRC_DIR} ${OBJS} -o ${NAME}

bonus: ${BONUS_OBJS}
	${CC} -I${BONUS_SRCS_DIR} ${BONUS_OBJS} -o ${NAME}

%.o: %.c
	${CC} -I${SRC_DIR} -DBUFFER_SIZE=${BUFFER_SIZE} -c $< -o $@

clean:
	rm -f ${OBJS}
	rm -f ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

run: Makefile ${NAME}
	./${NAME}
