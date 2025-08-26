/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:55 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/26 13:22:49 by teraslan         ###   ########.fr       */
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
	int	i;

	if (!path || !prefix)
		return (NULL);
	i = 0;
	if (ft_strncmp(path, prefix, ft_strlen(prefix)) == 0)
		i += ft_strlen(prefix);
	while (jumper(path[i]))
		i++;
	strip_whitespace(path + i);
	return (path + i);
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
