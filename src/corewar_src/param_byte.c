/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_byte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 01:54:07 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/21 01:55:04 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	read_value(char bin, int ind)
{
	if (bin == IND_CODE)
		return (IND_SIZE);
	else if (bin == REG_CODE)
		return (REG_SIZE_VM);
	else if (bin == DIR_CODE)
		return (ind ? IND_SIZE : DIR_SIZE);
	else
		return (0);
}

static char	check_value(char tab, char bin)
{
	if (bin == REG_CODE)
		return (tab & T_REG);
	else if (bin == DIR_CODE)
		return (tab & T_DIR);
	else if (bin == IND_CODE)
		return (tab & T_IND);
	else
		return (0);
}

char		read_p_byte(char p_byte, char *tab, char *size, int i)
{
	*size = (tab[0] ? read_value((p_byte & 0xc0) >> 6, i) : 0)
			+ (tab[1] ? read_value((p_byte & 0x30) >> 4, i) : 0)
			+ (tab[2] ? read_value((p_byte & 0x0c) >> 2, i) : 0)
			+ (tab[3] ? read_value((p_byte & 0x03), i) : 0);
	if ((tab[0] && !check_value(tab[0], (p_byte & 0xc0) >> 6))
			|| (tab[1] && !check_value(tab[1], (p_byte & 0x30) >> 4))
			|| (tab[2] && !check_value(tab[2], (p_byte & 0x0c) >> 2))
			|| (tab[3] && !check_value(tab[3], (p_byte & 0x03))))
		return (1);
	return (0);
}
