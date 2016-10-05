/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:33:33 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/26 19:59:03 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

/*
** Append src to value, starting from value_index and until max_length
** Data is appended until a START_END_VALUE_CHAR is found in src
** This event prevents from appending an extra new_line
** (which was originally removed by getnextline)
*/

int			append_until_end_char(t_head_instr *head_instr, char *src,
									char **content_end, t_asm *parsed_champ)
{
	int		end_line;

	end_line = 1;
	ft_logs(parsed_champ, "content to append : %s\n", src);
	if ((*content_end = ft_strchr(src, START_END_VALUE_CHAR)))
	{
		*content_end = ft_strdup(ft_strchr(src, START_END_VALUE_CHAR));
		src[ft_strlen(src) - ft_strlen(*content_end)] = 0;
		**content_end = 0;
		end_line = 0;
	}
	ft_logs(parsed_champ, "current length : %d\n",
		head_instr->champ_str_current_index + (int)ft_strlen(src) + end_line);
	ft_logs(parsed_champ, "max len : %d\n", head_instr->max_length);
	if (head_instr->champ_str_current_index + (int)ft_strlen(src) + end_line
		> head_instr->max_length)
		return (0);
	head_instr->champ_str_current_index = ft_append(head_instr->champ_str,
		head_instr->champ_str_current_index, src);
	if (end_line)
		head_instr->champ_str_current_index = ft_append(head_instr->champ_str,
			head_instr->champ_str_current_index, "\n");
	return (1);
}

int			load_head_end(int fd, t_asm *parsed_champ, t_head_instr *head_instr,
							char **content_end)
{
	char	*line;
	int		status;

	while (!*content_end && (status = get_next_line(fd, &line)) > 0)
	{
		if (!append_until_end_char(head_instr, line, content_end, parsed_champ))
		{
			free(line);
			return (0);
		}
		ft_logs(parsed_champ, "in champ content after append : %s\n",
			head_instr->champ_str);
		ft_logs(parsed_champ, "pointer on content_end : %p\n", *content_end);
		free(line);
	}
	if (!*content_end)
		return (0);
	return (1);
}

/*
** Storing the head instruction which was found in load_head
** .
** It has to end at START_END_VALUE_CHAR
** and to getnextlines until it is found (done in load_head_end)
** .
** The total also has to be less than max_length or it becomes an error
*/

int			load_head_instr(char *str, int fd, t_asm *parsed_champ,
								t_head_instr *head_instr)
{
	char	*content_end;

	head_instr->champ_str_current_index = 0;
	str += ft_strlen(head_instr->instr_name);
	str = ft_start_trim(str);
	if (str[0] != START_END_VALUE_CHAR)
		return (0);
	str++;
	content_end = NULL;
	if (!append_until_end_char(head_instr, str, &content_end, parsed_champ))
		return (0);
	ft_logs(parsed_champ, "champ content after append : %s\n",
		head_instr->champ_str);
	ft_logs(parsed_champ, "pointer on content_end : %p\n", content_end);
	if (!load_head_end(fd, parsed_champ, head_instr, &content_end))
		return (0);
	str = content_end + 1;
	str = ft_start_trim(str);
	if (!is_empty(str) && !is_comment(str))
		return (0);
	ft_logs(parsed_champ, "champ content after head load : %s\n",
		head_instr->champ_str);
	free(content_end);
	return (1);
}

/*
** Checking the head, looking for .name or .comment if it was not already found
*/

int			load_head(char *str, int fd, t_asm *parsed_champ)
{
	str = ft_start_trim(str);
	if (!ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
		&& !parsed_champ->head.got_name)
	{
		return (check_name(str, fd, parsed_champ));
	}
	else if (!ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))
		&& !parsed_champ->head.got_comment)
	{
		return (check_comment(str, fd, parsed_champ));
	}
	else
		return (!(parsed_champ->error_type = BAD_HEAD));
}
