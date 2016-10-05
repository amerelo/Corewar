/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compil_champ_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 22:33:33 by amerelo           #+#    #+#             */
/*   Updated: 2016/05/24 12:44:50 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_opts.h"

int		set_types2(t_asm *champ, t_instruction *el, int *i, int x)
{
	if (el->params[x][0] == '%')
	{
		if (el->params[x][1] == ':' &&
		!dis_to_hex(champ, el, i, x))
			return (!(champ->error_type = BAD_DIR_CONTENT));
		else if (ft_strisdigit(el->params[x] + 1))
			set_num(el, i, x);
	}
	else if (el->params[x][0] == 'r')
	{
		if (ft_strisdigit((el->params[x]) + 1) &&
		ft_strlen((el->params[x])) < 4)
			el->hexdump[*i] = ft_atoi(el->params[x] + 1);
		else
			return (!(champ->error_type = BAD_REG_CONTENT));
	}
	else if (ft_strisdigit((el->params[x])))
		set_num2(el, i, x);
	else if (el->params[x][0] == ':' && !dis_to_hex(champ, el, i, x))
		return (!(champ->error_type = BAD_IND_CONTENT));
	return (1);
}

int		set_types(t_asm *champ, t_instruction *el, int *i)
{
	int x;

	x = 0;
	while (el->params[x])
	{
		if (!set_types2(champ, el, i, x))
			return (0);
		++x;
		++(*i);
	}
	return (1);
}

int		test_arg(int *x, t_asm *parsed_champ, t_list **element)
{
	t_list			*tmp;

	tmp = (*element);
	if (!set_types(parsed_champ, tmp->content, x))
		return (0);
	return (1);
}

int		get_types2(t_asm *parsed_champ, t_instruction *element, int x)
{
	if (element->params[x][0] == '%' && element->params[x][1])
	{
		if (element->params[x][1] == ':')
			element->params_types[x] = T_DIR;
		else if (ft_strisdigit((element->params[x]) + 1))
			element->params_types[x] = T_DIR;
		else
			return (!(parsed_champ->error_type = BAD_INSTR_DIR_ARG));
	}
	else if (element->params[x][0] == 'r' && element->params[x][1])
	{
		if (ft_strisdigit(element->params[x] + 1))
			element->params_types[x] = T_REG;
		else
			return (!(parsed_champ->error_type = BAD_INSTR_REG_ARG));
	}
	else if (ft_strisdigit(element->params[x]))
		element->params_types[x] = T_IND;
	else if (element->params[x][0] == ':' && element->params[x][1])
		element->params_types[x] = T_IND;
	else
		return (!(parsed_champ->error_type = BAD_INSTR_IND_ARG));
	return (1);
}

int		get_types(t_asm *parsed_champ, t_instruction *element)
{
	int x;

	x = 0;
	while (element->params[x])
	{
		if (!get_types2(parsed_champ, element, x))
			return (0);
		++x;
	}
	return (1);
}
