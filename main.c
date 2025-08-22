/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:55:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/22 17:45:18 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_player_position_from_map(t_data *data)
{
    for (int y = 0; data->char_map[y]; y++) {
        for (int x = 0; data->char_map[y][x]; x++) {
            if (data->char_map[y][x] == 'N' || data->char_map[y][x] == 'S' ||
                data->char_map[y][x] == 'E' || data->char_map[y][x] == 'W') {
                data->player->posX = x + 0.5;
                data->player->posY = y + 0.5;
                data->player->start_pos = data->char_map[y][x];
                data->char_map[y][x] = '0';
                return;
            }
        }
    }
}

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
	// int map_height = 27;
	// data->widht = map_width;
	// data->high = map_height;
	// list_to_char(data);
	data->player->hit = 0;
	//printf("%c\n",data->player->start_pos);
	//data->player->start_pos = 'N';
	//fplayer_position(data->char_map,data);
	// data->player->mapX=3;
	// data->player->mapY=3;
	set_player_position_from_map(data);
	data->text_width = 0;
	data->text_height = 0;
    execute(data);
    return(0);
}
