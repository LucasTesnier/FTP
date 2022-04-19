##
## EPITECH PROJECT, 2022
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

CC 		= 	gcc

MAIN	=	src/main.c

FILES	=	src/init_ftp.c				\
			src/data_gestion.c			\
			src/socket_function.c		\
			src/utils.c					\
			src/ftp_command.c			\
			src/ftp_basic_command.c		\
			src/ftp_help_command.c		\
			src/ftp_complex_command.c	\
			src/ftp_data_command.c		\
			src/host_parsing.c			\
			src/ftp_file_command.c

SRC 	=	$(MAIN)		\
			$(FILES)

RM 		= 	rm -f

NAME 	= 	myftp

CFLAGS 	= 	-Wall -Werror -I include/

OBJ		=	$(SRC:.c=.o)

T_FILES	=	tests/temp.c

SRC_T	=	$(FILES)	\
			$(T_FILES)

TFLAGS	=	-lcriterion --coverage

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)
	find . -name '*~' -delete -o -name '#*#' -delete -o -name '*.gcno' \
		-delete -o -name -'*.gcdo' -delete -o -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

tests_run: CFLAGS += $(TFLAGS)
tests_run:
	gcc -o $(TEST_NAME) $(SRC_T) $(CFLAGS)
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

dbg: CFLAGS = -g -I include/
dbg: re

.PHONY: all clean fclean re dbg tests_run
