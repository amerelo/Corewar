/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:37:45 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/16 16:38:05 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			check_name(char *str, int fd, t_asm *parsed_champ)
{
	t_head_instr	head_instr;

	head_instr.champ_str = parsed_champ->head.prog_name;
	head_instr.instr_name = NAME_CMD_STRING;
	head_instr.max_length = PROG_NAME_LENGTH;
	if (load_head_instr(str, fd, parsed_champ, &head_instr))
	{
		parsed_champ->head.got_name = 1;
		return (1);
	}
	else
		return (!(parsed_champ->error_type = BAD_NAME));
}

int			check_comment(char *str, int fd, t_asm *parsed_champ)
{
	t_head_instr	head_instr;

	head_instr.champ_str = parsed_champ->head.comment;
	head_instr.instr_name = COMMENT_CMD_STRING;
	head_instr.max_length = COMMENT_LENGTH;
	if (load_head_instr(str, fd, parsed_champ, &head_instr))
	{
		parsed_champ->head.got_comment = 1;
		return (1);
	}
	else
		return (!(parsed_champ->error_type = BAD_COMMENT));
}
