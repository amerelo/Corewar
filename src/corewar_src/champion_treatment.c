/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 03:32:20 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/24 19:03:53 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		set_num(t_vm *vm)
{
	t_player	*current;
	int			min;

	min = 1;
	current = vm->players;
	while (current)
		if (current->number == min)
		{
			min += 1;
			current = vm->players;
		}
		else
			current = current->next;
	current = vm->players;
	while (current)
		if (current->number == -1)
		{
			current->number = min;
			return (1);
		}
		else
			current = current->next;
	return (0);
}

void	aff_champions(t_vm *vm, int n)
{
	t_player	*current;
	t_process	*nw;
	int			i;

	i = -1;
	current = vm->players;
	while (++i < n)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"
			, current->number, current->size, current->name, current->comment);
		if (!(nw = (t_process*)malloc(sizeof(t_process))))
			error(6);
		ft_bzero(nw->reg, (int)REG_NUMBER * sizeof(int));
		current->index = i + 1;
		nw->reg[0] = -current->number;
		nw->player = i + 1;
		nw->flags = 0;
		nw->cycles = 0;
		nw->pc = i * (MEM_SIZE / n);
		ft_memcpy(&vm->memory[nw->pc], current->champion, current->size);
		ft_memset(&vm->color[nw->pc], i + 1, current->size);
		nw->next = vm->process;
		vm->process = nw;
		current = current->next;
	}
}

void	aff_memory(t_vm *vm)
{
	size_t	index;

	index = 0;
	while (index < MEM_SIZE)
	{
		if (!(index % (vm->flags & VM_64 ? 64 : 32)))
			ft_printf("0x%.4x : ", index);
		if (vm->flags & VM_DUMP_COLOR)
			ft_printf("\e[%dm", vm->color[index] & 0x07
				? 30 + (vm->color[index] & 0x07) : 0);
		ft_printf("%.2x", vm->memory[index]);
		if (vm->flags & VM_64 ? ((index % 64) == 63) : (((index % 32) == 31)))
		{
			if (vm->flags & VM_DUMP_COLOR)
				ft_printf("\e[0m");
			ft_printf(" \n");
		}
		else
			ft_printf(" ");
		++index;
	}
}

void	free_process(t_process **pl)
{
	if (!*pl)
		return ;
	if ((*pl) && (*pl)->next)
		free_process(&(*pl)->next);
	(*pl)->next = NULL;
	free(*pl);
	*pl = NULL;
}

void	free_champions(t_player **pl)
{
	if (!*pl)
		return ;
	if ((*pl)->next)
		free_champions(&(*pl)->next);
	(*pl)->next = NULL;
	free((*pl)->name);
	free((*pl)->comment);
	free((*pl)->champion);
	free(*pl);
	*pl = NULL;
}
