/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfnc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:37:41 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/17 13:04:14 by skaynar          ###   ########.fr       */
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

t_map	*ft_mapnew(void *content)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->map_line = content;
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