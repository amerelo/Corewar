/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 09:05:18 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/14 16:50:17 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		new_flags(const char **s, va_list *ap, t_flags *new)
{
	new->alternative = 0;
	new->zero = 0;
	new->left = 0;
	new->space = 0;
	new->space = 0;
	new->sign = 0;
	new->h = 0;
	new->l = 0;
	new->maj = 0;
	new->j = 0;
	new->z = 0;
	new->padding = 0;
	new->precision = -4;
	new->sep = 0;
	while ((**s == ' ' || (**s >= '0' && **s <= '9') || **s == '#' || **s == '-'
				|| **s == '+' || **s == '.' || **s == 'l' || **s == 'h'
				|| **s == 'j' || **s == 'z' || **s == '*' || **s == '\'')
			&& **s)
	{
		define_flags(s, new, ap);
		*s += 1;
	}
}

static void	define_flags_bis(const char **c, t_flags *flags, va_list *ap)
{
	if (**c == '\'')
		flags->sep = 1;
	else if ((**c >= '1' && **c <= '9') || **c == '*')
		define_iflag(c, &flags->padding, ap, flags);
	else if (**c == '.')
	{
		*c += 1;
		define_iflag(c, &flags->precision, ap, flags);
	}
}

void		define_flags(const char **c, t_flags *flags, va_list *ap)
{
	if (**c == '#')
		flags->alternative = 1;
	else if (**c == '0')
		flags->zero = 1;
	else if (**c == '-')
		flags->left = 1;
	else if (**c == ' ')
		flags->space = 1;
	else if (**c == '+')
		flags->sign = 1;
	else if (**c == 'l')
		flags->l += 1;
	else if (**c == 'h')
		flags->h += 1;
	else if (**c == 'j')
		flags->j = 1;
	else if (**c == 'z')
		flags->z = 1;
	else
		define_flags_bis(c, flags, ap);
}

void		define_iflag(const char **c, int *mod, va_list *ap, t_flags *flags)
{
	*mod = 0;
	if (**c == '*')
	{
		*mod = va_arg(*ap, int);
		if (*mod < 0)
		{
			if (*(*c - 1) == '.')
				*mod = -4;
			else
			{
				*mod = -(*mod);
				flags->left = 1;
			}
		}
	}
	else
	{
		while (**c >= '0' && **c <= '9')
		{
			*mod = *mod * 10 + **c - '0';
			*c += 1;
		}
		*c -= 1;
	}
}
