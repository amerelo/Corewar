/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:42:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/21 18:58:58 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putchar_fd(int i, int fd)
{
	if (i < 0x80)
		write(fd, &i, 1);
	else if (i < 0x800)
	{
		putchar_fd(i >> 6 | 0xC0, fd);
		putchar_fd((i & 0xBF) | 0x80, fd);
	}
	else if (i < 0x10000)
	{
		putchar_fd(i >> 12 | 0xE0, fd);
		putchar_fd(((i >> 6) & 0xBF) | 0x80, fd);
		putchar_fd((i & 0xBF) | 0x80, fd);
	}
	else
	{
		putchar_fd(i >> 18 | 0xF0, fd);
		putchar_fd(((i >> 12) & 0xBF) | 0x80, fd);
		putchar_fd(((i >> 6) & 0xBF) | 0x80, fd);
		putchar_fd((i & 0xBF) | 0x80, fd);
	}
}
