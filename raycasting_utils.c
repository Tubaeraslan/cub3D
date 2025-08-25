/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:38:44 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/24 21:28:20 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_dist(t_player *player)
{
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	if (player->ray_dir_x == 0)
		player->delta_dist_x = 1e30;
	else
		player->delta_dist_x = fabs(1.0 / player->ray_dir_x);
	if (player->ray_dir_y == 0)
		player->delta_dist_y = 1e30;
	else
		player->delta_dist_y = fabs(1.0 / player->ray_dir_y);
}

void	side_ray(t_player *player)
{
	if (player->ray_dir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->pos_x - player->map_x)
			* player->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		player->side_dist_x = (player->map_x + 1.0 - player->pos_x)
			* player->delta_dist_x;
	}
	if (player->ray_dir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->pos_y - player->map_y)
			* player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->pos_y)
			* player->delta_dist_y;
	}
}

int	rgb_str_to_int(const char *str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	while (*str && (*str < '0' || *str > '9'))
		str++;
	r = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	g = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	b = ft_atoi(str);
	return ((r << 16) | (g << 8) | b);
}

void	ray_measure(int x, int w, t_data *data)
{
	double	camera_x;

	camera_x = 2 * (double)x / (double)w - 1.0;
	data->player->ray_dir_x = data->player->dir_x + data->player->plane_x
		* camera_x;
	data->player->ray_dir_y = data->player->dir_y + data->player->plane_y
		* camera_x;
}

void	sky_floor(t_skyfloor ts, t_data *data)
{
	int	sky_color;
	int	ground_color;
	int	y;

	sky_color = 0xFFB6C1;
	ground_color = 0xFFB6C1;
	if (data->feature->c)
		sky_color = rgb_str_to_int(data->feature->c);
	if (data->feature->f)
		ground_color = rgb_str_to_int(data->feature->f);
	ts.sky_color = sky_color;
	ts.ground_color = ground_color;
	y = 0;
	while (y < ts.draw_start)
	{
		if (ts.x >= 0 && ts.x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
			ts.img_data[y * (ts.size_line / 4) + ts.x] = ts.sky_color;
		y++;
	}
	y = ts.draw_end;
	while (y++ < SCREENHEIGHT)
	{
		if (ts.x >= 0 && ts.x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
			ts.img_data[y * (ts.size_line / 4) + ts.x] = ts.ground_color;
	}
}
