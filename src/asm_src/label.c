/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:41:32 by jblondea          #+#    #+#             */
/*   Updated: 2016/05/26 17:33:27 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

/*
** Checking a label, and storing it if there is one
** Just try to find LABEL_CHARS followed by a LABEL_CHAR
** and right after an empty or comment char
*/

int			load_label(char *str, t_asm *parsed_champ)
{
	t_label			label;
	int				i;

	ft_logs(parsed_champ, "checking label : %s\n", str);
	ft_bzero(&label, sizeof(label));
	str = ft_start_trim(str);
	i = 0;
	while (str[i])
	{
		if (!is_label_char(str[i]))
		{
			if (str[i] == LABEL_CHAR && i != 0)
			{
				label.name = ft_strndup(str, i);
				ft_logs(parsed_champ, "storing label %s\n", label.name);
				ft_lstpushback(&parsed_champ->elements, &label, sizeof(label));
				return (1);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}
