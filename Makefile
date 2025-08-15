NAME = cub3d
CC = cc

SRC = main.c player_position.c raycasting.c
LIBS = -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re