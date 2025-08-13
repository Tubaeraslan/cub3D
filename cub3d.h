#ifndef CUB_3D_H
#define CUB_3D_H

#include "stdlib.h"

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
}   t_player;

void	player_position(t_player *player);

#endif