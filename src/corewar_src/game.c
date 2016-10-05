/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 03:36:03 by flevesqu          #+#    #+#             */
/*   Updated: 2016/05/24 11:27:15 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"

static void	dump(t_vm *vm)
{
	aff_memory(vm);
	free_champions(&vm->players);
	free_process(&vm->process);
	exit(0);
}

static void	set_players_colors(t_player *players)
{
	int			count;
	static int	colors[4] = {P_1_COLOR, P_2_COLOR, P_3_COLOR, P_4_COLOR};
	static int	colors_hl[4] = {P_1_COLOR_HL, P_2_COLOR_HL, P_3_COLOR_HL
			, P_4_COLOR_HL};

	count = 0;
	while (players)
	{
		players->color = colors[count];
		players->color_hl = colors_hl[count];
		count++;
		players = players->next;
	}
}

static void	reset_players_period_infos(t_player *players)
{
	while (players)
	{
		players->curr_p_lives = 0;
		players = players->next;
	}
}

static void	check_vm(int *last_decrease, int *cycles_to_die, t_vm *vm)
{
	if (*last_decrease >= MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		*cycles_to_die += CYCLE_DELTA;
		*last_decrease = 1;
	}
	else
		*last_decrease += 1;
	check_process(vm);
	reset_players_period_infos(vm->players);
	vm->lives = 0;
	vm->period = 0;
}

void		let_the_game_begin(t_vm *vm, t_gui *gui)
{
	int	last_decrease;
	int	cycles_to_die;

	cycles_to_die = 0;
	last_decrease = 1;
	set_players_colors(vm->players);
	while (vm->process)
	{
		if (gui && (!(vm->flags & VM_DUMP) || vm->cycles >= vm->dump))
		{
			gui->cycles_to_die = CYCLE_TO_DIE - cycles_to_die;
			refresh_gui(vm, gui);
		}
		if (gui && (!(vm->flags & VM_DUMP) || vm->cycles >= vm->dump)
				&& (gui->events & GUI_PAUSE))
			continue ;
		if (!gui && vm->flags & VM_DUMP && vm->cycles == vm->dump)
			dump(vm);
		vm->cycles += 1;
		vm->period += 1;
		if (CYCLE_TO_DIE - cycles_to_die > 0)
			execute_process(vm);
		if (vm->period >= ((CYCLE_TO_DIE) - cycles_to_die))
			check_vm(&last_decrease, &cycles_to_die, vm);
	}
}
