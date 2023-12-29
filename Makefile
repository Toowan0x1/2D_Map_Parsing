CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I./gnl

SRC := main.c
GNL_SRC := gnl/get_next_line.c gnl/get_next_line_utils.c
OBJ := $(SRC:.c=.o) $(GNL_SRC:.c=.o)

NAME := parsing

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

