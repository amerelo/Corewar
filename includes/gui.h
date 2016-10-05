/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 03:06:33 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/24 22:10:00 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "corewar.h"
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <time.h>

# define SCREEN_WIDTH		2000
# define SCREEN_HEIGHT		1320

# define SDL_INIT_ERR		1
# define SDL_WIN_ERR		2
# define SDL_IMG_ERR		3
# define TTF_INIT_ERR		4
# define TTF_LOAD_ERR		5
# define GUI_INIT_ERR		6
# define GUI_LOAD_ERR		7
# define MIX_LOAD_ERR		8
# define MIX_INIT_ERR		9

# define GUI_MUTE			0x1
# define GUI_PAUSE			0x2
# define GUI_HELP			0x4

# define INFOS_HEIGHT_SPACE	30

# define P_1_COLOR		0xDC322F
# define P_2_COLOR		0x268BD2
# define P_3_COLOR		0xB58900
# define P_4_COLOR		0x859900
# define P_1_COLOR_HL	0xEA8482
# define P_2_COLOR_HL	0x7CB9E4
# define P_3_COLOR_HL	0xD2B866
# define P_4_COLOR_HL	0xB5C166
# define EMPTY_COLOR	0x657B83
# define WHITE_COLOR	0xFFFFFF
# define BLACK_COLOR	0x00151B
# define GRAY_COLOR		0x586E75

typedef struct		s_border
{
	int				x;
	int				y;
	int				xmax;
	int				ymax;
	int				size;
	int				color;
}					t_border;

typedef struct		s_txt
{
	SDL_Rect		position;
	SDL_Surface		*str;
	SDL_Color		color;
	TTF_Font		*font;
}					t_txt;

typedef struct		s_mediactl
{
	SDL_Surface		*play;
	SDL_Surface		*pause;
	SDL_Surface		*unmute;
	SDL_Surface		*mute;
	SDL_Surface		*slower;
	SDL_Surface		*faster;
}					t_mediactl;

typedef struct		s_gui
{
	SDL_Window		*win;
	SDL_Surface		*screensurface;
	SDL_Surface		*xout;
	SDL_Surface		*cthulhu;
	SDL_Surface		*crown;
	t_mediactl		mc;
	SDL_Event		e;
	t_txt			txt;
	Mix_Music		*music;
	Mix_Music		*hyy;
	Mix_Music		*fanfare;
	Mix_Chunk		*sound;
	char			events;
	int				cycles_per_sec;
	clock_t			last_render_time;
	int				cycles_per_frame;
	int				frame_cycles_count;
	int				cycles_to_die;
}					t_gui;

typedef struct		s_input
{
	char			key[SDL_NUM_SCANCODES + 1];
}					t_input;

SDL_Color			make_sdl_color(int color);
void				draw_str(t_gui *gui, char *str, t_txt params);
void				draw_itostr(t_gui *gui, int nb, t_txt params);
t_txt				to_screen(int x, int y, int color);
void				draw_hrz_line(SDL_Surface *s, int c, SDL_Rect p, int max);
void				draw_vrt_line(SDL_Surface *s, int c, SDL_Rect p, int max);
SDL_Rect			rect_props(int x, int y, int size);

int					help_key(SDL_Event event);
int					pause_key(SDL_Event event);
int					unmute_key(SDL_Event event);
int					mute_key(SDL_Event event);
int					minus_key(SDL_Event event);
int					plus_key(SDL_Event event);
void				gui_pause(t_vm *vm, t_gui *gui);
void				update_events(t_input *in);
void				do_events(t_input in, t_vm *vm, t_gui *gui);
void				press_any_key_to_quit(t_gui *gui);

void				draw_vm(t_vm *vm, t_gui *gui);
void				draw_byte(t_vm *vm, t_gui *gui, int i);
SDL_Color			color_byte(char *p, t_player *players, char paused);
void				draw_pcs(t_vm *vm, t_gui *gui);
void				draw_border(t_gui *gui);
void				draw_help(t_gui *gui);

void				print_breakdown(t_vm *vm, t_gui *gui);
void				print_media_control(t_gui *gui);
void				print_infos(t_vm *vm, t_gui *gui);
void				print_players_infos(t_vm *vm, t_gui *gui, t_player *win);
void				display_winner(t_vm *vm, t_gui *gui);

int					gui_error(int err, int ret, int bye);
int					init_gui_media(t_gui *gui);
void				init_gui(t_gui *gui);
void				launch_gui(t_vm *vm);
void				destroy_gui(t_gui *gui);
void				refresh_gui(t_vm *vm, t_gui *gui);
void				let_the_game_begin(t_vm *vm, t_gui *gui);
#endif
