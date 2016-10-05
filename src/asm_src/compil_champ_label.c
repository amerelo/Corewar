/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compil_champ_label.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 22:38:13 by amerelo           #+#    #+#             */
/*   Updated: 2016/05/23 16:11:33 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int		distance_between(t_asm *champ, t_instruction *el, int p, int *adrs)
{
	t_list	*tmp;
	char	*label;

	tmp = champ->elements;
	label = ft_strchr(el->params[p], ':');
	label++;
	while (tmp)
	{
		if (tmp->content_size == sizeof(t_instruction))
			*adrs = ((t_instruction*)(tmp->content))->address;
		if ((tmp->content_size == sizeof(t_label)) &&
		ft_strequ(((t_label*)(tmp->content))->name, label))
			return (1);
		tmp = tmp->next;
	}
	return (!(champ->error_type = UNKNOWN_LABEL));
}

int		find_label(t_asm *champ, t_instruction *element, int p, int *dis)
{
	int	address;

	address = 0;
	if (!distance_between(champ, element, p, &address))
		return (0);
	if (address <= element->address)
		*dis = address - element->address + element->size;
	else
		*dis = address - element->address + element->size;
	return (1);
}

int		dis_to_hex(t_asm *parsed_champ, t_instruction *element, int *i, int p)
{
	int dis;

	dis = 0;
	if (!find_label(parsed_champ, element, p, &dis))
		return (0);
	if (element->op_type->index_size || element->params_types[p] & T_IND)
	{
		element->hexdump[(*i)++] = (dis & 0x0000ff00) >> 8;
		element->hexdump[*i] = dis & 0x000000ff;
	}
	else
	{
		element->hexdump[(*i)++] = (dis & 0xff000000) >> 24;
		element->hexdump[(*i)++] = (dis & 0x00ff0000) >> 16;
		element->hexdump[(*i)++] = (dis & 0x0000ff00) >> 8;
		element->hexdump[*i] = dis & 0x000000ff;
	}
	return (1);
}
