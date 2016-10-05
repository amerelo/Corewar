/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_vm_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 06:19:23 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 16:33:09 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"

static int		count_process(t_process *p)
{
	int			counter;

	counter = 0;
	while (p)
	{
		counter += 1;
		p = p->next;
	}
	return (counter);
}

void			print_infos(t_vm *vm, t_gui *gui)
{
	int			process_count;
	int			top_pos;

	top_pos = 50;
	draw_str(gui, "cycles :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, vm->cycles, to_screen(1650, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "lives :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, vm->lives, to_screen(1650, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	process_count = count_process(vm->process);
	draw_str(gui, "processes :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, process_count, to_screen(1650, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "cycles per sec :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, gui->cycles_per_sec,
			to_screen(1650, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "cycles per frame :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, gui->cycles_per_frame,
			to_screen(1650, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "cycles to die :", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, gui->cycles_to_die, to_screen(1650, top_pos, WHITE_COLOR));
}

static void		print_breakdown_suite(t_gui *ui, int lives, int ttl, int x)
{
	int			counter;
	int			percents;

	percents = ((float)((float)(lives - ttl)
				/ (float)(lives + 1)) * 50);
	counter = 0;
	while (counter < percents)
	{
		++counter;
		draw_str(ui, "#", to_screen(x, 1230 - (counter * 8)
			, WHITE_COLOR));
	}
}

void			print_breakdown(t_vm *vm, t_gui *gui)
{
	t_player	*current;
	int			counter;
	int			percents;
	int			x_tot[2];

	current = vm->players;
	x_tot[0] = 1580;
	x_tot[1] = 0;
	while (current)
	{
		x_tot[1] += current->curr_p_lives;
		counter = 0;
		percents = ((float)(current->curr_p_lives
					/ (float)(vm->lives + 1)) * 50);
		while (counter < percents)
		{
			++counter;
			draw_str(gui, "#", to_screen(x_tot[0], 1231 - (counter * 8)
				, current->color));
		}
		x_tot[0] += 60;
		current = current->next;
	}
	print_breakdown_suite(gui, vm->lives, x_tot[1], x_tot[0]);
}
