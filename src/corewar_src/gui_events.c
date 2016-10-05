/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 10:09:05 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 16:35:28 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			gui_mute(t_gui *gui)
{
	if (gui->events & GUI_MUTE)
		Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	else
		Mix_VolumeMusic(0);
	gui->events ^= GUI_MUTE;
}

void			update_events(t_input *in)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT
				|| event.key.keysym.scancode == SDL_SCANCODE_Q)
			in->key[SDL_SCANCODE_Q] = 1;
		if (pause_key(event))
		{
			if (Mix_PausedMusic() == 1)
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
			in->key[SDL_SCANCODE_SPACE] = 1;
		}
		if (plus_key(event))
			in->key[SDL_SCANCODE_EQUALS] = 1;
		if (minus_key(event))
			in->key[SDL_SCANCODE_MINUS] = 1;
		if (mute_key(event))
			in->key[SDL_SCANCODE_M] = 1;
		if (help_key(event))
			in->key[SDL_SCANCODE_ESCAPE] = 1;
	}
}

void			gui_change_cycles_per_sec(t_gui *gui, int diff)
{
	gui->cycles_per_sec = gui->cycles_per_sec + diff;
	if (gui->cycles_per_sec < 1)
	{
		gui->cycles_per_sec = 1;
		gui->cycles_per_frame = 1;
	}
	if (gui->cycles_per_sec / gui->cycles_per_frame > 45)
		gui->cycles_per_frame++;
	else if (gui->cycles_per_sec / gui->cycles_per_frame < 30
				&& gui->cycles_per_frame > 1)
		gui->cycles_per_frame--;
	if (!(gui->events & GUI_MUTE))
		Mix_PlayChannel(0, gui->sound, 0);
}

void			do_events(t_input in, t_vm *vm, t_gui *gui)
{
	if (in.key[SDL_SCANCODE_Q])
	{
		destroy_gui(gui);
		free_champions(&vm->players);
		exit(0);
	}
	if (in.key[SDL_SCANCODE_SPACE])
		gui->events ^= GUI_PAUSE;
	if (in.key[SDL_SCANCODE_EQUALS])
		gui_change_cycles_per_sec(gui, 10);
	if (in.key[SDL_SCANCODE_MINUS])
		gui_change_cycles_per_sec(gui, -10);
	if (in.key[SDL_SCANCODE_M])
		gui_mute(gui);
	if (in.key[SDL_SCANCODE_ESCAPE])
	{
		gui->events ^= GUI_HELP;
		if (!(gui->events & GUI_MUTE))
			Mix_PlayChannel(0, gui->sound, 0);
	}
}

void			press_any_key_to_quit(t_gui *gui)
{
	SDL_Event	event;

	draw_str(gui, "PRESS ANY KEY TO QUIT", to_screen(1630, 1257, 0xFFFFFF));
	SDL_UpdateWindowSurface(gui->win);
	while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN)
		SDL_WaitEvent(&event);
}
