NAME = cub3d
SRC = main.c key_hook.c render.c init_game.c draw.c dda.c utils.c \
	argument_validation.c map/map_parser.c map/parse_elements.c \
	map/parse_map_grid.c map/map_validation.c map/parse_textures.c

OBJ := $(SRC:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

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