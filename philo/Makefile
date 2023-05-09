# NAME	=	philo

# CC	=	gcc
# FLAGS	=-Wall -g3 -Wextra -Werror -pthread

# SRC = main.c \
# 	init.c \
# 	utils.c \
# 	death_checker.c \
# 	checker_args.c \
# 	error.c \
# 	routine.c

# .c.o :
# 	$(CC) -c $(SRC)

# OBJS = $(SRC:.c=.o)

# $(NAME)	: $(OBJS)
# 	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

# all : $(NAME)

# clean :
# 	rm -rf $(OBJS)


# fclean : clean
# 	rm -rf $(NAME)

# re : fclean all


.DEFAULT_GOAL	= all

MAND_SRCS	=	 main.c \
	init.c \
	utils.c \
	death_checker.c \
	checker_args.c \
	error.c \
	routine.c
MAND_SRCDIR	=	src
MAND_PATH	=	$(addprefix $(MAND_SRCDIR)/, $(MAND_SRCS))
MAND_OBJDIR	=	obj
MAND_OBJS	=	$(patsubst $(MAND_SRCDIR)/%, $(MAND_OBJDIR)/%, $(MAND_PATH:.c=.o))

MD_DEP_DIR	=	dep
MAND_DEP	=	$(patsubst $(MAND_OBJDIR)/%.o, $(MD_DEP_DIR)/%.d, $(MAND_OBJS))
MD_HD_DIR	=	inc
MD_HD_PATH	=	$(addprefix $(MD_HD_DIR)/, $(MD_HD_SRCS))
NAME		=	philo
CC			=	gcc
RM			=	rm -f
RMD			=	rm -rvf
MK			=	mkdir -p
DEBUG		=	-g
CFLAGS		=	-Wall -Wextra -Werror
LFLAGS		=	-lpthread
DFLAGS		=	-MMD -MF
all:		$(NAME)

$(NAME):	$(MAND_OBJS)
				$(CC) $(CFLAGS) $(DEBUG) $^ -I$(MD_HD_DIR) $(LFLAGS) -o $@

-include $(MAND_DEP)
$(MAND_OBJDIR)/%.o:		$(MAND_SRCDIR)/%.c | $(MAND_OBJDIR) $(MD_DEP_DIR) $(MD_HD_PATH)
							$(CC) $(CFLAGS) $(DEBUG) $(DFLAGS) $(MD_DEP_DIR)/$*.d -I$(MD_HD_DIR) $(LFLAGS) -c $< -o $@

$(MAND_OBJDIR) $(MD_DEP_DIR):		;
				@$(MK) $@
clean:		;
				@$(RMD) $(MAND_OBJDIR) $(MD_DEP_DIR)

fclean:		clean
				@$(RM) $(NAME)

re:			fclean all
.PHONY:		all clean fclean re bonus