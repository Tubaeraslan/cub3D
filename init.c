/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:00:09 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/27 15:20:29 by teraslan         ###   ########.fr       */
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

// static int	process_line(char *line, t_data *data, int fd)
// {
// 	int	i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] == '\t')
// 			return (0);
// 	}
// 	if (is_feature(line, data) || is_empty(line))
// 	{
// 		free(line);
// 		return (1);
// 	}
// 	else if (is_map(line, data, 0))
// 	{
// 		free(line);
// 		return (1);
// 	}
// 	else
// 	{
// 		return (freegnl(fd), close(fd), free(line),
// 			printf("Error\nFalse map\n"), 0);
// 	}
// }

// int	is_true_map(t_data *data, int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!process_line(line, data, fd))
// 			return (0);
// 		line = get_next_line(fd);
// 		data->line_num++;
// 	}
// 	if (!feature_ctl(data))
// 		return (close(fd), 0);
// 	return (close(fd), 1);
// }
int check_tab(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if(line[i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_true_map(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if(!check_tab(line))
			return(free(line), freegnl(fd), 0);
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
	return (close(fd), 1);
}
