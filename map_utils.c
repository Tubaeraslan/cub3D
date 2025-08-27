/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:27:13 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/27 14:36:37 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_all_edge(char **a, int i, int j, char c)
{
	if (i == 0)
		return (1);
	if (i > 0 && a[i - 1][j] && a[i - 1][j] != '1'
		&& a[i - 1][j] != '0' && a[i - 1][j] != c)
		return (1);
	if (a[i + 1] && a[i + 1][j] != '1'
		&& a[i + 1][j] != '0' && a[i + 1][j] != c)
		return (1);
	if (j > 0 && a[i][j - 1] && a[i][j - 1] != '1'
		&& a[i][j - 1] != '0' && a[i][j - 1] != c)
		return (1);
	if (a[i][j + 1] && a[i][j + 1] && a[i][j + 1] != '1'
		&& a[i][j + 1] != '0' && a[i][j + 1] != c)
		return (1);
	if (!a[i + 1] || !a[i - 1] || !a[i][j + 1] || !a[i][j - 1])
		return (1);
	return (0);
}

int	ff_empty(char **a, char c)
{
	int	i;
	int	j;

	i = 0;
	while (a[i])
	{
		j = 0;
		while (a[i][j])
		{
			if (a[i][j] == '0')
			{
				if (check_all_edge(a, i, j, c))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ff_double(char **map, int x, int y, t_data *data)
{
	int	row_len;

	if (x < 0 || x >= data->high || !map[x])
		return ;
	row_len = (int)ft_strlen(map[x]);
	if (y < 0 || y >= row_len)
		return ;
	if (map[x][y] != '0' && map[x][y] != '1'
		&& map[x][y] != data->player->start_pos)
		return ;
	map[x][y] = '*';
	ff_double(map, x + 1, y, data);
	ff_double(map, x - 1, y, data);
	ff_double(map, x, y + 1, data);
	ff_double(map, x, y - 1, data);
}
