/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:29 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 17:39:14 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void raycasting(t_data *data, int *img_data, int size_line)
{
	int x;
	double wall_dist;
	t_draw draw;
	t_skyfloor ts;

	x = 0;
	while (x < screenWidth)
	{
		ray_measure(x, screenWidth, data);
		ray_dist(data->player);
		side_ray(data->player);
		dda_algorithm(data);
		wall_dist = find_wall_distance(data->player);
		draw.drawStart = -((int)(screenHeight / wall_dist)) / 2 + screenHeight / 2;
		if (draw.drawStart < 0)
			draw.drawStart = 0;
		draw.drawEnd = -draw.drawStart + screenHeight;
		if (draw.drawEnd >= screenHeight)
			draw.drawEnd = screenHeight - 1;
		ts.x = x;
		ts.drawStart = draw.drawStart;
		ts.drawEnd = draw.drawEnd;
		ts.img_data = img_data;
		ts.size_line = size_line;
		sky_floor(ts, data);
		draw.x = x;
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
