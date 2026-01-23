NAME = cub3d
SRC = main.c key_hook.c render.c init_game.c draw.c dda.c utils.c 

OBJ := $(SRC:%.c=%.o)
GNL_OBJ := $(GNL_SRC:%.c=%.o)

CC = cc
CFLAGS = -Wextra -Wall -Werror -I./MLX42/include -g3 -O0
LDFLAGS = -lm -L./MLX42/build -lmlx42 -lglfw -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	make clean
	rm -f $(NAME)

re : fclean all clean

.PHONY : all clean fclean libft