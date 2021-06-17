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
BONUS_SRCS = ${MAIN_FILES} ${addprefix ${BONUS_SRCS_DIR}, ${BONUS_SRCS_FILES}}

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BUFFER_SIZES = 32 9999 1 10000000

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

CC = clang ${CFLAGS}

all: run

run: ${BUFFER_SIZES}

%.o: %.c
	${CC} -I${SRC_DIR} -c $< -o $@

${BUFFER_SIZES}: BUFFER_SIZE = $@
${BUFFER_SIZES}:
	${CC} -I${SRC_DIR} -DBUFFER_SIZE=${BUFFER_SIZE} $% ${MAIN_FILES} ${SRCS} -o ${NAME}
	./${NAME}
	@./${NAME} 1
	@./${NAME} 2
	@./${NAME} 3
	@./${NAME} 4
	@./${NAME} 5
	@./${NAME} 6
	@./${NAME} 7
	@./${NAME} 8
	@./${NAME} 9
	@./${NAME} 10

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: ${NAME}
