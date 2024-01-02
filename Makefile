CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I./gnl -I./libft
LIBFT := ./libft/libft.a

SRC := main.c \
		parsing/init_map_line_ranges.c parsing/map_parse.c \
		parsing/textures_parse_1.c parsing/textures_parse_2.c \
		helpers/display_debug_infos.c helpers/remove_trailing_newline.c
GNL_SRC := gnl/get_next_line.c gnl/get_next_line_utils.c
OBJ := $(SRC:.c=.o) $(GNL_SRC:.c=.o)

NAME := MapParser

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re