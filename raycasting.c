/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:29 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 13:48:40 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void raycasting(t_data *data, int *img_data, int size_line)
{
	int x;
	int w;
	double cameraX;
	double wall_dist;
	t_draw draw;
	// char *sky = data->feature->c;
	// char *ground = data->feature->f;

	w = screenWidth;
	x = 0;
	while (x < w)
	{
		cameraX = 2 * (double)x / (double)w - 1.0;
		data->player->rayDirX = data->player->dirX + data->player->planeX * cameraX;
		data->player->rayDirY = data->player->dirY + data->player->planeY * cameraX;
		ray_dist(data->player);
		side_ray(data->player);
		dda_algorithm(data);
		wall_dist = find_wall_distance(data->player);
		int lineHeight = (int)(screenHeight / wall_dist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		// // gökyüzü
		int y = 0;
		// int sky_color = 0x87CEEB;
		// int ground_color = 0x444444;
		// strip_trailing_whitespace(sky);
		// strip_trailing_whitespace(ground);
		// if (sky)
		// 	sky_color = rgb_atoi(sky);
		// if (ground)
		// 	ground_color = rgb_atoi(ground);
		while (y < drawStart)
		{
			if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
				img_data[y * (size_line / 4) + x] = 0x87CEEB;
			y++;
		}
		// zemin
		y = drawEnd;
		while (y < screenHeight)
		{
			if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
				img_data[y * (size_line / 4) + x] = 0x444444;
			y++;
		}
		draw.x = x;
		draw.drawStart = drawStart;
		draw.drawEnd = drawEnd;
		draw.wall_dist = wall_dist;
		draw_wall_line(data, img_data, size_line, draw);
		x++;
	}
}

// Basit image buffer ile çizim için fonksiyon
void draw_image(t_data *data)
{
	void *img;
	int *img_data;
	int bpp, size_line, endian;

	img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	if (!img)
	{
		fprintf(stderr, "[ERROR] Image buffer olusturulamadi!\n");
		return;
	}
	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	raycasting(data, img_data, size_line);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}