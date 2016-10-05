/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 02:49:14 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/17 20:35:08 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			begin_conversion(const char **s, va_list *ap, t_flags *flags
		, int *ret)
{
	int r;

	flags->save = 0;
	r = 0;
	if (**s == 'c' || **s == 'C' || **s == 's' || **s == 'S')
		chars_conversion(s, ap, flags, ret);
	else if (**s == 'D' || **s == 'd' || **s == 'i')
		r = signed_conversion(s, ap, flags, ret);
	else if (**s == 'p')
		r = pf_utoa_base(va_arg(*ap, unsigned long long)
				, 16, flags, ret);
	else if (**s == 'o' || **s == 'O' || **s == 'u' || **s == 'x' || **s == 'X'
			|| **s == 'U' || **s == 'b')
		r = unsign_conversion(s, ap, flags, ret);
	else if (**s == 'n')
		*va_arg(*ap, int*) = *ret;
	else if (**s == '\0')
		return (0);
	else
		conv_char(**s, flags, ret);
	return (r);
}

void		chars_conversion(const char **s, va_list *ap, t_flags *flags
		, int *ret)
{
	void	*str;

	if (**s == 'C' || (**s == 'c' && (flags->l & 1)))
		conv_lchar(va_arg(*ap, wint_t), flags, ret);
	else if (**s == 'c' && !(flags->l & 1))
		conv_char(va_arg(*ap, int), flags, ret);
	else if (**s == 'S' || (**s == 's' && (flags->l & 1)))
	{
		if (!(str = va_arg(*ap, wchar_t*)))
			conv_str("(null)", flags, ret);
		else
			conv_lstr(str, flags, ret);
	}
	else if (**s == 's' && !(flags->l & 1))
	{
		if (!(str = va_arg(*ap, char*)))
			conv_str("(null)", flags, ret);
		else
			conv_str(str, flags, ret);
	}
}

int			signed_conversion(const char **s, va_list *ap, t_flags *flags
		, int *ret)
{
	int	r;

	r = 0;
	if (**s == 'D' || (!flags->j && !flags->z && (flags->l & 1)))
		r = pf_itoa(va_arg(*ap, long), flags, ret);
	else if (!flags->h && !flags->l && !flags->j && !flags->z)
		r = pf_itoa(va_arg(*ap, int), flags, ret);
	else if (!flags->l && !flags->j && !flags->z && (flags->h & 1))
		r = pf_itoa((short)va_arg(*ap, int), flags, ret);
	else if (!flags->l && !flags->j && !flags->z && flags->h && !(flags->h & 1))
		r = pf_itoa((char)va_arg(*ap, int), flags, ret);
	else if (!flags->j && !flags->z && flags->l && !(flags->l & 1))
		r = pf_itoa(va_arg(*ap, long long), flags, ret);
	else if (flags->z || flags->j)
		r = pf_itoa(va_arg(*ap, intmax_t), flags, ret);
	return (r);
}

static int	init_base(char c)
{
	int base;

	if (c == 'o' || c == 'O')
		base = 8;
	else if (c == 'x' || c == 'X')
		base = 16;
	else if (c == 'b')
		base = 2;
	else
		base = 10;
	return (base);
}

int			unsign_conversion(const char **s, va_list *ap, t_flags *flags
		, int *ret)
{
	int r;

	r = 0;
	if (**s == 'O' || **s == 'U' || ((flags->l & 1) && !flags->j && !flags->z))
		r = pf_utoa_base(va_arg(*ap, unsigned long),
				init_base(**s), flags, ret);
	else if (flags->h && !(flags->h & 1) && !flags->l && !flags->j && !flags->z)
		r = pf_utoa_base((unsigned char)va_arg(*ap, unsigned int)
				, init_base(**s), flags, ret);
	else if ((flags->h & 1) && !flags->j && !flags->l && !flags->z)
		r = pf_utoa_base((unsigned short)va_arg(*ap, unsigned int)
				, init_base(**s), flags, ret);
	else if (!flags->h && !flags->j && !flags->l && !flags->z)
		r = pf_utoa_base(va_arg(*ap, unsigned int), init_base(**s)
				, flags, ret);
	else if (!flags->j && !flags->z && flags->l && !(flags->l & 1))
		r = pf_utoa_base(va_arg(*ap, unsigned long long)
				, init_base(**s), flags, ret);
	else if (!flags->z && flags->j)
		r = pf_utoa_base(va_arg(*ap, uintmax_t), init_base(**s)
				, flags, ret);
	else if (flags->z)
		r = pf_utoa_base(va_arg(*ap, size_t), init_base(**s), flags
				, ret);
	return (r);
}
