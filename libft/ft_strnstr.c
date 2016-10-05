/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:26:55 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/25 21:39:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	index_1;
	size_t	index_2;

	index_1 = 0;
	if (!*s2)
		return ((char*)s1);
	while (index_1 < n && s1[index_1] != '\0')
	{
		if (s1[index_1] == *s2)
		{
			index_2 = 0;
			while (s1[index_1 + index_2] == s2[index_2]
					&& index_1 + index_2 < n)
			{
				index_2++;
				if (!s2[index_2])
					return ((char*)&s1[index_1]);
			}
		}
		index_1++;
	}
	return (NULL);
}
