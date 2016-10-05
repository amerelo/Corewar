/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 20:29:02 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 22:01:19 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "corewar.h"

static void		dspl_crown(t_gui *ui, t_player *win,
		t_player *p, SDL_Rect pos)
{
	if (win->number != p->number)
		return ;
	SDL_BlitSurface(ui->crown, NULL, ui->screensurface, &pos);
}

static void		print_pl_infos(t_player *win,
		t_gui *gui, t_player *p, int index)
{
	int			top_pos;
	SDL_Rect	pos;

	top_pos = 260 + index * INFOS_HEIGHT_SPACE * 4;
	if (win)
	{
		pos.x = 1510;
		pos.y = top_pos + 25;
		dspl_crown(gui, win, p, pos);
	}
	draw_str(gui, "Player ", to_screen(1500, top_pos, WHITE_COLOR));
	draw_itostr(gui, p->number, to_screen(1560, top_pos, WHITE_COLOR));
	draw_str(gui, ":", to_screen(1600, top_pos, WHITE_COLOR));
	draw_str(gui, p->name, to_screen(1620, top_pos, p->color));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "Last live :", to_screen(1600, top_pos, WHITE_COLOR));
	draw_itostr(gui, p->last_live, to_screen(1810, top_pos, WHITE_COLOR));
	top_pos += INFOS_HEIGHT_SPACE;
	draw_str(gui, "Lives in current period :",
			to_screen(1600, top_pos, WHITE_COLOR));
	draw_itostr(gui, p->curr_p_lives, to_screen(1810, top_pos, WHITE_COLOR));
}

void			print_players_infos(t_vm *vm, t_gui *gui, t_player *win)
{
	t_player	*player;
	int			index;

	index = 0;
	player = vm->players;
	while (player)
	{
		print_pl_infos(win, gui, player, index);
		index++;
		player = player->next;
	}
}
