/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:00:09 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/18 17:52:33 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int exe_feature(t_feature *f)
{
    if(f->so)
        if(is_exe(f->so))
            return(printf("Error\nCan't exe\n"),1);
    if(f->no)
        if(is_exe(f->no))
            return(printf("Error\nCan't exe\n"),1);
    if(f->we)
        if(is_exe(f->we))
            return(printf("Error\nCan't exe\n"),1);
    if(f->ea)
        if(is_exe(f->ea))
            return(printf("Error\nCan't exe\n"),1);
    if(f->f)
        if(!is_truedigit(f->f))
            return(printf("Error\nCan't exe\n"),1);
    if(f->c)
        if(!is_truedigit(f->c))
            return(printf("Error\nCan't exe\n"),1);
    return(0);
}

int	is_feature(char *line, t_data *data)
{
	while (*line && jumper(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2) && jumper(line[2]) && !data->feature->no)
		data->feature->no = line;
	else if (!ft_strncmp(line, "SO", 2) && jumper(line[2]) 
        && !data->feature->so)
		data->feature->so = line;
	else if (!ft_strncmp(line, "WE", 2) 
        && jumper(line[2]) && !data->feature->we)
		data->feature->we = line;
	else if (!ft_strncmp(line, "EA", 2)
        && jumper(line[2]) && !data->feature->ea)
		data->feature->ea = line;
	else if (line[0] == 'F' && jumper(line[1]) && !data->feature->f)
		data->feature->f = line;
	else if (line[0] == 'C' && jumper(line[1]) && !data->feature->c)
		data->feature->c = line;
	else
		return (0);
	return (1);
}

int is_map(char *line, t_data *data)
{	
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '1' || jumper(line[i]) || line[i] == '0' || line[i] == 'N')
			i++;
		else
			return(0);
	}
	map_add_back(&data->map, ft_mapnew(line));
	return(1);
}

int is_empty(char *line)
{
	int i;
    i = 0;
	while(line && line [i])
	{
		if(jumper(line[i]))
			i++;
		else
			return(0);
	}
	return(1);	
}

int is_true_map(char *map, t_data *data)
{
    int fd;
    char *line;
	
	fd = open(map, O_RDONLY);
    if(fd == -1)
		return (close(fd), printf("Error\nCould not open map file\n"), 0);
	line = get_next_line(fd);
	while(line)
	{
		if(is_feature(line, data) || is_empty(line))
			line = get_next_line(fd);
		else if(is_map(line, data))
			line = get_next_line(fd);
		else
			return(printf("Error\nFalse map\n"),0);
	}
	if(exe_feature(data->feature))
        return(printf("Error\nNo texture\n"),0);
    return(1);
}
