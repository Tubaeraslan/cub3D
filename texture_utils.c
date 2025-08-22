/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:48:55 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 18:19:22 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void strip_trailing_whitespace(char *str)
{
	if (!str)
        return;
	int len = ft_strlen(str);
	while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == '\t'))
		str[--len] = '\0';
}

char *parse_texture_path(char *path, const char *prefix)
{
    if (path && (strncmp(path, prefix, 3) == 0 || strncmp(path, prefix, 3) == 0))
        path += 3;
    while (path && *path == ' ')
        path++;
    while (path && *path == ' ')
        path++;
    strip_trailing_whitespace(path);
    return path;
}

t_texture *choose_texture(t_data *data)
{
	t_player *p = data->player;
	if (p->side == 0)
		return (p->rayDirX > 0) ? &data->east : &data->west;
	else
		return (p->rayDirY > 0) ? &data->south : &data->north;
}
