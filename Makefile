NAME	=	philo

CC	=	gcc
FLAGS	= -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread

SRC = main.c \
	init.c \
	utils.c \
	error.c \
	routine.c \
	exit.c \
	death_checker.c \
	checker_args.c

.c.o :
	$(CC) -c $(SRC)

OBJS = $(SRC:.c=.o)

$(NAME)	: $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -rf $(OBJS)


fclean : clean
	rm -rf $(NAME)

re : fclean all
