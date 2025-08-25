/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:00:09 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/24 22:05:03 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *line, t_data *data, int i)
{
	if (!data->feature->c || !data->feature->f || !data->feature->ea
		|| !data->feature->no || !data->feature->so || !data->feature->we)
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || jumper(line[i]))
		{
			i++;
			continue ;
		}
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (!data->player->start_pos)
				data->player->start_pos = line[i];
			else
				return (0);
		}
		else
			return (0);
		i++;
	}
	map_add_back(&data->map, ft_mapnew(line, data->line_num));
	return (1);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (jumper(line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_true_map(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_feature(line, data) || is_empty(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		else if (is_map(line, data, 0))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			return (freegnl(fd), close(fd), free(line),
				printf("Error\nFalse map\n"), 0);
		data->line_num++;
	}
	if (!feature_ctl(data))
		return (close(fd), 0);
	return (close(fd), 1);
}
