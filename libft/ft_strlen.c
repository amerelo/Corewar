/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:46:37 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/23 22:06:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	ft_strlen(const char *str)
{
	size_t	value;

	value = 0;
	while (str[value])
		value++;
	return (value);
}
