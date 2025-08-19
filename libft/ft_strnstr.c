/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:56:17 by skaynar           #+#    #+#             */
/*   Updated: 2024/10/25 16:55:02 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str1 && !len)
		return (NULL);
	if (str2 == str1 || str2[0] == 0)
		return ((char *)str1);
	while (str1[i] != 0 && i < len)
	{
		if (str1[i] == str2[j])
		{
			while (str1[i + j] == str2[j] && i + j < len)
			{
				if (str2[j + 1] == 0)
					return ((char *)str1 + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
