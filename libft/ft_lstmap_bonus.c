/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:23:20 by skaynar           #+#    #+#             */
/*   Updated: 2024/10/28 13:37:01 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*new;
	void	*tc;

	if (!lst || !f || !del)
		return (NULL);
	root = NULL;
	while (lst)
	{
		tc = f(lst->content);
		if (!tc)
			return (ft_lstclear(&root, del), NULL);
		new = ft_lstnew(tc);
		if (!new)
			return (ft_lstclear(&root, del), del(tc), NULL);
		ft_lstadd_back(&root, new);
		lst = lst->next;
	}
	return (root);
}
