/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:55:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/24 21:36:36 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_data *data)
{
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	set_player_position_from_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->char_map[y])
	{
		x = 0;
		while (data->char_map[y][x])
		{
			if (data->char_map[y][x] == 'N' || data->char_map[y][x] == 'S'
				|| data->char_map[y][x] == 'E' || data->char_map[y][x] == 'W')
			{
				data->player->pos_x = x + 0.5;
				data->player->pos_y = y + 0.5;
				data->player->start_pos = data->char_map[y][x];
				data->char_map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (write(1, "Error\nNumber of wrong arguments\n", 32), 0);
	data = ft_calloc(1, sizeof(t_data));
	data->feature = ft_calloc(1, sizeof(t_feature));
	data->player = ft_calloc(1, sizeof(t_player));
	if (!check_map(av, data))
		return (free_data(data, 0), 0);
	data->player->hit = 0;
	set_player_position_from_map(data);
	data->text_width = 0;
	data->text_height = 0;
	execute(data);
	free_data(data, 0);
	return (0);
}
