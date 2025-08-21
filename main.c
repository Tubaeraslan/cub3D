/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:55:12 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/21 19:37:59 by teraslan         ###   ########.fr       */
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
	int map_width = 62;
	int map_height = 27;
	data->widht = map_width;
	data->high = map_height;
	list_to_char(data);
	data->player->hit = 0;
	data->player->posX = 3.5;
	data->player->posY = 3.5;
	//printf("%c\n",data->player->start_pos);
	//data->player->start_pos = 'N';
	data->player->mapX=2;
	data->player->mapY=2;
	data->text_width = 0;
	data->text_height = 0;
    execute(data);
    return(0);
}
