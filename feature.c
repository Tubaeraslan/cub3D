/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:33 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/26 16:22:35 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exe_feature(t_feature *f)
{
	if (f->so)
		if (is_exe(f->so))
			return (printf("Error\nCan't exe\n"), 1);
	if (f->no)
		if (is_exe(f->no))
			return (printf("Error\nCan't exe\n"), 1);
	if (f->we)
		if (is_exe(f->we))
			return (printf("Error\nCan't exe\n"), 1);
	if (f->ea)
		if (is_exe(f->ea))
			return (printf("Error\nCan't exe\n"), 1);
	if (f->f)
		if (!is_truedigit(f->f, 0, -1, 0))
			return (printf("Error\nCan't exe\n"), 1);
	if (f->c)
		if (!is_truedigit(f->c, 0, -1, 0))
			return (printf("Error\nCan't exe\n"), 1);
	return (0);
}

int	is_feature(char *line, t_data *data)
{
	while (*line && jumper(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2) && jumper(line[2]) && !data->feature->no)
		data->feature->no = ft_strdup(line);
	else if (!ft_strncmp(line, "SO", 2) && jumper(line[2])
		&& !data->feature->so)
		data->feature->so = ft_strdup(line);
	else if (!ft_strncmp(line, "WE", 2) && jumper(line[2])
		&& !data->feature->we)
		data->feature->we = ft_strdup(line);
	else if (!ft_strncmp(line, "EA", 2) && jumper(line[2])
		&& !data->feature->ea)
		data->feature->ea = ft_strdup(line);
	else if (line[0] == 'F' && jumper(line[1]) && !data->feature->f)
		data->feature->f = ft_strdup(line);
	else if (line[0] == 'C' && jumper(line[1]) && !data->feature->c)
		data->feature->c = ft_strdup(line);
	else
		return (0);
	return (1);
}

int	is_feature_ok(t_feature *f)
{
	if (!f->no)
		return (0);
	if (!f->so)
		return (0);
	if (!f->we)
		return (0);
	if (!f->ea)
		return (0);
	if (!f->f)
		return (0);
	if (!f->c)
		return (0);
	return (1);
}

int	feature_ctl(t_data *data)
{
	if (!is_feature_ok(data->feature))
		return (printf("Error\nYou need some feature\n"), 0);
	if (!data->player->start_pos)
		return (printf("Error\nThere isn't Player\n"), 0);
	if (exe_feature(data->feature))
		return (0);
	return (1);
}
