/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:55 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/25 16:53:24 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip_whitespace(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len
				- 1] == '\r' || str[len - 1] == '\t'))
		str[--len] = '\0';
}

char	*parse_texture_path(char *path, const char *prefix)
{
	if (path && (ft_strncmp(path, prefix, 3) == 0 || ft_strncmp(path, prefix,
				3) == 0))
		path += 3;
	while (path && *path == ' ')
		path++;
	while (path && *path == ' ')
		path++;
	strip_whitespace(path);
	return (path);
}

t_texture	*choose_texture(t_data *data)
{
	t_player	*p;

	p = data->player;
	if (p->side == 0)
	{
		if (p->ray_dir_x > 0)
			return (&data->east);
		else
			return (&data->west);
	}
	else
	{
		if (p->ray_dir_y > 0)
			return (&data->south);
		else
			return (&data->north);
	}
}
