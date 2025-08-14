NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g
CC = cc

SRC = main.c player_position.c raycasting.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re