/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 21:26:53 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/30 01:06:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	counter;
	char	*dst;

	counter = 0;
	dst = (char*)malloc(sizeof(char) * n + 1);
	if (dst)
	{
		while (s1[counter] && n--)
		{
			dst[counter] = s1[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (dst);
}
