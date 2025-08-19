/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:41:01 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/16 13:16:00 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_before(char *repo)
{
	int		i;
	char	*line;

	i = 0;
	if (!repo[i])
		return (NULL);
	while (repo[i] && repo[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (repo[i] && repo[i] != '\n')
	{
		line[i] = repo[i];
		i++;
	}
	if (repo[i] == '\n')
	{
		line[i] = repo[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_after(char *repo)
{
	int		i;
	int		j;
	char	*new_repo;

	i = 0;
	while (repo[i] && repo[i] != '\n')
		i++;
	if (!repo[i] || !repo)
	{
		free(repo);
		return (NULL);
	}
	new_repo = (char *)malloc(sizeof(char) * (ft_strlen(repo) - i + 1));
	if (!new_repo)
		return (NULL);
	i++;
	j = 0;
	while (repo[i])
		new_repo[j++] = repo[i++];
	new_repo[j] = '\0';
	free(repo);
	return (new_repo);
}

static char	*ft_join(char *repo, char *buffer, int fd)
{
	int	count;

	count = 1;
	while (!ft_strchr(repo, '\n') && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free(repo);
			return (NULL);
		}
		buffer[count] = '\0';
		repo = gnl_strjoin(repo, buffer);
	}
	free(buffer);
	return (repo);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*repo;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	repo = ft_join(repo, buffer, fd);
	if (!repo)
		return (NULL);
	line = ft_before(repo);
	repo = ft_after(repo);
	return (line);
}
