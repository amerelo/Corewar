/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:07:52 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/24 16:40:04 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

/*
** Loading a line, which may contain a label OR an instruction
** First check for label,
** If there is one, check if there is an instruction after it
*/

int			load_instr_line(char *str, t_asm *parsed_champ)
{
	if (load_label(str, parsed_champ))
	{
		str = ft_strchr(str, LABEL_CHAR);
		str++;
		str = ft_start_trim(str);
	}
	if (is_empty(str) || is_comment(str))
		return (1);
	if (!load_instr(str, parsed_champ))
		return (0);
	return (1);
}

/*
** Parsing raw lines, the first ones should contain .name or .comment
** before we can start loading the instructions/labels
*/

int			parse_lines(int fd, t_asm *parsed_champ)
{
	int		status;
	char	*line;

	while ((status = get_next_line(fd, &line)) > 0)
	{
		ft_logs(parsed_champ, "checking line : %s\n", line);
		if (is_empty(line) || is_comment(line))
		{
			;
		}
		else if (!parsed_champ->head.got_name
				|| !parsed_champ->head.got_comment)
		{
			if (!load_head(line, fd, parsed_champ))
				return (0);
		}
		else
		{
			if (!load_instr_line(line, parsed_champ))
				return (0);
		}
		free(line);
	}
	return (1);
}

int			load_file(char *file_name, t_asm *parsed_champ)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (!(parsed_champ->error_type = FILE_OPEN_FAIL));
	if (!parse_lines(fd, parsed_champ))
		return (0);
	if (!parsed_champ->head.got_name
			|| !parsed_champ->head.got_comment)
		return (!(parsed_champ->error_type = BAD_HEAD));
	if (!parsed_champ->elements)
		return (!(parsed_champ->error_type = BAD_INSTR));
	if (parsed_champ->flags & FLAG_INFO || parsed_champ->flags & FLAG_LOGS)
	{
		ft_printf("parsing successful\n");
		print_champ(parsed_champ);
	}
	return (1);
}
