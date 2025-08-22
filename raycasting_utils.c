/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:44 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 17:40:32 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ray_dist(t_player *player)
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

void side_ray(t_player *player)
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

// 'C 225,30,0' veya '225,30,0' -> 0xE11E00
int rgb_str_to_int(const char *str)
{
    int r = 0, g = 0, b = 0;
    while (*str && (*str < '0' || *str > '9')) str++; // baştaki harf/boşlukları atla
    r = ft_atoi(str);
    while (*str && *str != ',') str++;
    if (*str == ',') str++;
    g = ft_atoi(str);
    while (*str && *str != ',') str++;
    if (*str == ',') str++;
    b = ft_atoi(str);
    return ((r << 16) | (g << 8) | b);
}

void ray_measure(int x, int w,t_data *data)
{
	double cameraX;

	cameraX = 2 * (double)x / (double)w - 1.0;
	data->player->rayDirX = data->player->dirX + data->player->planeX * cameraX;
	data->player->rayDirY = data->player->dirY + data->player->planeY * cameraX;
}

void sky_floor(t_skyfloor ts,t_data *data)
{
	int sky_color; // hex formatı
	int ground_color;
	int y;

	sky_color   = 0xFFB6C1; // hex formatı
	ground_color = 0xFFB6C1;
	if (data->feature->c)
		sky_color = rgb_str_to_int(data->feature->c);
	if (data->feature->f)
		ground_color = rgb_str_to_int(data->feature->f);
	ts.sky_color = sky_color;
	ts.ground_color = ground_color;
	y = 0;
	while (y < ts.drawStart)
	{
		if (ts.x >= 0 && ts.x < screenWidth && y >= 0 && y < screenHeight)
			ts.img_data[y * (ts.size_line / 4) + ts.x] = ts.sky_color;
		y++;
	}
	y = ts.drawEnd;
	while (y < screenHeight)
	{
		if (ts.x >= 0 && ts.x < screenWidth && y >= 0 && y < screenHeight)
			ts.img_data[y * (ts.size_line / 4) + ts.x] = ts.ground_color;
		y++;
	}
}

