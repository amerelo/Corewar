/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 03:36:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/14 20:46:34 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		conv_char(int c, t_flags *flags, int *ret)
{
	flags->padding -= 1;
	while (!flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		flags->zero ? pf_putchar('0', ret) : pf_putchar(' ', ret);
	}
	pf_putchar(c, ret);
	while (flags->left && flags->padding > 0)
	{
		flags->padding -= 1;
		pf_putchar(' ', ret);
	}
}

void		conv_lchar(wint_t c, t_flags *flags, int *ret)
{
	if (c < 0x80)
		flags->padding -= 1;
	else if (c < 0x800)
		flags->padding -= 2;
	else if (c < 0x10000)
		flags->padding -= 3;
	else
		flags->padding -= 4;
	while (!flags->left && flags->padding > 0)
	{
		flags->padding > 0 ? flags->padding -= 1 : flags->padding;
		flags->zero ? pf_putchar('0', ret) : pf_putchar(' ', ret);
	}
	pf_putwchar(c, ret);
	while (flags->left && flags->padding > 0)
	{
		flags->padding > 0 ? flags->padding -= 1 : flags->padding;
		pf_putchar(' ', ret);
	}
}

void		pf_putchar(int c, int *ret)
{
	write(1, (unsigned char*)&c, 1);
	*ret += 1;
}

void		pf_putwchar(wint_t i, int *ret)
{
	if ((wchar_t)i < 0x80)
		pf_putchar((wchar_t)i, ret);
	else if ((wchar_t)i < 0x800)
	{
		pf_putchar((wchar_t)i >> 6 | 0xC0, ret);
		pf_putchar(((wchar_t)i & 0xBF) | 0x80, ret);
	}
	else if ((wchar_t)i < 0x10000)
	{
		pf_putchar((wchar_t)i >> 12 | 0xE0, ret);
		pf_putchar((((wchar_t)i >> 6) & 0xBF) | 0x80, ret);
		pf_putchar(((wchar_t)i & 0xBF) | 0x80, ret);
	}
	else
	{
		pf_putchar((wchar_t)i >> 18 | 0xF0, ret);
		pf_putchar((((wchar_t)i >> 12) & 0xBF) | 0x80, ret);
		pf_putchar((((wchar_t)i >> 6) & 0xBF) | 0x80, ret);
		pf_putchar(((wchar_t)i & 0xBF) | 0x80, ret);
	}
}
