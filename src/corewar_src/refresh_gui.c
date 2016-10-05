/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_gui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 20:54:20 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/07/25 00:59:09 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "corewar.h"

static void		print_mouse_command(t_gui *gui)
{
	t_border	b;

	b.x = 1538;
	b.y = 1236;
	b.xmax = 1960;
	b.ymax = 1286;
	b.size = 8;
	draw_vrt_line(gui->screensurface, GRAY_COLOR,
			rect_props(b.x, b.y, b.size), b.ymax);
	b.x += 80;
	draw_vrt_line(gui->screensurface, GRAY_COLOR,
			rect_props(b.x, b.y, b.size), b.ymax);
	b.x += 180;
	draw_vrt_line(gui->screensurface, GRAY_COLOR,
			rect_props(b.x, b.y, b.size), b.ymax);
	b.x += 80;
	draw_vrt_line(gui->screensurface, GRAY_COLOR,
			rect_props(b.x, b.y, b.size), b.ymax);
	print_media_control(gui);
}

static int		wait_frame(t_gui *gui)
{
	clock_t		elapsed_time;

	gui->frame_cycles_count++;
	if (gui->frame_cycles_count < gui->cycles_per_frame)
		return (0);
	gui->frame_cycles_count = 0;
	elapsed_time = clock() - gui->last_render_time;
	if ((unsigned long)elapsed_time <
			(unsigned long)CLOCKS_PER_SEC
			/ gui->cycles_per_sec * gui->cycles_per_frame)
		usleep(CLOCKS_PER_SEC / gui->cycles_per_sec *
				gui->cycles_per_frame - elapsed_time);
	gui->last_render_time = clock();
	return (1);
}

void			refresh_gui(t_vm *vm, t_gui *gui)
{
	t_input		in;
	Uint32		blackscreen;

	if (!wait_frame(gui))
		return ;
	ft_bzero(&in, sizeof(in));
	update_events(&in);
	do_events(in, vm, gui);
	draw_vm(vm, gui);
	print_players_infos(vm, gui, NULL);
	print_breakdown(vm, gui);
	print_mouse_command(gui);
	draw_help(gui);
	SDL_UpdateWindowSurface(gui->win);
	blackscreen = SDL_MapRGB(gui->screensurface->format, 0, 21, 27);
	SDL_FillRect(gui->screensurface, NULL, blackscreen);
}
