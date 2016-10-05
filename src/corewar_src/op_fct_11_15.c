/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct_11_15.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 03:06:16 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 03:46:17 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				c_sti(t_vm *vm, t_process *cur)
{
	static char		tab[4] = {T_REG, T_IND | T_REG | T_DIR, T_DIR | T_REG};
	int				i[3];
	int				ic;
	char			size;

	ic = 2;
	cur->flags |= P_INDEX;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 1))
		return (size + 1);
	if (((i[0] = read_byte(vm, cur, &ic)) < 1 || i[0] > REG_NUMBER))
		return (size + 1);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	i[2] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x0c) >> 2
			, vm, cur, &ic);
	if (cur->flags & P_I_CARRY)
		return (size + 1);
	cpy_memory(cur->reg[i[0] - 1], 4, vm
		, get_addr(cur->pc + ((i[1] + i[2]) % IDX_MOD)));
	return (size + 1);
}

int				c_fork(t_vm *vm, t_process *cur)
{
	int			index;
	t_process	*new;
	int			ic;

	ic = 1;
	cur->flags |= P_INDEX;
	cur->flags |= P_IDX_MOD;
	index = read_dir(vm, cur, &ic);
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		error(6);
	ft_memcpy(new->reg, cur->reg, REG_NUMBER * sizeof(int));
	new->flags = cur->flags & (P_CARRY | P_LIVE);
	new->cycles = cur->cycles;
	new->pc = get_addr(cur->pc + (index % IDX_MOD));
	new->player = cur->player;
	new->next = vm->process;
	vm->process = new;
	return (2);
}

int				c_lld(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_DIR | T_IND, T_REG};
	int			i[2];
	int			ic;
	char		size;

	ic = 2;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	if (((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6) == IND_CODE)
		i[0] = i[0] >> 16;
	if (((i[1] = read_byte(vm, cur, &ic)) < 1 || i[1] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[1] - 1] = i[0]))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_lldi(t_vm *vm, t_process *cur)
{
	static char		tab[4] = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG};
	int				i[2];
	int				ic;
	char			size;

	ic = 2;
	cur->flags |= P_INDEX;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 1))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[0] += read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
		, vm, cur, &ic);
	if (((i[1] = read_byte(vm, cur, &ic)) < 1 || i[1] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	cur->reg[i[1] - 1] = vm->memory[get_addr(cur->pc + (i[0]))] << 24
		| vm->memory[get_addr(cur->pc + ((i[0] + 1)))] << 16
		| vm->memory[get_addr(cur->pc + ((i[0] + 2)))] << 8
		| vm->memory[get_addr(cur->pc + (i[0] + 3))];
	if (!cur->reg[i[1] - 1])
		cur->flags |= P_CARRY;
	else if (cur->flags & P_CARRY)
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_lfork(t_vm *vm, t_process *cur)
{
	int			index;
	t_process	*new;
	int			ic;

	ic = 1;
	cur->flags |= P_INDEX;
	index = read_dir(vm, cur, &ic);
	if (!(new = (t_process*)malloc(sizeof(t_process))))
		error(6);
	ft_memcpy(new->reg, cur->reg, REG_NUMBER * sizeof(int));
	new->flags = cur->flags & (P_CARRY | P_LIVE);
	new->cycles = cur->cycles;
	new->pc = get_addr(cur->pc + (index));
	new->player = cur->player;
	new->next = vm->process;
	vm->process = new;
	return (2);
}
