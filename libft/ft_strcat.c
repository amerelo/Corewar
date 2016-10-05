/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:13:14 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/25 16:28:24 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	null;
	size_t	index;

	index = 0;
	null = ft_strlen(s1);
	while (s2[index])
	{
		s1[null + index] = s2[index];
		index++;
	}
	s1[null + index] = '\0';
	return (s1);
}
