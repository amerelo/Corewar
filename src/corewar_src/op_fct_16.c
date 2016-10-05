/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct_16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 03:07:47 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 04:28:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				c_aff(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG};
	int			index;
	char		size;
	int			ic;

	ic = 2;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	if ((index = read_byte(vm, cur, &ic)) >= 1 && index <= REG_NUMBER)
		index = cur->reg[index - 1] % 256;
	else
		return (size + 1);
	if (!(vm->flags & VM_HIDE_AFF))
		ft_printf("Aff: %c\n", index);
	return (size + 1);
}
