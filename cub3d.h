#ifndef CUB_3D_H
#define CUB_3D_H

#include "stdlib.h"
#include "math.h"
#include "./minilibx_opengl_20191021/mlx.h"

#define screenWidth 640
#define screenHeight 480

struct s_data;

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
	struct s_data *data;
}   t_player;

typedef struct s_data
{
	char	**map;
	t_player *player;
	void	*mlx;   // Eklendi
    void	*win;
}	t_data;

void	player_position(t_player *player);
void	raycasting(t_player *player);
#endif