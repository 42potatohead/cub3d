NAME = cub3d
src = src/main.c src/key_hook.c src/render.c src/init_game.c src/draw.c src/dda.c src/utils.c \
	src/argument_validation.c src/map/map_parser.c src/map/parse_elements.c \
	src/map/parse_map_grid.c src/map/map_validation.c src/map/parse_textures.c \
	src/map/parse_color.c src/map/utils.c src/map/parse_map_line.c src/map/handle_map_line.c \
	src/map/check_boundaries.c src/map/check_boundaries_utils.c

OBJ := $(src:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.af

CC = cc
CFLAGS = -Wextra -Wall -Werror -I./MLX42/include -g3 -O0
LDFLAGS = -L./MLX42/build -L$(LIBFT_DIR)
LIBS = -lmlx42 -lglfw -lX11 -lXext -lm -lft

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re