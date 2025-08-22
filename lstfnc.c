/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfnc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:41 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/21 18:08:58 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_map	*ft_maplast(t_map *lst)
// {
// 	t_map	*current;

// 	if (!lst)
// 		return (NULL);
// 	current = lst;
// 	while (current->next != NULL)
// 		current = current->next;
// 	return (current);
// }

int	ft_mapsize(t_map *lst)
{
	int		i;
	t_map	*current;

	if (!lst)
		return (0);
	current = lst;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

t_map	*ft_mapnew(char *content, int line_num)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map_line = ft_strdup(content);
    new->num = line_num;
	new->next = NULL;
	return (new);
}

void map_add_back(t_map **lst, t_map *new)
{
    t_map *tmp;

    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}