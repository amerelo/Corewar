/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:43:01 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/03 18:11:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	size_t	index;

	index = 0;
	if (!s || !f
			|| !(new_str = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	while (s[index])
	{
		new_str[index] = (*f)(index, s[index]);
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}
