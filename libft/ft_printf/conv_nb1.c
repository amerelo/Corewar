/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_nb1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 02:42:44 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/21 14:48:34 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ct_digit(size_t nb, int base, t_flags *flags, char sign)
{
	int		counter;
	size_t	x;

	counter = 0;
	x = nb;
	if (flags->sep && *localeconv()->thousands_sep)
		while (x /= 1000)
			counter += 1;
	if (sign == '0' && flags->precision)
		counter += 1;
	if (base == 8 && flags->alternative
			&& (nb || (!nb && flags->precision == 0)))
		counter += 1;
	while (nb)
	{
		counter += 1;
		nb /= base;
	}
	if (counter < flags->precision)
		counter = flags->precision;
	if (sign == '-')
		counter += 1;
	return (counter);
}

static void	set_digits(size_t u, int index, t_flags *flags, char *str)
{
	int	rep;

	rep = 0;
	while (u)
	{
		index--;
		if (flags->sep && *localeconv()->thousands_sep && rep % 4 == 3)
			str[index] = *localeconv()->thousands_sep;
		else
		{
			str[index] = (u % 10) + '0';
			u /= 10;
		}
		rep++;
	}
}

int			pf_itoa(intmax_t nb, t_flags *flags, int *ret)
{
	char		*str;
	char		sign;
	int			index;
	size_t		u;

	sign = nb == 0 ? '0' : '+';
	sign = nb < 0 ? '-' : sign;
	u = nb < 0 ? -nb : nb;
	index = ct_digit(u, 10, flags, sign);
	if (!(str = ft_strchar(index, '0')))
		return (1);
	str[0] = sign == '-' ? '-' : str[0];
	set_digits(u, index, flags, str);
	conv_integral(&str, flags, ret);
	return (0);
}

int			pf_utoa_base(size_t n, int b, t_flags *flags, int *ret)
{
	char	*str;
	char	sign;
	int		index;

	flags->save = n;
	sign = n == 0 ? '0' : '+';
	index = ct_digit(n, b, flags, sign);
	if (!(str = ft_strchar(index, '0')))
		return (1);
	while (n)
	{
		index--;
		if (flags->maj)
			str[index] = n % b >= 10 ? (n % b) + 'A' - 10 : (n % b) + '0';
		else
			str[index] = n % b >= 10 ? (n % b) + 'a' - 10 : (n % b) + '0';
		n /= b;
	}
	conv_unsigned(&str, b, flags, ret);
	return (0);
}
