/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:47:21 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/24 21:27:48 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_position(t_player *player)
{
	double	fov;

	fov = 66.0 * M_PI / 180.0;
	if (player->start_pos == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (player->start_pos == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (player->start_pos == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (player->start_pos == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->plane_x = -player->dir_y * tan(fov / 2);
	player->plane_y = player->dir_x * tan(fov / 2);
}

void	ready_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, exit_program, data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

void	load_textures(t_data *data)
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	north = parse_texture_path(data->feature->no, "NO ");
	south = parse_texture_path(data->feature->so, "SO ");
	east = parse_texture_path(data->feature->ea, "EA ");
	west = parse_texture_path(data->feature->we, "WE ");
	data->north.img = mlx_xpm_file_to_image(data->mlx, north,
			&data->north.width, &data->north.height);
	data->north.addr = (int *)mlx_get_data_addr(data->north.img,
			&data->north.bpp, &data->north.size_line, &data->north.endian);
	data->south.img = mlx_xpm_file_to_image(data->mlx, south,
			&data->south.width, &data->south.height);
	data->south.addr = (int *)mlx_get_data_addr(data->south.img,
			&data->south.bpp, &data->south.size_line, &data->south.endian);
	data->east.img = mlx_xpm_file_to_image(data->mlx, east, &data->east.width,
			&data->east.height);
	data->east.addr = (int *)mlx_get_data_addr(data->east.img, &data->east.bpp,
			&data->east.size_line, &data->east.endian);
	data->west.img = mlx_xpm_file_to_image(data->mlx, west, &data->west.width,
			&data->west.height);
	data->west.addr = (int *)mlx_get_data_addr(data->west.img, &data->west.bpp,
			&data->west.size_line, &data->west.endian);
}

void	execute(t_data *data)
{
	player_position(data->player);
	data->player->move_speed = 0.10;
	data->player->rot_speed = 0.06;
	ready_mlx(data);
	load_textures(data);
	draw_image(data);
	mlx_loop(data->mlx);
}
