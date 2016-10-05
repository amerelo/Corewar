/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 03:11:30 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 16:34:28 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

SDL_Color		make_sdl_color(int color)
{
	SDL_Color	s_color;

	s_color.r = ((color & 0xFF0000) >> 16);
	s_color.g = ((color & 0x00FF00) >> 8);
	s_color.b = ((color & 0x0000FF));
	return (s_color);
}

t_txt			to_screen(int x, int y, int color)
{
	t_txt		text;

	text.position.x = x;
	text.position.y = y;
	text.color = make_sdl_color(color);
	text.str = NULL;
	return (text);
}

void			draw_str(t_gui *gui, char *str, t_txt params)
{
	params.str = TTF_RenderText_Blended(gui->txt.font, str, params.color);
	SDL_BlitSurface(params.str, NULL, gui->screensurface, &params.position);
	SDL_FreeSurface(params.str);
	params.str = NULL;
}

void			draw_itostr(t_gui *gui, int nb, t_txt params)
{
	char		*s;

	if (!(s = ft_itoa(nb)))
		return ;
	draw_str(gui, s, params);
	ft_strdel(&s);
}
