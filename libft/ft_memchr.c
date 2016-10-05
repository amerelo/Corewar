/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 00:21:49 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/29 03:41:25 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			counter;

	counter = 0;
	while (counter < n)
	{
		if (((unsigned char*)s)[counter] == (unsigned char)c)
			return (&((unsigned char*)s)[counter]);
		counter++;
	}
	return (NULL);
}
