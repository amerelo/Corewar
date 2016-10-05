/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 05:17:57 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/03 17:52:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	ch_sign(int n)
{
	if (n > 0)
		return ('+');
	else if (n < 0)
		return ('-');
	return ('0');
}

char		*ft_itoa(int n)
{
	char			sign;
	char			*str;
	short			index;
	unsigned int	tmp;
	unsigned int	v;

	sign = ch_sign(n);
	v = sign == '-' ? -n : n;
	tmp = v;
	index = sign != '+' ? 1 : 0;
	while (tmp)
	{
		index++;
		tmp /= 10;
	}
	if (!(str = ft_strnew(index)))
		return (NULL);
	str[0] = sign;
	while (v)
	{
		index--;
		str[index] = v % 10 + '0';
		v /= 10;
	}
	return (str);
}
