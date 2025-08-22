/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:47:21 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 14:52:42 by teraslan         ###   ########.fr       */
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

void strip_trailing_whitespace(char *str)
{
	if (!str)
        return;
	int len = ft_strlen(str);
	while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == '\t'))
		str[--len] = '\0';
}

void	load_textures(t_data *data)
{
	char *north = data->feature->no;
	char *south = data->feature->so;
	char *east  = data->feature->ea;
	char *west  = data->feature->we;

	if (north && (strncmp(north, "NO ", 3) == 0 || strncmp(north, "NO\t", 3) == 0))
		north += 3;
	while (north && *north == ' ')
		north++;
	if (south && (strncmp(south, "SO ", 3) == 0 || strncmp(south, "SO\t", 3) == 0))
		south += 3;
	while (south && *south == ' ')
		south++;
	if (east && (strncmp(east, "EA ", 3) == 0 || strncmp(east, "EA\t", 3) == 0))
		east += 3;
	while (east && *east == ' ')
		east++;
	if (west && (strncmp(west, "WE ", 3) == 0 || strncmp(west, "WE\t", 3) == 0))
		west += 3;
	while (west && *west == ' ')
		west++;

	// Başındaki boşlukları da atla
	while (north && *north == ' ')
		north++;
	while (south && *south == ' ')
		south++;
	while (east && *east == ' ')
		east++;
	while (west && *west == ' ')
		west++;
	strip_trailing_whitespace(north);
	strip_trailing_whitespace(south);
	strip_trailing_whitespace(east);
	strip_trailing_whitespace(west);
	data->north.img = mlx_xpm_file_to_image(data->mlx, north, &data->north.width, &data->north.height);
	if (!data->north.img)
		printf("[ERROR] North texture yüklenemedi: %s\n", north);
	data->north.addr = (int *)mlx_get_data_addr(data->north.img, &data->north.bpp, &data->north.size_line, &data->north.endian);
	data->south.img = mlx_xpm_file_to_image(data->mlx, south, &data->south.width, &data->south.height);
	if (!data->south.img)
		printf("[ERROR] South texture yüklenemedi: %s\n", south);
	data->south.addr = (int *)mlx_get_data_addr(data->south.img, &data->south.bpp, &data->south.size_line, &data->south.endian);
	data->east.img = mlx_xpm_file_to_image(data->mlx, east, &data->east.width, &data->east.height);
	if (!data->east.img)
		printf("[ERROR] East texture yüklenemedi: %s\n", east);
	data->east.addr = (int *)mlx_get_data_addr(data->east.img, &data->east.bpp, &data->east.size_line, &data->east.endian);
	data->west.img = mlx_xpm_file_to_image(data->mlx, west, &data->west.width, &data->west.height);
	if (!data->west.img)
		printf("[ERROR] West texture yüklenemedi: %s\n", west);
	data->west.addr = (int *)mlx_get_data_addr(data->west.img, &data->west.bpp, &data->west.size_line, &data->west.endian);
}

void	execute(t_data *data)
{
	player_position(data->player);
	ready_mlx(data);
	load_textures(data);
	draw_image(data);
	mlx_loop(data->mlx);
}
