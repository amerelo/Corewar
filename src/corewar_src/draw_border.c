/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_border.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 06:58:24 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/23 20:41:49 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void				draw_border(t_gui *gui)
{
	t_border		b;

	b.x = 1460;
	b.y = 22;
	b.xmax = 1960;
	b.ymax = 1286;
	b.size = 8;
	b.color = 0x586e75;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.ymax, b.size), b.xmax + 1);
	draw_vrt_line(gui->screensurface, b.color,
			rect_props(b.xmax, b.y, b.size), b.ymax);
	draw_vrt_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.ymax);
	b.y = 235;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
	b.y = 1236;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
}

static void			print_instructions(t_gui *gui)
{
	int				x;
	int				y;
	int				gap;

	x = 50;
	y = 1125;
	gap = 25;
	draw_str(gui, "ESCAPE       show/hide menu",
			to_screen(x, 1125, WHITE_COLOR));
	y += gap;
	draw_str(gui, "q            quit", to_screen(x, y, WHITE_COLOR));
	y += gap;
	draw_str(gui, "m            mute on/off", to_screen(x, y, WHITE_COLOR));
	y += gap;
	draw_str(gui, "+            speed up cycles per second",
			to_screen(x, y, WHITE_COLOR));
	y += gap;
	draw_str(gui, "-            slow down cycles per second",
			to_screen(x, y, WHITE_COLOR));
	y += gap;
	draw_str(gui, "SPACE        pause", to_screen(x, y, WHITE_COLOR));
}

static void			draw_little_square(t_gui *gui)
{
	t_border		b;

	b.x = 16;
	b.y = 1298;
	b.xmax = b.x + 1;
	b.ymax = 1296;
	b.size = 7;
	b.color = 0x586e75;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
}

void				draw_help(t_gui *gui)
{
	t_border		b;

	draw_little_square(gui);
	if (!(gui->events & GUI_HELP))
		return ;
	b.y = 1094;
	b.x = 27;
	b.xmax = 200;
	b.ymax = 1288;
	b.size = 200;
	b.color = 0x002b36;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
	b.size = 5;
	b.xmax = 395;
	b.color = 0x586e75;
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.xmax);
	draw_hrz_line(gui->screensurface, b.color,
			rect_props(b.x, b.ymax, b.size), b.xmax + 1);
	draw_vrt_line(gui->screensurface, b.color,
			rect_props(b.x, b.y, b.size), b.ymax);
	draw_vrt_line(gui->screensurface, b.color,
			rect_props(b.xmax, b.y, b.size), b.ymax);
	print_instructions(gui);
}
