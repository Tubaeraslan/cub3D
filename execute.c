/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:21:54 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/19 14:39:48 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_position(t_player *player)
{
	double	fov;

	fov = 66.0 * M_PI / 180.0; // 66° FOV
	if (player->start_pos == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
	}
	else if(player->start_pos == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
	}
	else if(player->start_pos == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
	}
	else if(player->start_pos == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	player->planeX = -player->dirY * tan(fov / 2);
	player->planeY = player->dirX * tan(fov / 2);
}

void	ready_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "cub3d");
	mlx_hook(data->win, 2, 1L<<0, key_hook, data);      // Key press
	mlx_hook(data->win, 17, 0, exit_program, data);
}

void	load_textures(t_data *data)
{
	char *north = data->feature->no;
	char *south = data->feature->so;
	char *east  = data->feature->ea;
	char *west  = data->feature->we;

	if (north && (strncmp(north, "NO ", 3) == 0 || strncmp(north, "NO\t", 3) == 0))
		north += 3;
	if (south && (strncmp(south, "SO ", 3) == 0 || strncmp(south, "SO\t", 3) == 0))
		south += 3;
	if (east && (strncmp(east, "EA ", 3) == 0 || strncmp(east, "EA\t", 3) == 0))
		east += 3;
	if (west && (strncmp(west, "WE ", 3) == 0 || strncmp(west, "WE\t", 3) == 0))
		west += 3;

	// Başındaki boşlukları da atla
	while (north && *north == ' ')
		north++;
	while (south && *south == ' ')
		south++;
	while (east && *east == ' ')
		east++;
	while (west && *west == ' ')
		west++;
	data->tex_north = mlx_xpm_file_to_image(data->mlx, "./textures/north.xpm", &data->text_width, &data->text_height);
	if (!data->tex_north)
		printf("[ERROR] North texture yüklenemedi: %s\n", north);
	data->tex_south = mlx_xpm_file_to_image(data->mlx, "./textures/south.xpm", &data->text_width, &data->text_height);
	if (!data->tex_south)
		printf("[ERROR] South texture yüklenemedi: %s\n", south);
	data->tex_east = mlx_xpm_file_to_image(data->mlx, "./textures/east.xpm", &data->text_width, &data->text_height);
	if (!data->tex_east)
		printf("[ERROR] East texture yüklenemedi: %s\n", east);
	data->tex_west = mlx_xpm_file_to_image(data->mlx, "./textures/west.xpm", &data->text_width, &data->text_height);
	if (!data->tex_west)
		printf("[ERROR] West texture yüklenemedi: %s\n", west);
}

void	execute(t_data *data)
{
	player_position(data->player);
	ready_mlx(data);
	load_textures(data);
	draw_image(data);
	mlx_loop(data->mlx);
}
