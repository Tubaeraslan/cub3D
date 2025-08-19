/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:18:44 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/19 14:22:18 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall_line(t_data *data, int *img_data, int size_line, t_draw draw)
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

double find_wall_distance(t_player *player)
{
	double perpWallDist;
	if (player->side == 0)
		perpWallDist = fabs((player->mapX - player->posX + (1 - player->stepX) / 2.0) / player->rayDirX);
	else
		perpWallDist = fabs((player->mapY - player->posY + (1 - player->stepY) / 2.0) / player->rayDirY);
	return perpWallDist;
}

void dda_algorithm(t_data *data)
{
	// DDA
	data->player->hit = 0;
	while (data->player->hit == 0)
	{
		if (data->player->sideDistX < data->player->sideDistY)
		{
			data->player->sideDistX += data->player->deltaDistX;
			data->player->mapX += data->player->stepX;
			data->player->side = 0;
		}
		else
		{
			data->player->sideDistY += data->player->deltaDistY;
			data->player->mapY += data->player->stepY;
			data->player->side = 1;
		}
		if (data->player->mapY < 0 || data->player->mapY >= data->map_height ||
			data->player->mapX < 0 || data->player->mapX >= data->map_width ||
			data->char_map[data->player->mapY][data->player->mapX] == '1')
			data->player->hit = 1;
	}
}
