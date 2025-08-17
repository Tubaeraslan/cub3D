NAME = cub3d
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC = main.c player_position.c raycasting.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(MLX_DIR) 
	cc $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	make clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re