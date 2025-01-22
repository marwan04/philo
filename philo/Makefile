NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCDIR = srcs
OBJDIR = obj

RM = rm -rf

SRC_FILES = main.c utils.c init.c errors.c simulate.c routine_check.c

SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

${NAME}: ${OBJ}
	 ${CC} ${CFLAGS} $^ -o $@
	 
$(OBJDIR)/%.o: $(SRCDIR)/%.c  | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	 
clean:
	${RM} $(OBJDIR)

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
