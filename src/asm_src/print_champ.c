/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:17:24 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/16 16:17:46 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

void		print_head(t_asm *parsed_champ)
{
	ft_printf("name : %s\n", parsed_champ->head.prog_name);
	ft_printf("comment : %s\n", parsed_champ->head.comment);
}

void		print_label(t_label *label)
{
	ft_printf("label named : %s\n", label->name);
}

void		print_instr(t_instruction *instr)
{
	int		i;

	ft_printf("instruction : %s\n", instr->op_type->name);
	i = 0;
	while (i < instr->op_type->size)
	{
		ft_printf("param %d contains : %s\n", i, instr->params[i]);
		i++;
	}
}

void		print_elem(t_list *elem)
{
	if (elem->content_size == sizeof(t_label))
	{
		print_label(elem->content);
	}
	else if (elem->content_size == sizeof(t_instruction))
	{
		print_instr(elem->content);
	}
	else
		ft_printf("element unknown\n");
}

void		print_champ(t_asm *parsed_champ)
{
	print_head(parsed_champ);
	ft_lstiter(parsed_champ->elements, print_elem);
}
