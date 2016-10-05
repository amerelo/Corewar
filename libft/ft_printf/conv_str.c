/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 06:58:09 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/11 03:28:35 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	nb_bytes(wchar_t c)
{
	if (c < 0x80)
		return (1);
	else if (c >= 0x80 && c < 0x800)
		return (2);
	else if (c >= 0x800 && c < 0x10000)
		return (3);
	else
		return (4);
}

void		conv_str(char *str, t_flags *flags, int *ret)
{
	int		counter;
	char	*tmp;

	counter = 0;
	tmp = str;
	while (*tmp && (counter < flags->precision || flags->precision < 0))
	{
		counter++;
		tmp += 1;
	}
	flags->padding -= counter;
	while (!flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		flags->zero ? pf_putchar('0', ret) : pf_putchar(' ', ret);
	}
	pf_putstr(str, flags, ret);
	while (flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		pf_putchar(' ', ret);
	}
}

void		conv_lstr(wchar_t *str, t_flags *flags, int *ret)
{
	int		counter;
	wchar_t	*tmp;

	tmp = str;
	counter = 0;
	while (*tmp && (counter < flags->precision || flags->precision < 0))
	{
		counter += nb_bytes(*tmp);
		tmp += 1;
	}
	if (flags->precision > 0 && counter > flags->precision)
		counter -= nb_bytes(*(tmp - 1));
	flags->padding -= counter;
	while (!flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		flags->zero ? pf_putchar('0', ret) : pf_putchar(' ', ret);
	}
	pf_putwstr(str, flags, ret);
	while (flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		pf_putchar(' ', ret);
	}
}

void		pf_putstr(char *str, t_flags *flags, int *ret)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*ret += 6;
		return ;
	}
	while (*str && flags->precision)
	{
		if (flags->precision > 0)
			flags->precision -= 1;
		if (flags->precision >= 0 || flags->precision == -4)
			pf_putchar(*str, ret);
		str += 1;
	}
}

void		pf_putwstr(wchar_t *str, t_flags *flags, int *ret)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*ret += 6;
		return ;
	}
	while (*str && (flags->precision > 0 || flags->precision == -4))
	{
		if (flags->precision > 0)
			flags->precision -= nb_bytes(*str);
		if (flags->precision >= 0 || flags->precision == -4)
			pf_putwchar(*str, ret);
		str += 1;
	}
}
