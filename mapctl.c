/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:43:31 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/25 22:50:40 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	list_to_char(t_data *data)
{
	t_map	*fakemap;
	int		size;
	char	**map;
	int		i;

	i = 0;
	fakemap = data->map;
	size = ft_mapsize(data->map);
	data->high = size;
	map = malloc(sizeof(char *) * (size + 1));
	while (fakemap)
	{
		if ((int)ft_strlen(fakemap->map_line) > data->widht)
			data->widht = (int)ft_strlen(fakemap->map_line);
		map[i] = ft_strdup(fakemap->map_line);
		i++;
		fakemap = fakemap->next;
	}
	map[i] = NULL;
	data->char_map = map;
}

int	itelim(t_data *data)
{
	t_map	*fakemap;
	int		tmp;

	fakemap = data->map;
	tmp = fakemap->num;
	fakemap = fakemap->next;
	while (fakemap)
	{
		if (tmp + 1 == fakemap->num)
		{
			tmp = fakemap->num;
			fakemap = fakemap->next;
		}
		else
			return (printf("Error\nThere is empty line in map\n"), 1);
	}
	data->widht = 0;
	return (0);
}

void	find_player_position(char **map, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == data->player->start_pos)
			{
				data->player->map_x = x;
				data->player->map_y = y;
				return ;
			}
			y++;
		}
		x++;
	}
}

int	flood_fill(int x, int y, t_data *data, char sp)
{
	int		rowlen;
	char	c;

	if (x < 0 || y < 0 || data->fakemap[y] == NULL)
		return (1);
	rowlen = (int)ft_strlen(data->fakemap[y]);
	if (x >= rowlen)
		return (1);
	c = data->fakemap[y][x];
	if (c == '\0' || c == '\n' || c == ' ')
		return (1);
	if (c == '1' || c == 'V')
		return (0);
	if (c != '0' && c != sp)
		return (1);
	data->fakemap[y][x] = 'V';
	if (flood_fill(x + 1, y, data, sp))
		return (1);
	if (flood_fill(x - 1, y, data, sp))
		return (1);
	if (flood_fill(x, y + 1, data, sp))
		return (1);
	if (flood_fill(x, y - 1, data, sp))
		return (1);
	return (0);
}

int	check_map(char **av, t_data *data)
{
	int	fd;

	if (!check_map_name(av[1]))
		return (printf("Invalid map name\n"), 0);
	data->line_num = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error\nCould not open map file\n"), 0);
	if (!is_true_map(data, fd))
		return (0);
	if (itelim(data))
		return (0);
	list_to_char(data);
	find_player_position(data->char_map, data);
	data->fakemap = copy_char_matrix(data->char_map, 0);
	if (flood_fill(data->player->map_y, data->player->map_x, data,
			data->player->start_pos))
		return (printf("Error\nInvalid map\n"), 0);
	return (1);
}
