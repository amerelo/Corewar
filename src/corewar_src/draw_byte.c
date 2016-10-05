/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_byte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 10:27:48 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/23 02:35:57 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gui.h"

void				assign_hexa(unsigned char i, char *str)
{
	str[1] = (i % 16) >= 10 ? (i % 16) + 'A' - 10 : (i % 16) + '0';
	i /= 16;
	str[0] = (i % 16) >= 10 ? (i % 16) + 'A' - 10 : (i % 16) + '0';
	str[2] = '\0';
}

t_player			*get_player_by_index(char index, t_player *players)
{
	while (players)
	{
		if (players->index == index)
			return (players);
		players = players->next;
	}
	return (NULL);
}

SDL_Color			color_byte(char *p, t_player *players, char paused)
{
	t_player		*player;

	player = get_player_by_index((*p & 0x07), players);
	if ((*p & 0xf8))
	{
		if (!(paused & GUI_PAUSE))
			*p = (((*p >> 3) - 1) << 3) | (*p & 0x07);
		return (make_sdl_color(player->color_hl));
	}
	if (player)
		return (make_sdl_color(player->color));
	else
		return (make_sdl_color(EMPTY_COLOR));
}

void				draw_byte(t_vm *vm, t_gui *gui, int i)
{
	char			tm[3];

	assign_hexa(vm->memory[i], tm);
	gui->txt.color = color_byte(&vm->color[i], vm->players, gui->events);
	gui->txt.position.x += 22;
	if (!(gui->txt.str =
				TTF_RenderText_Blended(gui->txt.font, tm, gui->txt.color)))
		return ;
	SDL_BlitSurface(gui->txt.str, NULL,
			gui->screensurface, &gui->txt.position);
	SDL_FreeSurface(gui->txt.str);
}
