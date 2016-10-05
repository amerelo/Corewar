/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 16:46:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/07/25 00:55:14 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <locale.h>
# include <stdint.h>

typedef struct	s_flags
{
	char				alternative;
	char				zero;
	char				left;
	char				space;
	char				sign;
	int					h;
	int					l;
	char				j;
	char				z;
	char				sep;
	char				maj;
	int					padding;
	int					precision;
	size_t				save;
	char				c;
}				t_flags;

int				ft_printf(const char *format, ...);
int				ft_vprintf(const char *format, va_list *ap);
int				read_id(const char **format, va_list *ap, int *ret);
void			new_flags(const char **s, va_list *ap, t_flags *n);
void			define_flags(const char **c, t_flags *flags, va_list *ap);
void			define_iflag(const char **c, int *mod, va_list *ap, t_flags *f);
int				begin_conversion(const char **s, va_list *ap
		, t_flags *nw, int *ret);
void			chars_conversion(const char **s, va_list *ap
		, t_flags *nw, int *ret);
int				signed_conversion(const char **s, va_list *ap
		, t_flags *nw, int *ret);
int				unsign_conversion(const char **s, va_list *ap
		, t_flags *nw, int *ret);
void			pf_putchar(int c, int *ret);
void			pf_putwchar(wint_t c, int *ret);
void			conv_char(int c, t_flags *flags, int *ret);
void			conv_lchar(wint_t c, t_flags *flags, int *ret);
void			conv_str(char *str, t_flags *flags, int *ret);
void			conv_lstr(wchar_t *str, t_flags *flags, int *ret);
void			pf_putwstr(wchar_t *str, t_flags *flags, int *ret);
void			pf_putstr(char *str, t_flags *flags, int *ret);
void			conv_integral(char **str, t_flags *flags, int *ret);
void			conv_unsigned(char **str, int base, t_flags *flags
		, int *ret);
int				pf_itoa(intmax_t i, t_flags *flags, int *ret);
int				pf_utoa_base(size_t i, int base, t_flags *flags
		, int *ret);
size_t			ft_strlen(const char *str);
char			*ft_strchar(size_t n, char c);
void			ft_putstr(const char *s);

#endif
