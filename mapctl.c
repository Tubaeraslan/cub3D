/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:43:31 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/21 15:21:30 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void list_to_char(t_data *data)
{
	t_map *fakemap;
	int size;
	char **map;
	int i;
	
	i = 0;
	fakemap = data->map;
	size = ft_mapsize(data->map);
	data->high = size;
	map = malloc(sizeof(char *) * size);
	while (fakemap)
	{
		map[i] = fakemap->map_line;
		i++;
		fakemap = fakemap->next;
	}
	map[i] = NULL;
	data->char_map = map;
}

int itelim(t_data *data)
{
	t_map *fakemap;
	int tmp;
	fakemap = data->map;
	tmp = fakemap->num;
	fakemap = fakemap->next;
	while (fakemap)
	{
		if(tmp + 1 == fakemap->num)
		{
			tmp = fakemap->num;
			fakemap = fakemap->next;
		}
		else
			return(printf("Error\nThere is empty line in map\n"), 1);	
	}
	return(0);
}

void find_player_position(char **map, t_data *data)
{
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == data->player->start_pos)
			{
				data->player->posX = x + 0.5;
				data->player->posY = y + 0.5;
				return;
			}
			x++;
		}
		y++;
	}
}

int check_map(char **av, t_data *data)
{
	if(!check_map_name(av[1]))
		return(printf("Invalid map name\n"),0);
	if(!is_true_map(av[1], data))
		{
			return(0);
		}
		
	if(data->feature->we)
		printf("%s",data->feature->we);
	if(data->feature->so)
		printf("%s",data->feature->so);
	if(data->feature->no)
		printf("%s",data->feature->no);			
	if(data->feature->ea)
		printf("%s",data->feature->ea);
	if(data->feature->f)
		printf("%s",data->feature->f);
	if(data->feature->c)
		printf("%s",data->feature->c);
	// while (data->map)
	// { 
	// 	if(data->map != NULL)
	//     {
	// 		printf("%s", data->map->map_line);
	// 		data->map = data->map->next;
	// 	}
	// 	else
	// 		printf("NOMAP\n");
	// }
	return(1);
}