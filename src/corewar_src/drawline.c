/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:11:13 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/23 16:11:35 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			draw_hrz_line(SDL_Surface *s, int c, SDL_Rect p, int max)
{
	while (p.x < max)
	{
		SDL_FillRect(s, &p, c);
		++p.x;
	}
}

void			draw_vrt_line(SDL_Surface *s, int c, SDL_Rect p, int max)
{
	while (p.y < max)
	{
		SDL_FillRect(s, &p, c);
		++p.y;
	}
}

SDL_Rect		rect_props(int x, int y, int size)
{
	SDL_Rect		rectangle;

	rectangle.h = size;
	rectangle.w = size;
	rectangle.x = x;
	rectangle.y = y;
	return (rectangle);
}
