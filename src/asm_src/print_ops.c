/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 21:13:01 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/24 16:29:20 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

void		print_op_type(t_op *op)
{
	ft_printf("name : %s, opcode : %d, size : %d, cost : %d\n", op->name,
		op->opcode, op->size, op->cost);
	ft_printf("types : [0] : %#x, [1] : %#x, [2] : %#x\n", op->params_types[0],
		op->params_types[1], op->params_types[2]);
	ft_printf("params_byte : %c\n", op->params_byte);
	ft_printf("index_size : %c\n", op->index_size);
}

void		print_op_types(t_asm *parsed_champ)
{
	int		i;

	i = 0;
	while (i < 17)
	{
		print_op_type(&parsed_champ->ops[i]);
		i++;
	}
}
