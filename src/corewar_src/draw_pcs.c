/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 11:22:37 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/22 11:33:57 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static t_player		*get_process_player(t_process *proc, t_player *players)
{
	while (players)
	{
		if (proc->player == players->index)
			return (players);
		players = players->next;
	}
	return (NULL);
}

static void			draw_pc_at(t_vm *vm, t_process *proc, t_gui *gui, int i)
{
	int				x;
	int				y;
	t_player		*player;
	SDL_Rect		rect;

	x = 5 + i % 64 * 22;
	y = 20 * ((i / 64) + 1);
	player = get_process_player(proc, vm->players);
	rect.x = x;
	rect.y = y;
	rect.w = 16;
	rect.h = 16;
	SDL_FillRect(gui->screensurface, &rect, player->color);
	draw_str(gui, "->", to_screen(x, y, 0xFFFFFF));
}

void				draw_pcs(t_vm *vm, t_gui *gui)
{
	t_process		*proc;
	char			drawn[MEM_SIZE];

	ft_bzero(&drawn, sizeof(drawn));
	proc = vm->process;
	while (proc)
	{
		if (!drawn[proc->pc])
		{
			drawn[proc->pc] = 1;
			draw_pc_at(vm, proc, gui, proc->pc);
		}
		proc = proc->next;
	}
}
