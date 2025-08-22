
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:57:17 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/22 13:54:52 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	jumper(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	rgb_atoi(const char *str)
{
	int	isaret;
	int	basamak;
	int	i;

	isaret = 1;
	basamak = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isaret *= -1;
		i++;
	}
	while (str[i])
	{
        if(str[i] >= '0' && str[i] <= '9')
		    basamak = basamak * 10 + (str[i] - '0');
        else if(!jumper(str[i]))
            return(-1);
		i++;
    }
	return (isaret * basamak);
}

char **copy_char_matrix(char **src)
{
    int i = 0;
    char **dest;

    if (!src)
        return NULL;

    while (src[i])
        i++;
    dest = malloc(sizeof(char *) * (i + 1));
    if (!dest)
        return NULL;

    i = 0;
    while (src[i])
    {
        dest[i] = ft_strdup(src[i]);
        if (!dest[i])
        {
            while (i-- > 0)
                free(dest[i]);
            free(dest);
            return NULL;
        }
        i++;
    }
    dest[i] = NULL;
    return dest;
}

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

void free_data(t_data *data)
{
    t_map *tmp_map;
    t_map *next_map;
    int i;

    if (!data)
        return;

    if (data->feature)
    {
		if(data->feature->no)
        	free(data->feature->no);
        if(data->feature->so)
			free(data->feature->so);
        if(data->feature->we)
			free(data->feature->we);
        if(data->feature->ea)
			free(data->feature->ea);
        if(data->feature->f)
			free(data->feature->f);
        if(data->feature->c)
			free(data->feature->c);
		if(data->feature)
			free(data->feature);
    }

    if (data->player)
        free(data->player);

    tmp_map = data->map;
    while (tmp_map)
    {
        next_map = tmp_map->next;
        if (tmp_map->map_line)
            free(tmp_map->map_line);
        free(tmp_map);
        tmp_map = next_map;
    }

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
