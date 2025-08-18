/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:16:29 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/18 18:55:02 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void ray_dist(t_player *player)
{
	// DDA setup
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
}

static void side_ray(t_player *player)
{
	// Step and initial sideDist
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
}

static void dda_algorithm(t_player *player)
{
	// DDA
	player->hit = 0;
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
		if (player->mapY < 0 || player->mapY >= player->data->map_height ||
			player->mapX < 0 || player->mapX >= player->data->map_width ||
			player->data->map[player->mapY][player->mapX] == '1')
			player->hit = 1;
	}
}

static double find_wall_distance(t_player *player)
{
	double perpWallDist;
	if (player->side == 0)
		perpWallDist = fabs((player->mapX - player->posX + (1 - player->stepX) / 2.0) / player->rayDirX);
	else
		perpWallDist = fabs((player->mapY - player->posY + (1 - player->stepY) / 2.0) / player->rayDirY);
	return perpWallDist;
}

void *choose_texture(t_data *data)
{
	t_player *p = data->player;

	if (p->side == 0) { // X ekseninde çarpma (dikey duvar)
		if (p->rayDirX > 0)
			return data->tex_east;
		else
			return data->tex_west;
	} else {            // Y ekseninde çarpma (yatay duvar)
		if (p->rayDirY > 0)
			return data->tex_south;
		else
			return data->tex_north;
	}
}

static void draw_wall_line(t_data *data, int *img_data, int size_line, t_draw draw)
{
	void *tex;
	int *tex_data;
	double wallX;
	int texX;
	double step;
	double texPos;

	tex = choose_texture(data);
	tex_data = (int *)mlx_get_data_addr(tex, &data->bpp, &data->size_line, &data->endian);
	if (data->player->side == 0)
		wallX = data->player->posY + draw.wall_dist * data->player->rayDirY;
	else
		wallX = data->player->posX + draw.wall_dist * data->player->rayDirX;
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)data->text_width);
	if (data->player->side == 0 && data->player->rayDirX > 0)
		texX = data->text_width - texX - 1;
	if (data->player->side == 1 && data->player->rayDirY < 0)
		texX = data->text_width - texX - 1;
	step = 1.0 * data->text_height / (draw.drawEnd - draw.drawStart);
	texPos = (draw.drawStart - screenHeight / 2 + (draw.drawEnd - draw.drawStart) / 2) * step;
	int y = draw.drawStart;
	while (y < draw.drawEnd)
	{
		int texY = (int)texPos & (data->text_height - 1);
		texPos += step;
		int color = tex_data[texY * (data->size_line / 4) + texX];
		img_data[y * (size_line / 4) + draw.x] = color;
		y++;
	}
}


void raycasting(t_player *player, int *img_data, int size_line)
{
	int x;
	int w;
	double cameraX;
	double wall_dist;
	t_draw draw;

	w = screenWidth;
	x = 0;
	while (x < w)
	{
		cameraX = 2 * (double)x / (double)w - 1.0;
		player->rayDirX = player->dirX + player->planeX * cameraX;
		player->rayDirY = player->dirY + player->planeY * cameraX;
		ray_dist(player);
		side_ray(player);
		dda_algorithm(player);
		wall_dist = find_wall_distance(player);
		int lineHeight = (int)(screenHeight / wall_dist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		// gökyüzü
		int y = 0;
		while (y < drawStart)
		{
			img_data[y * (size_line / 4) + x] = 0x87CEEB;
			y++;
		}
		// zemin
		y = drawEnd;
		while (y < screenHeight)
		{
			img_data[y * (size_line / 4) + x] = 0x444444;
			y++;
		}
		draw.x = x;
		draw.drawStart = drawStart;
		draw.drawEnd = drawEnd;
		draw.wall_dist = wall_dist;
		draw_wall_line(player->data, img_data, size_line, draw);
		x++;
	}
}
