/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:56:14 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/22 17:40:45 by teraslan         ###   ########.fr       */
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


typedef struct s_skyfloor
{
    int x;
    int drawStart;
    int drawEnd;
    int sky_color;
    int ground_color;
    int *img_data;
    int size_line;
}   t_skyfloor;


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
	int player_x;
	int player_y;
}	t_player;

typedef struct s_map
{
	char *map_line;
	int num;
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
	int high;
	int widht;
	char **char_map;
	t_texture north;
	t_texture south;
	t_texture east;
	t_texture west;
	char **fakemap;
	int line_num;
	void	*mlx;
    void	*win;
    bool    empty;
	int text_width;
	int text_height;
}	t_data;

int is_true_map(char *map, t_data *data);
void	clear_array(char **array);
void	freegnl(int fd);
int	jumper(char c);
int	check_map_name(char *str);
int check_map(char **av, t_data *data);
t_map	*ft_mapnew(char *content, int line_num);
void    map_add_back(t_map **lst, t_map *new);
int	ft_mapsize(t_map *lst);
int is_exe(char *str);
int	rgb_atoi(const char *str);
int is_truedigit(char *str);
char **copy_char_matrix(char **src);
void free_data(t_data *data);
void	execute(t_data *data);
int	key_hook(int keycode, t_data *data);
int	exit_program(t_data *data);
void list_to_char(t_data *data);
void find_player_position(char **map, t_data *data);
void draw_image(t_data *data);
void dda_algorithm(t_data *data);
double find_wall_distance(t_player *player);
void draw_wall_line(t_data *data, int *img_data, int size_line, t_draw draw);
t_texture *choose_texture(t_data *data);
void player_position(t_player *player);
void strip_trailing_whitespace(char *str);
char *parse_texture_path(char *path, const char *prefix);
void ray_dist(t_player *player);
void side_ray(t_player *player);
int rgb_str_to_int(const char *str);
void ray_measure(int x, int w,t_data *data);
void sky_floor(t_skyfloor ts,t_data *data);
#endif