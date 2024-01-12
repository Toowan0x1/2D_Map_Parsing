CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I./gnl -I./libft
LIBFT := ./libft/libft.a

SRC := main.c \
		parsing/map_parse.c \
		parsing/map_section_detector_00.c \
		parsing/map_section_detector_01.c \
		parsing/map_section_analysis_00.c \
		parsing/textures_parse_00.c \
		parsing/textures_parse_01.c \
		parsing/textures_parse_02.c \
		parsing/textures_parse_03.c \
		parsing/textures_parse_04.c \
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