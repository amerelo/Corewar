/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:11:44 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/08 18:33:40 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char*)s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s += 1;
		if (*s == (char)c)
			return ((char*)s);
	}
	return (NULL);
}
