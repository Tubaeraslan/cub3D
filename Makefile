NAME = cub3D

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC = main.c mapctl.c get_next_line.c get_next_line_utils.c lstfnc.c utils.c init.c check.c \
		execute.c key_control.c raycasting.c dda.c texture_utils.c raycasting_utils.c move_player.c free.c feature.c \
		map_utils.c

OBJS = main.o mapctl.o get_next_line.o get_next_line_utils.o lstfnc.o utils.o init.o check.o \
		execute.o key_control.o raycasting.o dda.o texture_utils.o raycasting_utils.o move_player.o free.o feature.o \
		map_utils.o

CFLAGS = -Wall -Wextra -Werror

CC = cc

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME) $(LIBFT)

clean:
	@rm -f $(OBJS)
	make clean -C libft
	make clean -C $(MLX_DIR)

go: all clean

fclean: clean
	@rm -f $(NAME)
	make fclean -C libft
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re