/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:16:29 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/14 19:17:28 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
static void find_wall_dist(t_player *player, int x)
{
	double wallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int i;
	void *texture;
	int *text_data;
	int bpp, size_line, endian;
	int tex_x, tex_y;
	double wallX;
	int color;

	if (player->side == 0)
		wallDist = fabs((player->mapX - player->posX + (1 - player->stepX) / 2.0) / player->rayDirX);
	else
		wallDist = fabs((player->mapY - player->posY + (1 - player->stepY) / 2.0) / player->rayDirY);	if (wallDist <= 0.01 || isnan(wallDist) || isinf(wallDist)) {
    printf("x: %d, wallDist: %f (skip)\n", x, wallDist);
    return;
	}
	lineHeight = (int)(screenHeight / wallDist);
	drawStart = -lineHeight / 2 + screenHeight / 2;
	if (drawStart < 0)
    	drawStart = 0;
	drawEnd = lineHeight / 2 + screenHeight / 2;
	if (drawEnd >= screenHeight)
    	drawEnd = screenHeight - 1;
	if (player->side == 0 && player->rayDirX > 0)
        texture = player->data->tex_east;
    else if (player->side == 0 && player->rayDirX < 0)
        texture = player->data->tex_west;
    else if (player->side == 1 && player->rayDirY > 0)
        texture = player->data->tex_south;
    else
        texture = player->data->tex_north;
	// Duvarın çarpma noktasını bul
	if (player->side == 0)
        wallX = player->posY + wallDist * player->rayDirY;
    else
        wallX = player->posX + wallDist * player->rayDirX;
    wallX -= floor(wallX);
	tex_x = (int)(wallX * (double)player->data->text_width);
    if ((player->side == 0 && player->rayDirX > 0) || (player->side == 1 && player->rayDirY < 0))
        tex_x = player->data->text_width - tex_x - 1;

    text_data = (int *)mlx_get_data_addr(texture, &bpp, &size_line, &endian);
	printf("x: %d, drawStart: %d, drawEnd: %d\n", x, drawStart, drawEnd);
	for (i = drawStart; i < drawEnd; i++)
    {
        int d = i * 256 - screenHeight * 128 + lineHeight * 128;
        tex_y = ((d * player->data->text_height) / lineHeight) / 256;
        color = text_data[tex_y * player->data->text_width + tex_x];
        mlx_pixel_put(player->data->mlx, player->data->win, x, i, color);
    }
	
}

static int hit_wall(t_player *player)
{
    if (player->mapY < 0 || player->mapY >= player->data->map_height)
    	return 1;
	if (player->mapX < 0 || player->mapX >= player->data->map_width)
    	return 1;
	if (player->data->map[player->mapY][player->mapX] == '1')
        return 1;
    return 0;
}



static void perform_dda(t_player *player, int x)
{
	// DDA algoritması: duvara çarpana kadar ilerle
	while (player->hit == 0)
	{
		if (player->sideDistX < player->sideDistY)
		{
			player->sideDistX += player->deltaDistX;
			player->mapX += player->stepX;
			player->side = 0;
		}
		else
		{
			player->sideDistY += player->deltaDistY;
			player->mapY += player->stepY;
			player->side = 1;
		}
		if (hit_wall(player))
		{
			player->hit = 1;
		}
	}
	// Sadece duvara çarpınca çizim yap
	if (player->hit == 1)
		find_wall_dist(player, x);
}

static void	find_ray(t_player *player,int x)
{
	// Her ışın için hit sıfırlanmalı
	player->hit = 0;
	if (player->rayDirX < 0)
	{
		player->stepX = -1;
		player->sideDistX = (player->posX - player->mapX) * player->deltaDistX;
	}
	else
	{
		player->stepX = 1;
		player->sideDistX = (player->mapX + 1.0 - player->posX) * player->deltaDistX;
	}
	if (player->rayDirY < 0)
	{
		player->stepY = -1;
		player->sideDistY = (player->posY - player->mapY) * player->deltaDistY;
	}
	else
	{
		player->stepY = 1;
		player->sideDistY = (player->mapY + 1.0 - player->posY) * player->deltaDistY;
	}
	perform_dda(player, x);
}

static void	dda_algorithm(t_player *player,int x)
{
	player->mapX = (int)player->posX;
	player->mapY = (int)player->posY;
	if (player->rayDirX == 0)
		player->deltaDistX = 1e30;
	else
		player->deltaDistX = fabs(1.0 / player->rayDirX);
	if (player->rayDirY == 0)
		player->deltaDistY = 1e30;
	else
		player->deltaDistY = fabs(1.0 / player->rayDirY);
	printf("DDA: mapX=%d, mapY=%d, hit=%d, mapVal=%c\n", player->mapX, player->mapY, player->hit, player->data->map[player->mapY][player->mapX]);
	find_ray(player,x);
}

void	raycasting(t_player *player)
{
	int x;
	int w;
	double cameraX;

	x = 0;
	w = screenWidth;
	//ışın pozisyonu ve yönü hesaplama
	while (x < w)
	{
		cameraX = 2 * (double)x / (double)w - 1.0;
		player->rayDirX = player->dirX + player->planeX * cameraX;
		player->rayDirY = player->dirY + player->planeY * cameraX;
		dda_algorithm(player,x);
		if (x % 100 == 0)
        	printf("Ray %d dir: (%f, %f)\n", x, player->rayDirX, player->rayDirY);
		x++;
	}
}
