/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:07:52 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/24 23:22:08 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int			load_flags(char *opt, t_asm *parsed_champ)
{
	if (!ft_strcmp(opt, "-l"))
		parsed_champ->flags |= FLAG_LOGS;
	else if (!ft_strcmp(opt, "-e"))
		parsed_champ->flags |= FLAG_ERROR;
	else if (!ft_strcmp(opt, "-i"))
		parsed_champ->flags |= FLAG_INFO;
	else
		return (0);
	return (1);
}

void		print_usage(void)
{
	ft_printf("Usage: ./asm [-i -e -l] <sourcefile.s> [-i -e -l]\n");
	ft_printf("    -i : Provides the content of the parsed champion\n");
	ft_printf("    -e : Provides a specific error message instead of ERROR\n");
	ft_printf("    -l : Various logs\n");
}

char		*load_args(int ac, char **av, t_asm *parsed_champ)
{
	int		i;
	char	*file_name;

	file_name = NULL;
	i = 0;
	while (i < ac)
	{
		if (!load_flags(av[i], parsed_champ))
			file_name = av[i];
		i++;
	}
	return (file_name);
}

/*
** Removal of ".s\0" if it is there, else let the .something
*/

char		*remove_s_ext(char *file_name)
{
	char		*s_pos;
	char		*new_name;

	new_name = ft_strdup(file_name);
	if ((s_pos = ft_strstr(new_name, ".s")))
	{
		if (!s_pos[2])
			*s_pos = 0;
	}
	return (new_name);
}

int			main(int ac, char **av)
{
	char	*file_name;
	t_asm	parsed_champ;

	if (ac < 2)
	{
		print_usage();
		return (0);
	}
	ft_bzero(&parsed_champ, sizeof(parsed_champ));
	if (!(file_name = load_args(ac, av, &parsed_champ)))
		return (ft_error(&parsed_champ));
	parsed_champ.file_name = remove_s_ext(file_name);
	load_ops(&parsed_champ);
	if (!load_file(file_name, &parsed_champ))
		return (ft_error(&parsed_champ));
	if (!(compile_champ(&parsed_champ)))
		return (ft_error(&parsed_champ));
	write_champ(&parsed_champ);
	return (0);
}
