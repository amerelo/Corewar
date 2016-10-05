/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct_6_10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 03:05:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 03:55:32 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				c_and(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG};
	int			i[3];
	int			ic;
	char		size;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	if (((i[2] = read_byte(vm, cur, &ic)) < 1 || i[2] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[2] - 1] = (i[0] & i[1])))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_or(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG};
	int			i[3];
	int			ic;
	char		size;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	if (((i[2] = read_byte(vm, cur, &ic)) < 1 || i[2] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[2] - 1] = (i[0] | i[1])))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_xor(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG};
	int			i[3];
	int			ic;
	char		size;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	if (((i[2] = read_byte(vm, cur, &ic)) < 1 || i[2] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[2] - 1] = (i[0] ^ i[1])))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_zjmp(t_vm *vm, t_process *cur)
{
	int	ic;
	int	index;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (!(cur->flags & P_CARRY))
		return (2);
	cur->flags |= P_INDEX;
	ic = 1;
	index = read_dir(vm, cur, &ic);
	cur->pc = get_addr(cur->pc + (index % IDX_MOD));
	return (get_addr(index % IDX_MOD - 1));
}

int				c_ldi(t_vm *vm, t_process *cur)
{
	static char		tab[4] = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG};
	int				i[2];
	int				ic;
	char			size;

	ic = 2;
	cur->flags |= P_INDEX;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 1))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[0] += read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
		, vm, cur, &ic);
	if (((i[1] = read_byte(vm, cur, &ic)) < 1 || i[1] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	cur->reg[i[1] - 1] = vm->memory[get_addr(cur->pc + (i[0] % IDX_MOD))] << 24
		| vm->memory[get_addr(cur->pc + ((i[0] + 1) % IDX_MOD))] << 16
		| vm->memory[get_addr(cur->pc + ((i[0] + 2) % IDX_MOD))] << 8
		| vm->memory[get_addr(cur->pc + (i[0] + 3) % IDX_MOD)];
	return (size + 1);
}
