/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compil_champ_find_and_set.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 22:45:41 by amerelo           #+#    #+#             */
/*   Updated: 2016/05/23 16:17:00 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

t_op	*find_op(t_asm *parsed_champ, int opcode)
{
	int	x;

	x = 0;
	while (x < 17)
	{
		if (parsed_champ->ops[x].opcode == opcode)
			return (&(parsed_champ)->ops[x]);
		++x;
	}
	return (NULL);
}

int		find_size(t_op op, t_instruction *element)
{
	int i;
	int x;

	i = 0;
	x = 1;
	if (op.params_byte)
		++x;
	while (i < 4)
	{
		if (element->params_types[i] & 0x1)
			++x;
		else if ((element->params_types[i] & 0x2) && op.index_size)
			x += 2;
		else if ((element->params_types[i] & 0x2) && !op.index_size)
			x += 4;
		else if ((element->params_types[i] & 0x4))
			x += 2;
		++i;
	}
	return (x);
}

int		test_in(t_asm *parsed_champ, t_instruction *element)
{
	t_op *op_type;

	if (!(op_type = find_op(parsed_champ, element->opcode)))
		return (!(parsed_champ->error_type = BAD_COMPILATION_OPCODE));
	element->op_type = op_type;
	if (!test_param(parsed_champ, *op_type, element))
		return (0);
	element->size = find_size(*op_type, element);
	return (1);
}

void	set_num2(t_instruction *element, int *i, int p)
{
	int	res;

	res = ft_atoi(element->params[p]);
	element->hexdump[(*i)++] = (res & 0x0000ff00) >> 8;
	element->hexdump[*i] = res & 0x000000ff;
}

void	set_num(t_instruction *element, int *i, int p)
{
	int	res;

	if (element->op_type->index_size)
	{
		res = ft_atoi(element->params[p] + 1);
		element->hexdump[(*i)++] = (res & 0x0000ff00) >> 8;
		element->hexdump[*i] = res & 0x000000ff;
	}
	else
	{
		res = ft_atoi(element->params[p] + 1);
		element->hexdump[(*i)++] = (res & 0xff000000) >> 24;
		element->hexdump[(*i)++] = (res & 0x00ff0000) >> 16;
		element->hexdump[(*i)++] = (res & 0x0000ff00) >> 8;
		element->hexdump[*i] = res & 0x000000ff;
	}
}
