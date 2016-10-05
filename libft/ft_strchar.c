/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 12:32:18 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/12 17:42:22 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_strchar(size_t n, char c)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	new[n] = '\0';
	while (n)
	{
		n--;
		new[n] = c;
	}
	return (new);
}
