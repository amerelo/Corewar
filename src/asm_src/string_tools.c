/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:28:16 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/24 12:44:41 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			ft_strisdigit(char *str)
{
	int x;

	x = 0;
	if (str[0] == '-')
		++x;
	while (str[x])
	{
		if (!ft_isdigit(str[x]))
			return (0);
		++x;
	}
	return (1);
}

char		*ft_start_trim(char *str)
{
	while (*str)
	{
		if (!is_empty_char(*str))
			return (str);
		str++;
	}
	return (str);
}

/*
** Append src into dst, starting from index in dst
** Return the index of the last copied char + 1
** (where a \0 was put)
*/

int			ft_append(char *dst, int index, char *src)
{
	while (*src)
	{
		dst[index] = *src;
		index++;
		src++;
	}
	dst[index] = 0;
	return (index);
}

int			len_before_empty(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_empty_char(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int			len_before_empty_or_comment(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_empty_char(str[i]))
			return (i);
		if (is_comment_char(str[i]))
			return (i);
		i++;
	}
	return (i);
}
