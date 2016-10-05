/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:06:17 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/28 03:17:27 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (n - 1 && *(unsigned char*)s1 == *(unsigned char*)s2
				&& *(unsigned char*)s1)
		{
			s1 += 1;
			s2 += 1;
			n--;
		}
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	}
	else
		return (0);
}
