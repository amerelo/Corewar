/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_nb2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 06:27:17 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/14 16:19:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	conv_integral_bis(char *str, t_flags *flags, int *ret)
{
	if ((!flags->zero || (flags->zero && flags->precision >= 0))
			&& (*str == '-' || flags->sign) && !flags->left)
		*str == '-' ? pf_putchar('-', ret) : pf_putchar('+', ret);
	*str == '-' ? str += 1 : str;
	ft_putstr(str);
	*ret += ft_strlen(str);
	while (flags->padding > 0 && flags->left)
	{
		pf_putchar(' ', ret);
		flags->padding -= 1;
	}
}

void		conv_integral(char **str, t_flags *flags, int *ret)
{
	if (**str == '-' || flags->sign || flags->space)
		flags->padding -= 1;
	if (flags->space && !flags->sign && **str != '-')
		pf_putchar(' ', ret);
	if (((flags->zero && flags->precision < 0) || flags->left)
			&& (**str == '-' || flags->sign))
		**str == '-' ? pf_putchar('-', ret) : pf_putchar('+', ret);
	flags->padding -= **str == '-' ? ft_strlen(*str + 1) : ft_strlen(*str);
	while (flags->padding > 0 && !flags->left)
	{
		flags->zero && flags->precision < 0 ?
			pf_putchar('0', ret) : pf_putchar(' ', ret);
		flags->padding -= 1;
	}
	conv_integral_bis(*str, flags, ret);
	free(*str);
}

static void	conv_unsigned_bis(char *str, int base, t_flags *flags, int *ret)
{
	if (base == 16 && flags->alternative && (flags->save || flags->c == 'p')
			&& ((!flags->zero || (flags->zero && flags->precision >= 0))
				&& !flags->left))
	{
		flags->maj ? write(1, "0X", 2) : write(1, "0x", 2);
		*ret += 2;
	}
	ft_putstr(str);
	*ret += ft_strlen(str);
	while (flags->padding > 0 && flags->left)
	{
		pf_putchar(' ', ret);
		flags->padding -= 1;
	}
}

void		conv_unsigned(char **str, int base, t_flags *flags, int *ret)
{
	if (base == 16 && flags->alternative && (flags->save || flags->c == 'p'))
		flags->padding -= 2;
	if (base == 16 && flags->alternative && (flags->save || flags->c == 'p')
			&& ((flags->zero && flags->precision < 0) || flags->left))
	{
		flags->maj ? write(1, "0X", 2) : write(1, "0x", 2);
		*ret += 2;
	}
	flags->padding -= ft_strlen(*str);
	while (flags->padding > 0 && !flags->left)
	{
		flags->zero && flags->precision < 0 ?
			pf_putchar('0', ret) : pf_putchar(' ', ret);
		flags->padding -= 1;
	}
	conv_unsigned_bis(*str, base, flags, ret);
	free(*str);
}
