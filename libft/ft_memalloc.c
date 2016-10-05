/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:46:48 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/24 15:43:04 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memory;

	memory = (char*)malloc(sizeof(char) * size);
	if (memory)
	{
		while (size)
		{
			size--;
			memory[size] = 0;
		}
	}
	return (memory);
}
