/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:55:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/23 18:33:11 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (data->char_map[y][x] == 'N' || data->char_map[y][x] == 'S' ||
				data->char_map[y][x] == 'E' || data->char_map[y][x] == 'W')
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
		return (free_data(data), 0);
	data->player->hit = 0;
	set_player_position_from_map(data);
	data->text_width = 0;
	data->text_height = 0;
	execute(data);
	free_data(data);
	return (0);
}
