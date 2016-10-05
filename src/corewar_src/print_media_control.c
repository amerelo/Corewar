/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_media_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 20:23:57 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/23 21:17:35 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void		print_running(t_gui *gui, int x, int y)
{
	static int	i = 0;

	if (i == 0)
	{
		draw_str(gui, "RUNNING", to_screen(x, y, WHITE_COLOR));
		i = 1;
	}
	else if (i == 1)
	{
		draw_str(gui, "RUNNING.", to_screen(x, y, WHITE_COLOR));
		i = 2;
	}
	else if (i == 2)
	{
		draw_str(gui, "RUNNING..", to_screen(x, y, WHITE_COLOR));
		i = 3;
	}
	else if (i == 3)
	{
		draw_str(gui, "RUNNING...", to_screen(x, y, WHITE_COLOR));
		i = 0;
	}
}

static void		print_status(t_gui *gui, int x, int y)
{
	if (gui->events & GUI_PAUSE)
	{
		draw_str(gui, " PAUSE ", to_screen(x, y, WHITE_COLOR));
		return ;
	}
	print_running(gui, x, y);
}

void			print_media_control(t_gui *gui)
{
	SDL_Rect	pos;

	pos.x = 1490;
	pos.y = 1253;
	if (gui->events & GUI_PAUSE)
		SDL_BlitSurface(gui->mc.play, NULL, gui->screensurface, &pos);
	else
		SDL_BlitSurface(gui->mc.pause, NULL, gui->screensurface, &pos);
	pos.x += 80;
	if (gui->events & GUI_MUTE)
		SDL_BlitSurface(gui->mc.mute, NULL, gui->screensurface, &pos);
	else
		SDL_BlitSurface(gui->mc.unmute, NULL, gui->screensurface, &pos);
	print_status(gui, pos.x + 109, pos.y + 3);
	pos.x += 260;
	SDL_BlitSurface(gui->mc.slower, NULL, gui->screensurface, &pos);
	pos.x += 80;
	SDL_BlitSurface(gui->mc.faster, NULL, gui->screensurface, &pos);
}
