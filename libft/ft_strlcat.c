/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:49:24 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/26 19:26:42 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	while (dst[index])
	{
		index++;
		if (index > size)
			return (size + ft_strlen(src));
	}
	while (*src && index < size - 1)
	{
		dst[index] = *src;
		index++;
		src += 1;
	}
	dst[index] = '\0';
	return (ft_strlen(src) + ft_strlen(dst));
}
