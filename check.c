/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:58:38 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/27 16:03:42 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_name(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 4)
	{
		if (str[len - 1] == 'b' && str[len - 2] == 'u' && str[len - 3] == 'c'
			&& str[len - 4] == '.')
			return (1);
	}
	return (printf("Error\n"), 0);
}

char	*namectl(char *xpm)
{
	int		len;
	char	*path;

	path = ft_strtrim(xpm, " \n\t");
	len = ft_strlen(path);
	if (len > 4)
	{
		if (path[len - 1] == 'm' && path[len - 2] == 'p' && path[len - 3] == 'x'
			&& path[len - 4] == '.')
			return (path);
	}
	return (free(path), NULL);
}

int	is_exe(char *str)
{
	char	**split;
	char	*path;
	int		i;
	int		j;

	split = ft_split(str, ' ');
	i = -1;
	while (split[++i])
	{
		if (i > 1)
		{
			j = -1;
			while (split[i][++j])
			{
				if (!jumper(split[i][j]))
					return (1);
			}
		}
	}
	path = namectl(split[1]);
	i = open(path, O_RDONLY);
	if (i < 0)
		return (clear_array(split), free(path), 1);
	return (close(i), clear_array(split), free(path), 0);
}

int	countsome(char *line)
{
    int	a;
    int	b;

    a = 0;
    while (line[a])
    {
        if (line[a] == ',')
        {
            b = a - 1;
            while (b >= 0 && line[b] == ' ')
                b--;
            if (b < 0 || !ft_isdigit(line[b]))
                return (0);
            // Check next non-space character
            b = a + 1;
            while (line[b] == ' ')
                b++;
            if (!line[b] || !ft_isdigit(line[b]))
                return (0);
        }
        a++;
    }
    return (1);
}

int	is_truedigit(char *line, int val, int i, int count)
{
	char	**split;

	if (!line || !countsome(line))
		return (0);
	while (*line && jumper(*line))
		line++;
	if (*line == 'F' || *line == 'C')
		line++;
	while (*line && jumper(*line))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (0);
	while (split[count])
		count++;
	if (count != 3)
		return (clear_array(split), 0);
	while (++i < 3)
	{
		val = rgb_atoi(split[i]);
		if (val < 0 || val > 255)
			return (clear_array(split), 0);
	}
	clear_array(split);
	return (1);
}
