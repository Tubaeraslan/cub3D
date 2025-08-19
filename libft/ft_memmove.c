/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:35:15 by skaynar           #+#    #+#             */
/*   Updated: 2024/10/28 16:27:30 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (dst);
	if ((char *)dst > (char *)src)
	{
		i = len - 1;
		while (i >= 0)
		{
			*((char *)dst + i) = *((char *)src + i);
			i--;
		}
	}
	else
	{
		ft_memcpy(dst, (char *)src, len);
	}
	return (dst);
}
