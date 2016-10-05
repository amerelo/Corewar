/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:22:16 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/24 16:39:55 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			is_empty_char(char c)
{
	if (c == '\v' ||
		c == '\t' ||
		c == '\f' ||
		c == '\r' ||
		c == ' ')
		return (1);
	return (0);
}

int			is_comment_char(char c)
{
	if (c == COMMENT_CHAR ||
		c == COMMENT_CHAR_2)
		return (1);
	return (0);
}

int			is_label_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}
