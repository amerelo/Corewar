/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:40:49 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/16 16:51:50 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			check_param(char *str, char **instr_param,
							t_asm *parsed_champ, char *param_sep)
{
	char		*param_end;
	char		*param_trim_ended;

	str = ft_start_trim(str);
	ft_logs(parsed_champ, "trimed new param : %s\n", str);
	if (!*str)
		return (!(parsed_champ->error_type = BAD_INSTR_ARGS));
	param_end = str + len_before_empty_or_comment(str);
	if (param_end > param_sep && param_sep)
		param_end = param_sep;
	param_trim_ended = ft_start_trim(param_end);
	if (*param_trim_ended != SEPARATOR_CHAR && param_sep)
		return (!(parsed_champ->error_type = BAD_INSTR_ARGS));
	if (!(*instr_param = ft_strndup(str, param_end - str)))
		return (!(parsed_champ->error_type = MALLOC_FAIL));
	ft_logs(parsed_champ, "registered param : %s\n", *instr_param);
	return (1);
}

/*
** Checking the arguments of an instruction
** Storing a number of argument depending on the instruction type
** at the end there should be nothing left or a comment,
** anything else is an error
** .
** the final argument should stop where there is an empty char or a comment char
*/

int			load_instr_args(char *str, t_instruction *instr,
							t_asm *parsed_champ)
{
	int				i;
	char			*param_sep;

	i = 0;
	while (i < instr->op_type->size)
	{
		param_sep = NULL;
		ft_logs(parsed_champ, "param to check : %s\n", str);
		if (i + 1 < instr->op_type->size)
		{
			param_sep = ft_strchr(str, SEPARATOR_CHAR);
			if (!param_sep)
				return (!(parsed_champ->error_type = BAD_INSTR_ARGS));
		}
		if (!check_param(str, &instr->params[i], parsed_champ, param_sep))
			return (0);
		if (++i < instr->op_type->size)
			str = param_sep + 1;
	}
	str = ft_start_trim(str);
	str = ft_start_trim(str + len_before_empty_or_comment(str));
	ft_logs(parsed_champ, "remaining : %s\n", str);
	if (!is_empty(str) && !is_comment(str))
		return (!(parsed_champ->error_type = BAD_INSTR_ARGS));
	return (1);
}

/*
** Checking the instruction name with the op_types
** First checking the instruction name,
** Then the arguments count
*/

int			check_instr(char *str, t_asm *parsed_champ, int instr_name_len,
	t_instruction *instr)
{
	int				type_i;

	type_i = 0;
	while (parsed_champ->ops[type_i].opcode != 0)
	{
		if (!ft_strncmp(str, parsed_champ->ops[type_i].name, instr_name_len) &&
			instr_name_len == (int)ft_strlen(parsed_champ->ops[type_i].name))
		{
			ft_logs(parsed_champ, "%s instruction found\n", str);
			instr->opcode = parsed_champ->ops[type_i].opcode;
			instr->op_type = &parsed_champ->ops[type_i];
			str += ft_strlen(parsed_champ->ops[type_i].name);
			if (!load_instr_args(str, instr, parsed_champ))
				return (0);
			ft_logs(parsed_champ, "storing instruction %d\n", instr->opcode);
			ft_lstpushback(&parsed_champ->elements, instr, sizeof(*instr));
			ft_logs(parsed_champ, "instr : %s loaded successfully\n", str);
			return (1);
		}
		type_i++;
	}
	return (!(parsed_champ->error_type = BAD_INSTR));
}

/*
** Loading from the start of an instruction
*/

int			load_instr(char *str, t_asm *parsed_champ)
{
	t_instruction	instr;
	int				instr_name_len;

	ft_bzero(&instr, sizeof(instr));
	ft_logs(parsed_champ, "checking instr : %s\n", str);
	str = ft_start_trim(str);
	instr_name_len = len_before_empty(str);
	if (instr_name_len == 0)
		return (!(parsed_champ->error_type = BAD_INSTR));
	return (check_instr(str, parsed_champ, instr_name_len, &instr));
}
