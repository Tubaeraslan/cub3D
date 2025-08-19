/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:16:08 by skaynar           #+#    #+#             */
/*   Updated: 2024/10/28 15:55:53 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)dest;
	while (n > 0)
	{
		*s = (unsigned char)c;
		s++;
		n--;
	}
	return (dest);
}
