#include "cub3d.h"

void player_position(t_player *player)
{
	double	fov;

	fov = 66.0 * M_PI / 180.0; // 66° FOV
	if (player->start_pos == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
	}
	else if(player->start_pos == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
	}
	else if(player->start_pos == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
	}
	else if(player->start_pos == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	player->planeX = -player->dirY * tan(fov / 2);
	player->planeY = player->dirX * tan(fov / 2);
}

