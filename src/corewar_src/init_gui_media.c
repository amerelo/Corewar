/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui_media.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 20:33:04 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/26 06:03:16 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static int		load_fanfare(t_gui *gui)
{
	if (!(gui->fanfare =
				Mix_LoadMUS("./resources/music/fanfare.ogg")))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	if (!(gui->hyy =
				Mix_LoadMUS("./resources/music/HEYYEYAAEYAAAEYAEYAA.ogg")))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

static int		load_music(t_gui *gui)
{
	if (Mix_AllocateChannels(2) != 2)
	{
		ft_putendl_fd("Allocate Channels", 2);
		return (0);
	}
	Mix_Volume(0, MIX_MAX_VOLUME);
	if (!(gui->sound = Mix_LoadWAV("./resources/music/se.ogg")))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	if (!(gui->music =
				Mix_LoadMUS("./resources/music/let-the-battle-begin.ogg")))
	{
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	if (!(load_fanfare(gui)))
		return (0);
	Mix_VolumeChunk(gui->sound, MIX_MAX_VOLUME / 2);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	if (Mix_PlayMusic(gui->music, -1))
		return (0);
	Mix_PauseMusic();
	return (1);
}

static int		load_media(t_gui *sdl)
{
	if (!(sdl->xout = IMG_Load("./resources/img/HEYYEYAAEYAAAEYAEYAA.gif")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.play = IMG_Load("./resources/img/play.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.pause = IMG_Load("./resources/img/pause.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.mute = IMG_Load("./resources/img/mute.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.unmute = IMG_Load("./resources/img/unmute.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.slower = IMG_Load("./resources/img/slower.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->mc.faster = IMG_Load("./resources/img/faster.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (TTF_Init() == -1)
		return (gui_error(TTF_INIT_ERR, 0, 0));
	if (!(sdl->txt.font = TTF_OpenFont("./resources/Terminus.ttf", 15)))
		return (gui_error(TTF_LOAD_ERR, 0, 0));
	if (!(sdl->cthulhu = IMG_Load("./resources/img/Cthulhu_mush.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	if (!(sdl->crown = IMG_Load("./resources/img/couronne.png")))
		return (gui_error(SDL_IMG_ERR, 0, 0));
	return (1);
}

int				init_gui_media(t_gui *gui)
{
	if (!load_media(gui))
		return (0);
	if (!load_music(gui))
		return (gui_error(MIX_LOAD_ERR, 0, 0));
	return (1);
}
