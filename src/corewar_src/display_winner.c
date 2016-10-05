/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_winner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 13:02:05 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/26 15:25:26 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <time.h>

void			gui_sleep(t_gui *gui, unsigned int sec)
{
	time_t		now;
	SDL_Event	event;

	now = time(NULL);
	while (now + sec >= time(NULL))
	{
		while (SDL_WaitEventTimeout(&event, sec * 1000))
		{
			if (event.type == SDL_QUIT
					|| event.key.keysym.scancode == SDL_SCANCODE_Q
					|| event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				destroy_gui(gui);
				exit(0);
			}
		}
	}
}

void			play_fanfare(t_gui *gui, char *win_name)
{
	if (ft_strequ(win_name, "Legendary_mushroom"))
	{
		Mix_PlayMusic(gui->hyy, 1);
	}
	else
	{
		Mix_PlayMusic(gui->fanfare, 1);
	}
}

void			print_winner(t_gui *gui, char *win_name)
{
	t_txt		t;

	gui_sleep(gui, 1);
	t.color = make_sdl_color(WHITE_COLOR);
	t.position.x = 660;
	t.position.y = 560;
	if (!(t.font = TTF_OpenFont("./resources/Terminus.ttf", 50)))
		return ;
	if (!(t.str = TTF_RenderText_Blended(t.font, "winner", t.color)))
		return ;
	TTF_CloseFont(t.font);
	SDL_BlitSurface(t.str, NULL, gui->screensurface, &t.position);
	SDL_FreeSurface(t.str);
	SDL_UpdateWindowSurface(gui->win);
	gui_sleep(gui, 1);
	t.position.x = 715 - ((ft_strlen(win_name) / 2) * 33);
	t.position.y = 660;
	if (!(t.font = TTF_OpenFont("./resources/Terminus.ttf", 70)))
		return ;
	if (!(t.str = TTF_RenderText_Blended(t.font, win_name, t.color)))
		return ;
	TTF_CloseFont(t.font);
	SDL_BlitSurface(t.str, NULL, gui->screensurface, &t.position);
	SDL_FreeSurface(t.str);
	SDL_UpdateWindowSurface(gui->win);
}

void			display_winner(t_vm *vm, t_gui *gui)
{
	t_player	*pl;
	t_player	*win;
	SDL_Rect	pos;

	pl = vm->players;
	win = pl;
	print_breakdown(vm, gui);
	while (pl)
	{
		if (pl->last_live > win->last_live)
			win = pl;
		pl = pl->next;
	}
	print_players_infos(vm, gui, win);
	SDL_UpdateWindowSurface(gui->win);
	play_fanfare(gui, win->name);
	print_winner(gui, win->name);
	pos.x = 1500;
	pos.y = 800;
	if (ft_strequ(win->name, "Legendary_mushroom"))
		SDL_BlitSurface(gui->xout, NULL, gui->screensurface, &pos);
	SDL_UpdateWindowSurface(gui->win);
}
