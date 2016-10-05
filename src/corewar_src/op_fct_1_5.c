/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fct_1_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 06:48:04 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/23 03:47:34 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				c_live(t_vm *vm, t_process *cur)
{
	int			index;
	t_player	*pl;
	int			ic;

	ic = 1;
	index = read_dir(vm, cur, &ic);
	pl = vm->players;
	cur->flags |= P_LIVE;
	vm->lives += 1;
	while (pl)
	{
		if (pl->number == -index)
		{
			if (!(vm->flags & VM_HIDE))
				ft_printf("A process tells that player %d (\"%s\") is alive.\n"
					, pl->number, pl->name);
			pl->last_live = vm->cycles;
			pl->curr_p_lives += 1;
			pl->lives += 1;
		}
		pl = pl->next;
	}
	return (4);
}

int				c_ld(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_DIR | T_IND, T_REG};
	int			i[2];
	int			ic;
	char		size;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	if (((i[1] = read_byte(vm, cur, &ic)) < 1 || i[1] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[1] - 1] = i[0]))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_st(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG, T_IND | T_REG};
	int			i[2];
	int			ic;
	char		size;

	ic = 2;
	cur->flags |= P_IDX_MOD;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	if ((i[0] = read_byte(vm, cur, &ic)) < 1 || i[0] > REG_NUMBER)
		return (size + 1);
	if ((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4 == T_REG)
	{
		if ((i[1] = read_byte(vm, cur, &ic)) >= 1 && i[1] <= REG_NUMBER)
			cur->reg[i[1] - 1] = cur->reg[i[0] - 1];
	}
	else
	{
		cur->flags |= P_INDEX;
		i[1] = read_dir(vm, cur, &ic);
		cpy_memory(cur->reg[i[0] - 1], 4, vm
			, get_addr(cur->pc + (i[1] % IDX_MOD)));
	}
	return (size + 1);
}

int				c_add(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG, T_REG, T_REG};
	int			i[3];
	int			ic;
	char		size;

	ic = 2;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	if (((i[2] = read_byte(vm, cur, &ic)) < 1 || i[2] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[2] - 1] = i[0] + i[1]))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}

int				c_sub(t_vm *vm, t_process *cur)
{
	static char	tab[4] = {T_REG, T_REG, T_REG};
	int			i[3];
	int			ic;
	char		size;

	ic = 2;
	if (read_p_byte((vm->memory[get_addr(cur->pc + 1)]), tab, &size, 0))
		return (size + 1);
	i[0] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0xc0) >> 6
		, vm, cur, &ic);
	i[1] = read_param((vm->memory[get_addr(cur->pc + 1)] & 0x30) >> 4
			, vm, cur, &ic);
	if (((i[2] = read_byte(vm, cur, &ic)) < 1 || i[2] > REG_NUMBER)
			|| cur->flags & P_I_CARRY)
		return (size + 1);
	if (!(cur->reg[i[2] - 1] = i[0] - i[1]))
		cur->flags |= P_CARRY;
	else if ((cur->flags & P_CARRY))
		cur->flags ^= P_CARRY;
	return (size + 1);
}
