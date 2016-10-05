/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_commands_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 20:15:32 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/23 21:19:43 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

int				help_key(SDL_Event event)
{
	int	x;
	int	y;

	if (event.type == SDL_KEYDOWN
			&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		return (1);
	x = event.button.x;
	y = event.button.y;
	if (event.type == SDL_MOUSEBUTTONUP
			&& (event.button.button == SDL_BUTTON_LEFT
				|| event.button.button == SDL_BUTTON_RIGHT))
	{
		if ((x >= 17 && x <= 24) && (y >= 1300 && y <= 1308))
			return (1);
	}
	return (0);
}

int				pause_key(SDL_Event event)
{
	int x;
	int y;

	if (event.type == SDL_KEYDOWN
			&& event.key.keysym.scancode == SDL_SCANCODE_SPACE)
		return (1);
	x = event.button.x;
	y = event.button.y;
	if (event.type == SDL_MOUSEBUTTONUP
			&& (event.button.button == SDL_BUTTON_LEFT
				|| event.button.button == SDL_BUTTON_RIGHT))
	{
		if ((x >= 1469 && x <= 1539) && (y >= 1246 && y <= 1387))
			return (1);
	}
	return (0);
}

int				mute_key(SDL_Event event)
{
	int x;
	int y;

	if (event.type == SDL_KEYDOWN
			&& event.key.keysym.scancode == SDL_SCANCODE_M)
		return (1);
	x = event.button.x;
	y = event.button.y;
	if (event.type == SDL_MOUSEBUTTONUP
			&& (event.button.button == SDL_BUTTON_LEFT
				|| event.button.button == SDL_BUTTON_RIGHT))
	{
		if ((x >= 1549 && x <= 1618) && (y >= 1246 && y <= 1387))
			return (1);
	}
	return (0);
}

int				minus_key(SDL_Event event)
{
	int x;
	int y;

	if (event.type == SDL_KEYDOWN
			&& (event.key.keysym.scancode == SDL_SCANCODE_MINUS
				|| event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS))
		return (1);
	x = event.button.x;
	y = event.button.y;
	if (event.type == SDL_MOUSEBUTTONDOWN
			&& (event.button.button == SDL_BUTTON_LEFT
				|| event.button.button == SDL_BUTTON_RIGHT))
	{
		if ((x >= 1807 && x <= 1879) && (y >= 1246 && y <= 1387))
			return (1);
	}
	return (0);
}

int				plus_key(SDL_Event event)
{
	int x;
	int y;

	if (event.type == SDL_KEYDOWN
			&& (event.key.keysym.scancode == SDL_SCANCODE_EQUALS
				|| event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS))
		return (1);
	x = event.button.x;
	y = event.button.y;
	if (event.type == SDL_MOUSEBUTTONDOWN
			&& (event.button.button == SDL_BUTTON_LEFT
				|| event.button.button == SDL_BUTTON_RIGHT))
	{
		if ((x >= 1888 && x <= 1962) && (y >= 1246 && y <= 1387))
			return (1);
	}
	return (0);
}
