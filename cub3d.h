#ifndef CUB_3D_H
#define CUB_3D_H

#include "stdlib.h"
#include "math.h"
#include "./minilibx-linux/mlx.h"

#define screenWidth 1920
#define screenHeight 1080


#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

struct s_data;

typedef struct s_draw
{
	int x;
	int drawStart;
	int drawEnd;
	double wall_dist;
} t_draw;

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
	struct s_data *data;
}   t_player;

typedef struct s_data
{
	char	**map;
	t_player *player;
	void	*mlx;   // Eklendi
	void	*win;
	int map_width;
	int map_height;
	void *tex_north;
	void *tex_south;
	void *tex_east;
	void *tex_west;
	int		*img_data;     // eklendi
	int		size_line;     // eklendi
	int		bpp;           // eklendi
	int		endian;        // eklendi
	int text_width;
	int text_height;
}	t_data;

void	player_position(t_player *player);
void	raycasting(t_player *player, int *img_data, int size_line);
void draw_image(t_data *data);
#endif