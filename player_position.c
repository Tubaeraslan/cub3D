#include "cub3d.h"

void    player_position(t_player *player)
{
    if (player->start_pos == 'N')
    {
        player->dirX = 0;
        player->dirY = -1;
        player->planeX = player->fov;
        player->planeY = 0;
    }
    else if(player->start_pos == 'S')
    {
        player->dirX = 0;
        player->dirY = 1;
        player->planeX = -(player->fov);
        player->planeY = 0;
    }
    else if(player->start_pos == 'E')
    {
        player->dirX = 1;
        player->dirY = 0;
        player->planeX = 0;
        player->planeY = player->fov;
    }
    else if(player->start_pos == "W")
    {
        player->dirX = -1;
        player->dirY = 0;
        player->planeX = 0;
        player->planeY = -(player->fov);
    }
}
