/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 02:17:56 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/21 02:30:46 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_addr(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr;
	return (addr);
}

int				read_dir(t_vm *vm, t_process *current, int *ic)
{
	if (current->flags & P_INDEX)
		return ((short)((read_byte(vm, current, ic) << 8)
			| (read_byte(vm, current, ic))));
	else
		return ((read_byte(vm, current, ic) << 24)
			| (read_byte(vm, current, ic) << 16)
			| (read_byte(vm, current, ic) << 8)
			| read_byte(vm, current, ic));
}

int				read_ind(t_vm *vm, t_process *current, int *ic)
{
	short	tmp;

	tmp = ((read_byte(vm, current, ic) << 8)
		| (read_byte(vm, current, ic)));
	tmp = current->flags & P_IDX_MOD ? tmp % IDX_MOD : tmp;
	return (vm->memory[get_addr(current->pc + tmp)] << 24
		| vm->memory[get_addr(current->pc + tmp + 1)] << 16
		| vm->memory[get_addr(current->pc + tmp + 2)] << 8
		| vm->memory[get_addr(current->pc + tmp + 3)]);
}

unsigned char	read_byte(t_vm *vm, t_process *current, int *ic)
{
	*ic += 1;
	return (vm->memory[get_addr(current->pc + *ic - 1)]);
}

int				read_param(char code, t_vm *vm, t_process *cur, int *ic)
{
	int	tmp;

	if (code == REG_CODE)
	{
		if ((tmp = read_byte(vm, cur, ic)) >= 1 && tmp <= REG_NUMBER)
			return (cur->reg[tmp - 1]);
		else
		{
			cur->flags |= P_I_CARRY;
			return (0);
		}
	}
	else if (code == DIR_CODE)
		return (read_dir(vm, cur, ic));
	else if (code == IND_CODE)
		return (read_ind(vm, cur, ic));
	else
		return (0);
}
