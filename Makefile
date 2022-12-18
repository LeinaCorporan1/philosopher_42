NAME	=	philo

CC	=	gcc
FLAGS	=-Wall -g3 -Wextra -Werror -pthread

SRC = main.c \
	init.c \
	utils.c

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
