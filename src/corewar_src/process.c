/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 10:38:53 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/24 19:00:16 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	and_the_winner_is(t_vm *vm)
{
	t_player	*pl;
	t_player	*win;

	pl = vm->players;
	win = pl;
	while (pl)
	{
		if (pl->last_live > win->last_live || !win->last_live)
			win = pl;
		pl = pl->next;
	}
	ft_printf("Contestant %d \"%s\" has won, with %d lives!", win->number
		, win->name, win->lives);
	ft_printf(" (last was in cycle %d / %d)\n", win->last_live, vm->cycles);
}

void	cpy_memory(int i, int size, t_vm *vm, int addr)
{
	if (size == 4)
	{
		vm->memory[get_addr(addr)] = (i & 0xff000000) >> 24;
		vm->color[get_addr(addr)] = vm->pl | 0xf8;
		vm->memory[get_addr(addr + 1)] = (i & 0x00ff0000) >> 16;
		vm->color[get_addr(addr + 1)] = vm->pl | 0xf8;
		vm->memory[get_addr(addr + 2)] = (i & 0x0000ff00) >> 8;
		vm->color[get_addr(addr + 2)] = vm->pl | 0xf8;
		vm->memory[get_addr(addr + 3)] = (i & 0x000000ff);
		vm->color[get_addr(addr + 3)] = vm->pl | 0xf8;
	}
}

void	check_process(t_vm *vm)
{
	t_process	**current;
	t_process	*tmp;

	current = &vm->process;
	while (*current)
	{
		if (!((*current)->flags & P_LIVE))
		{
			tmp = (*current)->next;
			free(*current);
			*current = tmp;
		}
		else
		{
			if ((*current)->flags & P_LIVE)
				(*current)->flags ^= P_LIVE;
			current = &(*current)->next;
		}
	}
}

void	execute_process(t_vm *vm)
{
	t_process	*current;

	current = vm->process;
	while (current)
	{
		current->flags &= (P_CARRY | P_LIVE);
		current->pc = get_addr(current->pc);
		vm->pl = current->player;
		if (current->cycles <= 0)
			current->cycles = read_op(current, vm);
		if (current->cycles > 0)
			--current->cycles;
		if (current->cycles <= 0)
		{
			current->pc = get_addr(current->pc + (current->opcode >= 1
				&& current->opcode <= 16
				? vm->f[current->opcode - 1](vm, current)
				+ 1 : 1));
		}
		current = current->next;
	}
}

int		read_op(t_process *current, t_vm *vm)
{
	if ((current->opcode = vm->memory[current->pc]) == LD
			|| current->opcode == ST)
		return (5);
	else if (current->opcode == AND || current->opcode == OR
			|| current->opcode == XOR)
		return (6);
	else if (current->opcode == LIVE || current->opcode == ADD
			|| current->opcode == SUB || current->opcode == LLD)
		return (10);
	else if (current->opcode == ZJMP)
		return (20);
	else if (current->opcode == LDI || current->opcode == STI)
		return (25);
	else if (current->opcode == LLDI)
		return (50);
	else if (current->opcode == FORK)
		return (800);
	else if (current->opcode == LFORK)
		return (1000);
	else if (current->opcode == AFF)
		return (2);
	else
		return (0);
}
