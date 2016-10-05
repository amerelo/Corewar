/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 00:18:50 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/03 18:17:57 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	size_t	index;

	index = 0;
	if (!s1 || !s2
			|| !(new = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (*s1)
	{
		new[index] = *s1;
		s1 += 1;
		index++;
	}
	while (*s2)
	{
		new[index] = *s2;
		s2 += 1;
		index++;
	}
	new[index] = '\0';
	return (new);
}
