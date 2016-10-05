/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:24:37 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/16 16:24:58 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			is_empty(char *str)
{
	while (*str)
	{
		if (!is_empty_char(*str))
			return (0);
		str++;
	}
	return (1);
}

int			is_comment(char *str)
{
	str = ft_start_trim(str);
	if (!is_comment_char(*str))
		return (0);
	return (1);
}
