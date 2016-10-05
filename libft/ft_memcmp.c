/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:50:26 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/30 03:08:56 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1str;
	unsigned char	*s2str;

	s1str = (unsigned char*)s1;
	s2str = (unsigned char*)s2;
	if (n)
	{
		while (n - 1 && *s1str == *s2str)
		{
			s1str += 1;
			s2str += 1;
			n--;
		}
		return (*s1str - *s2str);
	}
	else
		return (0);
}
