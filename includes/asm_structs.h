/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:11:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 16:29:49 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCTS_H
# define ASM_STRUCTS_H

typedef struct				s_op
{
	char					*name;
	int						size;
	char					params_types[4];
	int						opcode;
	int						cost;
	char					params_byte;
	char					index_size;
}							t_op;

typedef struct				s_instruction
{
	char					opcode;
	char					params_types[4];
	char					*params[4];
	t_op					*op_type;
	int						size;
	int						address;
	char					*hexdump;
}							t_instruction;

typedef struct				s_header
{
	char					prog_name[PROG_NAME_LENGTH + 1];
	char					comment[COMMENT_LENGTH + 1];
	char					got_name;
	char					got_comment;
}							t_header;

typedef struct				s_label
{
	char					*name;
	int						address;
}							t_label;

typedef struct				s_head_instr
{
	char					*champ_str;
	int						champ_str_current_index;
	char					*instr_name;
	int						max_length;

}							t_head_instr;

typedef struct				s_asm
{
	int						flags;
	int						error_type;
	int						champ_size;
	char					*file_name;
	t_header				head;
	t_list					*elements;
	t_op					ops[17];
}							t_asm;

#endif
