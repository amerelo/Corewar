/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 05:11:40 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 23:25:01 by jblondea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void		gui_error_suite(int err)
{
	if (err == TTF_INIT_ERR)
		ft_putstr_fd("Failed to init TTF_Init\n", 2);
	else if (err == TTF_LOAD_ERR)
		ft_putstr_fd("Failed to load font\n", 2);
	else if (err == GUI_INIT_ERR)
		ft_putstr_fd("Failed to initialize!\n", 2);
	else if (err == GUI_LOAD_ERR)
		ft_putstr_fd("Failed to load media!\n", 2);
	else if (err == MIX_LOAD_ERR)
		ft_putstr_fd("Failed to load music!\n", 2);
	else if (err == MIX_INIT_ERR)
		ft_putstr_fd("Failed to init mixer!\n", 2);
}

int				gui_error(int err, int ret, int bye)
{
	if (err == SDL_INIT_ERR)
	{
		ft_putstr_fd("SDL_Init Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
	}
	else if (err == SDL_WIN_ERR)
	{
		ft_putstr_fd("SDL_CreateWindow Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
	}
	else if (err == SDL_IMG_ERR)
	{
		ft_putstr_fd("Unable to load media: SDL Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
	}
	else
		gui_error_suite(err);
	if (bye)
		exit(1);
	return (ret);
}

static int		init(SDL_Window **win, SDL_Surface **screensurface)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		return (gui_error(SDL_INIT_ERR, 0, 0));
	*win = SDL_CreateWindow("Les Champignons de la Reine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (*win == NULL)
		return (gui_error(SDL_WIN_ERR, 0, 0));
	*screensurface = SDL_GetWindowSurface(*win);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,
				MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		ft_putendl_fd(Mix_GetError(), 2);
		return (gui_error(MIX_INIT_ERR, 0, 0));
	}
	SDL_FillRect(*screensurface, NULL,
			SDL_MapRGB((*screensurface)->format, 0, 21, 27));
	return (1);
}

void			init_gui(t_gui *sdl)
{
	ft_bzero(sdl, sizeof(*sdl));
	sdl->cycles_per_sec = 10;
	sdl->cycles_per_frame = 1;
	if (!init(&sdl->win, &sdl->screensurface))
		gui_error(GUI_INIT_ERR, 42, 1);
	if (!init_gui_media(sdl))
		gui_error(GUI_INIT_ERR, 42, 1);
	sdl->events = 0;
	sdl->events |= GUI_PAUSE;
}
