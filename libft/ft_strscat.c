/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 04:48:24 by flevesqu          #+#    #+#             */
/*   Updated: 2016/03/03 18:05:21 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strscat(char *s1, char *s2)
{
	char	*new;
	size_t	index;

	index = 0;
	if (!(new = (char*)malloc(sizeof(char)
					* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[index])
	{
		new[index] = s1[index];
		index++;
	}
	while (*s2)
	{
		new[index] = *s2;
		index++;
		s2 += 1;
	}
	new[index] = '\0';
	free(s1);
	return (new);
}
