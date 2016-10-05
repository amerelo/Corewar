/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_opts.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 15:07:29 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/23 16:28:08 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_OPTS_H
# define ASM_OPTS_H

/*
** error codesg
*/

enum				e_error
{
	BAD_NAME = 1,
	BAD_COMMENT,
	MALLOC_FAIL,
	EMPTY_FILE,
	FILE_OPEN_FAIL,
	BAD_HEAD,
	BAD_INSTR_ARGS,
	BAD_INSTR,
	BAD_ARG,
	BAD_COMPILATION_OPCODE,
	UNKNOWN_LABEL,
	BAD_ARG_TYPE,
	BAD_ARG_COUNT,
	BAD_REG_CONTENT,
	BAD_DIR_CONTENT,
	BAD_IND_CONTENT,
	BAD_INSTR_DIR_ARG,
	BAD_INSTR_IND_ARG,
	BAD_INSTR_REG_ARG
};

/*
** program opts, one flag per bit
*/

enum				e_flags
{
	FLAG_LOGS = 0b1,
	FLAG_ERROR = 0b10,
	FLAG_INFO = 0b100
};

#endif
