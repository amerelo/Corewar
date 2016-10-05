/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:10:27 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/23 16:18:56 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int		test_param(t_asm *parsed_champ, t_op op, t_instruction *element)
{
	int x;

	x = 0;
	while (element->params[x])
		++x;
	if (op.size != x)
		return (!(parsed_champ->error_type = BAD_ARG_COUNT));
	x = 0;
	while (element->params_types[x])
	{
		if (x > op.size)
			return (!(parsed_champ->error_type = BAD_ARG_COUNT));
		if (!(element->params_types[x] & op.params_types[x]))
			return (!(parsed_champ->error_type = BAD_ARG_TYPE));
		++x;
	}
	return (1);
}

char	add_opc(t_list *element)
{
	int				x;
	int				i;
	char			res;
	t_instruction	*tmp;

	i = 0;
	x = 3;
	res = 0;
	tmp = element->content;
	while (i < 4)
	{
		if (tmp->params_types[i] & T_REG)
			res += 1 << (x * 2);
		else if (tmp->params_types[i] & T_DIR)
			res += 2 << (x * 2);
		else if (tmp->params_types[i] & T_IND)
			res += 3 << (x * 2);
		++i;
		--x;
	}
	return (res);
}

int		cor_mod(t_asm *parsed_champ, t_list **element)
{
	t_list	*tmp;
	int		x;

	tmp = *element;
	while (tmp)
	{
		if (tmp->content_size == sizeof(t_instruction))
		{
			((t_instruction*)(tmp->content))->hexdump =
			(char*)ft_memalloc(((t_instruction*)(tmp->content))->size);
			((t_instruction*)(tmp->content))->hexdump[0] =
			((t_instruction*)(tmp->content))->opcode;
			x = 1;
			if ((((t_instruction*)(tmp->content))->op_type->params_byte))
			{
				((t_instruction*)(tmp->content))->hexdump[1] = add_opc(tmp);
				x = 2;
			}
			if (!test_arg(&x, parsed_champ, &tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		compile_champ2(t_asm *parsed_champ, t_list *tmp, t_list *prev)
{
	tmp = parsed_champ->elements;
	while (tmp)
	{
		if (tmp->content_size == sizeof(t_instruction) &&
		!test_in(parsed_champ, tmp->content))
			return (0);
		if (tmp->content_size == sizeof(t_instruction) && prev)
		{
			((t_instruction*)(tmp->content))->address =
			((t_instruction*)(prev->content))->address;
		}
		if (tmp->content_size == sizeof(t_instruction))
		{
			((t_instruction*)(tmp->content))->address +=
			((t_instruction*)(tmp->content))->size;
		}
		if (tmp->content_size == sizeof(t_instruction))
			prev = tmp;
		tmp = tmp->next;
	}
	parsed_champ->champ_size = ((t_instruction*)(prev->content))->address;
	return (1);
}

int		compile_champ(t_asm *parsed_champ)
{
	t_list	*tmp;
	t_list	*prev;

	prev = NULL;
	tmp = parsed_champ->elements;
	while (tmp)
	{
		if (tmp->content_size == sizeof(t_instruction) &&
		!get_types(parsed_champ, tmp->content))
			return (0);
		tmp = tmp->next;
	}
	if (!compile_champ2(parsed_champ, tmp, prev))
		return (0);
	tmp = parsed_champ->elements;
	if (!cor_mod(parsed_champ, &tmp))
		return (0);
	return (1);
}
