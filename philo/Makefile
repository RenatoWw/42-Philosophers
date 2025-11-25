NAME = philo
SRCS = philo.c \
		utils.c \
		forks.c \
		time.c \
		routine.c

CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -pthread
OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re