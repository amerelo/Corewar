/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:19:20 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/16 16:19:39 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

/*
** Write logs if FLAG_LOGS is set
*/

int			ft_logs(t_asm *env, const char *format, ...)
{
	va_list		ap;
	int			res;

	res = 0;
	va_start(ap, format);
	if (env->flags & FLAG_LOGS)
		res = ft_vprintf(format, &ap);
	va_end(ap);
	return (res);
}
