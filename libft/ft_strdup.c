/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 21:26:53 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/24 22:21:22 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	counter;
	char	*dst;

	counter = 0;
	dst = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (dst)
	{
		while (s1[counter])
		{
			dst[counter] = s1[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (dst);
}
