/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:37:01 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/25 16:50:49 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	null;
	size_t	index;

	null = ft_strlen(s1);
	index = 0;
	while (s2[index] && index < n)
	{
		s1[index + null] = s2[index];
		index++;
	}
	s1[index + null] = '\0';
	return (s1);
}
