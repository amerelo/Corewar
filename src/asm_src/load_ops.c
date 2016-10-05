/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:44:36 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/24 16:28:33 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

void		fill_op_start(t_op *op, char *name, int size_code_cost[3])
{
	op->name = ft_strdup(name);
	op->size = size_code_cost[0];
	op->opcode = size_code_cost[1];
	op->cost = size_code_cost[2];
}

void		fill_op_args(t_op *op, char params_types[4], char params_byte,
						char index_size)
{
	op->params_types[0] = params_types[0];
	op->params_types[1] = params_types[1];
	op->params_types[2] = params_types[2];
	op->params_types[3] = params_types[3];
	op->params_byte = params_byte;
	op->index_size = index_size;
}

void		load_ops2(t_asm *parsed_champ)
{
	fill_op_start(&parsed_champ->ops[8], "zjmp", (int[3]){1, 9, 20});
	fill_op_args(&parsed_champ->ops[8], (char[4]){T_DIR, 0, 0, 0}, 0, 1);
	fill_op_start(&parsed_champ->ops[9], "ldi", (int[3]){3, 10, 25});
	fill_op_args(&parsed_champ->ops[9], (char[4]){T_REG | T_DIR | T_IND,
		T_DIR | T_REG, T_REG, 0}, 1, 1);
	fill_op_start(&parsed_champ->ops[10], "sti", (int[3]){3, 11, 25});
	fill_op_args(&parsed_champ->ops[10], (char[4]){T_REG, T_REG | T_DIR | T_IND,
		T_DIR | T_REG, 0}, 1, 1);
	fill_op_start(&parsed_champ->ops[11], "fork", (int[3]){1, 12, 800});
	fill_op_args(&parsed_champ->ops[11], (char[4]){T_DIR, 0, 0, 0}, 0, 1);
	fill_op_start(&parsed_champ->ops[12], "lld", (int[3]){2, 13, 10});
	fill_op_args(&parsed_champ->ops[12], (char[4]){T_DIR | T_IND, T_REG, 0, 0},
		1, 0);
	fill_op_start(&parsed_champ->ops[13], "lldi", (int[3]){3, 14, 50});
	fill_op_args(&parsed_champ->ops[13], (char[4]){T_REG | T_DIR | T_IND,
		T_DIR | T_REG, T_REG, 0}, 1, 1);
	fill_op_start(&parsed_champ->ops[14], "lfork", (int[3]){1, 15, 1000});
	fill_op_args(&parsed_champ->ops[14], (char[4]){T_DIR, 0, 0, 0}, 0, 1);
	fill_op_start(&parsed_champ->ops[15], "aff", (int[3]){1, 16, 2});
	fill_op_args(&parsed_champ->ops[15], (char[4]){T_REG, 0, 0, 0}, 1, 0);
	fill_op_start(&parsed_champ->ops[16], "", (int[3]){0, 0, 0});
	fill_op_args(&parsed_champ->ops[16], (char[4]){0, 0, 0, 0}, 0, 0);
	if (parsed_champ->flags & FLAG_INFO || parsed_champ->flags & FLAG_LOGS)
		ft_printf("instructions types loading %s\n", "ok");
}

void		load_ops(t_asm *parsed_champ)
{
	fill_op_start(&parsed_champ->ops[0], "live", (int[3]){1, 1, 10});
	fill_op_args(&parsed_champ->ops[0], (char[4]){T_DIR, 0, 0, 0}, 0, 0);
	fill_op_start(&parsed_champ->ops[1], "ld", (int[3]){2, 2, 5});
	fill_op_args(&parsed_champ->ops[1], (char[4]){T_DIR | T_IND, T_REG, 0, 0},
		1, 0);
	fill_op_start(&parsed_champ->ops[2], "st", (int[3]){2, 3, 5});
	fill_op_args(&parsed_champ->ops[2], (char[4]){T_REG, T_IND | T_REG, 0, 0},
		1, 0);
	fill_op_start(&parsed_champ->ops[3], "add", (int[3]){3, 4, 10});
	fill_op_args(&parsed_champ->ops[3], (char[4]){T_REG, T_REG, T_REG, 0},
		1, 0);
	fill_op_start(&parsed_champ->ops[4], "sub", (int[3]){3, 5, 10});
	fill_op_args(&parsed_champ->ops[4], (char[4]){T_REG, T_REG, T_REG, 0},
		1, 0);
	fill_op_start(&parsed_champ->ops[5], "and", (int[3]){3, 6, 6});
	fill_op_args(&parsed_champ->ops[5], (char[4]){T_REG | T_DIR | T_IND,
		T_REG | T_IND | T_DIR, T_REG, 0}, 1, 0);
	fill_op_start(&parsed_champ->ops[6], "or", (int[3]){3, 7, 6});
	fill_op_args(&parsed_champ->ops[6], (char[4]){T_REG | T_IND | T_DIR,
		T_REG | T_IND | T_DIR, T_REG, 0}, 1, 0);
	fill_op_start(&parsed_champ->ops[7], "xor", (int[3]){3, 8, 6});
	fill_op_args(&parsed_champ->ops[7], (char[4]){T_REG | T_IND | T_DIR,
		T_REG | T_IND | T_DIR, T_REG, 0}, 1, 0);
	load_ops2(parsed_champ);
}
