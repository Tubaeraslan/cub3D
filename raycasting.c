/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:29 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/23 19:46:35 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ready_ts(t_skyfloor *ts, t_draw *draw)
{
	ts->draw_start = draw->draw_start;
	ts->draw_end = draw->draw_end;
}

static void	raycast_column(t_data *data, int x, int *img_data, int size_line)
{
	double		wall_dist;
	t_draw		draw;
	t_skyfloor	ts;

	ray_measure(x, SCREENWIDTH, data);
	ray_dist(data->player);
	side_ray(data->player);
	dda_algorithm(data);
	wall_dist = find_wall_distance(data->player);
	if (wall_dist < 0.3)
		wall_dist = 0.3;
	draw.draw_start = -((int)(SCREENHEIGHT / wall_dist)) / 2 + SCREENHEIGHT / 2;
	if (draw.draw_start < 0)
		draw.draw_start = 0;
	draw.draw_end = -draw.draw_start + SCREENHEIGHT;
	if (draw.draw_end >= SCREENHEIGHT)
		draw.draw_end = SCREENHEIGHT - 1;
	ts.x = x;
	ts.img_data = img_data;
	ready_ts(&ts, &draw);
	ts.size_line = size_line;
	sky_floor(ts, data);
	draw.x = x;
	draw.wall_dist = wall_dist;
	draw_wall_line(data, img_data, size_line, draw);
}

static void	raycasting(t_data *data, int *img_data, int size_line)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		raycast_column(data, x, img_data, size_line);
		x++;
	}
}

void	draw_image(t_data *data)
{
	void	*img;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;

	img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!img)
	{
		fprintf(stderr, "[ERROR] Image buffer olusturulamadi!\n");
		return ;
	}
	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	raycasting(data, img_data, size_line);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
