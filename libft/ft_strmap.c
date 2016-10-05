/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 20:38:36 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/03 18:09:54 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*new_str;
	size_t	index;

	index = 0;
	if (!s || !f
			|| !(new_str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[index])
	{
		new_str[index] = (*f)(s[index]);
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
