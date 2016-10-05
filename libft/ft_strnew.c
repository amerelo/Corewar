/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:58:16 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/03 17:51:43 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	size += 1;
	str = (char*)malloc(sizeof(char) * size);
	if (str)
	{
		while (size)
		{
			size--;
			str[size] = 0;
		}
	}
	return (str);
}
