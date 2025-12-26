NAME = cub3d
SRC = main.c arugment_validation.c map.c

OBJ := $(SRC:%.c=%.o)
GNL_OBJ := $(GNL_SRC:%.c=%.o)

CC = cc
CFLAGS = -Wextra -Wall -Werror -I./MLX42/include -L./MLX42/build -lmlx42 -lglfw -lX11 -lXext -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	make clean
	rm -f $(NAME)

re : fclean all clean

.PHONY : all clean fclean libft