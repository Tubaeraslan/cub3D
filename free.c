/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:32:33 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/24 22:05:46 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	freegnl(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
}

void	free_char_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->player)
		free(data->player);
	if (data->char_map)
	{
		i = 0;
		while (data->char_map[i])
		{
			free(data->char_map[i]);
			i++;
		}
		free(data->char_map);
	}
}

void	free_feature(t_data *data)
{
	if (data->feature)
	{
		if (data->feature->no)
			free(data->feature->no);
		if (data->feature->so)
			free(data->feature->so);
		if (data->feature->we)
			free(data->feature->we);
		if (data->feature->ea)
			free(data->feature->ea);
		if (data->feature->f)
			free(data->feature->f);
		if (data->feature->c)
			free(data->feature->c);
		if (data->feature)
			free(data->feature);
	}
	free_char_map(data);
}

void	free_data(t_data *data, int i)
{
	t_map	*tmp_map;
	t_map	*next_map;

	tmp_map = data->map;
	while (tmp_map)
	{
		next_map = tmp_map->next;
		if (tmp_map->map_line)
			free(tmp_map->map_line);
		free(tmp_map);
		tmp_map = next_map;
	}
	free_feature(data);
	if (data->fakemap)
	{
		i = 0;
		while (data->fakemap[i])
		{
			free(data->fakemap[i]);
			i++;
		}
		free(data->fakemap);
	}
	free(data);
}
