/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:18:32 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/23 16:37:32 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int		ft_error_part2(t_asm *parsed_champ)
{
	if (parsed_champ->error_type == BAD_COMPILATION_OPCODE)
		ft_putstr_fd("Unknown instruction opcode!\n", 2);
	else if (parsed_champ->error_type == UNKNOWN_LABEL)
		ft_putstr_fd("Unknown label!\n", 2);
	else if (parsed_champ->error_type == BAD_ARG_TYPE)
		ft_putstr_fd("Incompatible argument type!\n", 2);
	else if (parsed_champ->error_type == BAD_ARG_COUNT)
		ft_putstr_fd("Bad argument count on instruction!\n", 2);
	else if (parsed_champ->error_type == BAD_REG_CONTENT)
		ft_putstr_fd("Bad REG content on argument!\n", 2);
	else if (parsed_champ->error_type == BAD_DIR_CONTENT)
		ft_putstr_fd("Bad DIR content on argument!\n", 2);
	else if (parsed_champ->error_type == BAD_IND_CONTENT)
		ft_putstr_fd("Bad IND content on argument!\n", 2);
	else if (parsed_champ->error_type == BAD_INSTR_DIR_ARG)
		ft_putstr_fd("Bad DIR format on argument!\n", 2);
	else if (parsed_champ->error_type == BAD_INSTR_IND_ARG)
		ft_putstr_fd("Bad IND format on argument!\n", 2);
	else if (parsed_champ->error_type == BAD_INSTR_REG_ARG)
		ft_putstr_fd("Bad REG format on argument!\n", 2);
	else
		ft_putstr_fd("\n", 2);
	return (0);
}

int		ft_error(t_asm *parsed_champ)
{
	if (!(parsed_champ->flags & FLAG_ERROR))
	{
		ft_putstr_fd("ERROR\n", 2);
		return (0);
	}
	ft_putstr_fd("\xF0\x9F\x98\xb1  Error \xF0\x9F\x92\xA9  ", 2);
	if (parsed_champ->error_type == FILE_OPEN_FAIL)
		ft_putstr_fd("File opening failed!\n", 2);
	else if (parsed_champ->error_type == MALLOC_FAIL)
		ft_putstr_fd("Malloc failed!\n", 2);
	else if (parsed_champ->error_type == BAD_NAME)
		ft_putstr_fd("Bad format on .name!\n", 2);
	else if (parsed_champ->error_type == BAD_COMMENT)
		ft_putstr_fd("Bad format on .comment!\n", 2);
	else if (parsed_champ->error_type == BAD_HEAD)
		ft_putstr_fd("Bad format on header!\n", 2);
	else if (parsed_champ->error_type == BAD_INSTR_ARGS)
		ft_putstr_fd("Bad format on instruction arguments!\n", 2);
	else if (parsed_champ->error_type == BAD_INSTR)
		ft_putstr_fd("Bad format on instruction!\n", 2);
	else if (parsed_champ->error_type == BAD_ARG)
		ft_putstr_fd("Bad ARGUMENT!\n", 2);
	else
		ft_error_part2(parsed_champ);
	return (0);
}
