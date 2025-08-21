/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:55:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/21 15:36:49 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    if (ac != 2)
		  return (write(1, "Error\nNumber of wrong arguments\n", 32), 0);
    t_data *data;
    data = malloc(sizeof(t_data));
    data->feature = malloc(sizeof(t_feature));
    data->player = malloc(sizeof(t_player));
    if (!check_map(av, data))
		  return (0);
	// int map_width = 62;
	// data->widht = map_width;
	data->player->hit = 0;
	list_to_char(data);
	int max_width = 0;
	for (int i = 0; data->char_map[i] != NULL; i++) {
		int len = ft_strlen(data->char_map[i]);
		if (len > max_width)
			max_width = len;
	}
	data->widht = max_width;
	find_player_position(data->char_map,data);
	data->player->start_pos = 'N';
	data->text_width = 0;
	data->text_height = 0;
    execute(data);
    return(0);
}
