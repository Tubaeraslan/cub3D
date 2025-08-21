
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:56:14 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/19 14:24:46 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>      // open
#include <stdio.h>      // printf, perror
#include <string.h>     // strerror
#include <sys/time.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include "math.h"
#include "./minilibx-linux/mlx.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define screenWidth 1920
#define screenHeight 1080

typedef struct s_draw
{
	int x;
	int drawStart;
	int drawEnd;
	double wall_dist;
} t_draw;

typedef struct s_texture {
	void *img;
	int *addr;
	int width;
	int height;
	int bpp;
	int size_line;
	int endian;
} t_texture;

typedef struct s_player
{
	double	posX; //oyuncunun map üzerindeki x konumu
	double	posY; //oyuncunun map üzerindeki y konumu
	double	dirX; //oyuncunun baktığı x 
	double	dirY; //oyuncunun baktığı y
	char	start_pos; // N-S-E-W oyuncunun hangi yöne bakarak başladığı
	double	fov;
	double	planeX; //oyuncunun sağa ve sola bakabilmesi için dirx ve dir y ye dik bir vektör
	double	planeY;
	double rayDirX; //ışın ın yönü
	double rayDirY;
	int mapX;
	int mapY;
	double deltaDistX;
	double deltaDistY;
	int stepX;
	int stepY;
	double sideDistX;
	double sideDistY;
	int hit;
	int side;
	t_draw	draw;
}	t_player;

typedef struct s_map
{
	char *map_line;
	struct s_map *next;	
}	t_map;

typedef struct s_feature
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;
	
}   t_feature;

typedef struct s_data
{
	t_feature *feature;
	t_player *player;
	t_map *map;
	int map_width;
	int map_height;
	void	*mlx;
	void	*win;
	bool    empty;
	char	**char_map;
	t_texture north;
	t_texture south;
	t_texture east;
	t_texture west;
	int text_width;
	int text_height;
	int		size_line;     // eklendi
	int		bpp;           // eklendi
	int		endian;
}	t_data;

int is_true_map(char *map, t_data *data);
int	jumper(char c);
int	check_map_name(char *str);
int check_map(char **av, t_data *data);
t_map	*ft_mapnew(void *content);
void    map_add_back(t_map **lst, t_map *new);
int is_exe(char *str);
int	rgb_atoi(const char *str);
int is_truedigit(char *str);
void	execute(t_data *data);
int	key_hook(int keycode, t_data *data);
int	exit_program(t_data *data);
void draw_image(t_data *data);
void dda_algorithm(t_data *data);
double find_wall_distance(t_player *player);
void draw_wall_line(t_data *data, int *img_data, int size_line, t_draw draw);
t_texture *choose_texture(t_data *data);

#endif