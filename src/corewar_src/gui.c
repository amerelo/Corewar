/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 03:11:02 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 23:25:10 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"
#include <time.h>

static void		display_cthulhu(t_gui *gui)
{
	SDL_Rect	pos;

	pos.x = 1800;
	pos.y = 40;
	SDL_BlitSurface(gui->cthulhu, NULL, gui->screensurface, &pos);
}

static void		draw_memory(t_vm *vm, t_gui *gui)
{
	int			i;
	size_t		j;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		gui->txt.position.x = 5;
		gui->txt.position.y = 20 * ((i / 64) + 1);
		while (j < 64 && i < MEM_SIZE)
		{
			draw_byte(vm, gui, i);
			++i;
			++j;
		}
	}
}

void			draw_vm(t_vm *vm, t_gui *gui)
{
	draw_border(gui);
	draw_memory(vm, gui);
	draw_pcs(vm, gui);
	print_infos(vm, gui);
	display_cthulhu(gui);
}

void			destroy_gui(t_gui *gui)
{
	SDL_FreeSurface(gui->mc.faster);
	SDL_FreeSurface(gui->mc.slower);
	SDL_FreeSurface(gui->mc.play);
	SDL_FreeSurface(gui->mc.pause);
	SDL_FreeSurface(gui->mc.mute);
	SDL_FreeSurface(gui->mc.unmute);
	Mix_FreeMusic(gui->music);
	Mix_FreeMusic(gui->hyy);
	Mix_FreeMusic(gui->fanfare);
	Mix_FreeChunk(gui->sound);
	TTF_CloseFont(gui->txt.font);
	TTF_Quit();
	SDL_FreeSurface(gui->screensurface);
	SDL_FreeSurface(gui->cthulhu);
	SDL_FreeSurface(gui->xout);
	SDL_FreeSurface(gui->crown);
	SDL_DestroyWindow(gui->win);
	gui->txt.font = NULL;
	gui->screensurface = NULL;
	gui->xout = NULL;
	gui->win = NULL;
	Mix_CloseAudio();
	SDL_Quit();
}

void			launch_gui(t_vm *vm)
{
	t_gui		gui;

	init_gui(&gui);
	vm->flags |= VM_REFRESH;
	let_the_game_begin(vm, &gui);
	draw_vm(vm, &gui);
	display_winner(vm, &gui);
	press_any_key_to_quit(&gui);
	destroy_gui(&gui);
	free_champions(&vm->players);
}
