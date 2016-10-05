# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblondea <jblondea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/17 06:36:42 by flevesqu          #+#    #+#              #
#    Updated: 2016/07/25 01:13:15 by rliou-ke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = corewar
NAME2 = asm

NAME = $(NAME1) $(NAME2)

LIB_INCLUDES = libft/includes/
SRC_INCLUDES = includes/

DIR1 = src/corewar_src/
DIR2 = src/asm_src/

FILE1 =	corewar.c\
		parsing.c\
		champion_treatment.c\
		game.c\
		process.c\
		op_fct_1_5.c\
		op_fct_6_10.c\
		op_fct_11_15.c\
		op_fct_16.c\
		init_gui.c\
		init_gui_media.c\
		draw_byte.c\
		display_winner.c\
		draw.c\
		param_byte.c\
		read_bytes.c\
		draw_border.c\
		draw_pcs.c\
		drawline.c\
		gui.c\
		refresh_gui.c\
		gui_events.c\
		gui_commands_keys.c\
		gui_vm_status.c\
		print_media_control.c\
		print_players_status.c
FILE2 = asm.c load_file.c compile_champ.c write_champ.c error.c load_ops.c \
		print_ops.c print_champ.c ft_logs.c char_types.c string_types.c \
		string_tools.c head.c head_parts.c instruction.c label.c \
		compil_champ_find_and_set.c compil_champ_label.c compil_champ_type.c \

SRC1 := $(addprefix $(DIR1), $(FILE1))
SRC2 := $(addprefix $(DIR2), $(FILE2))

WFLAGS = -Wall -Werror -Wextra -O3 -march=native
#WFLAGS = -Wall -Werror -Wextra -O0 -g -fsanitize=address

LFLAGS = -L libft/ -lft

CC = gcc

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

HEADER_0 = $(SRC_INCLUDES)op.h
HEADER_1 = $(SRC_INCLUDES)$(NAME1).h
HEADER_2 = $(SRC_INCLUDES)$(NAME2).h
HEADER_3 = $(SRC_INCLUDES)gui.h

SDL2        = -lSDL2
SDL2_IMG    = -lSDL2_image
SDL2_TTF    = -lSDL2_ttf
SDL2_MIXER  = -lSDL2_mixer

SDL2_HEADER         = -I /usr/include/SDL2/
SDL2_HEADER_MODULES   = -I /usr/local/include/SDL2/

SDL         = $(SDL2_MIXER) $(SDL2_IMG) $(SDL2_TTF) $(SDL2)
SDL_HEADER  = $(SDL2_HEADER_MODULES) $(SDL2_HEADER)

SYS		:= $(shell gcc -dumpmachine)
ifneq (, $(findstring darwin, $(SYS)))
SDL2_HEADER         = -I ~/Library/Frameworks/SDL2.framework/Headers/
SDL2_HEADER_MIXER   = -I ~/Library/Frameworks/SDL2_mixer.framework/Headers/
SDL2_HEADER_IMG     = -I ~/Library/Frameworks/SDL2_image.framework/Headers/
SDL2_HEADER_TTF     = -I ~/Library/Frameworks/SDL2_ttf.framework/Headers/

SDL2        = -framework SDL2
SDL2_IMG    = -framework SDL2_image
SDL2_TTF    = -framework SDL2_ttf
SDL2_MIXER  = -framework SDL2_mixer

SDL         = -F ~/Library/Frameworks $(SDL2_MIXER) $(SDL2_IMG) $(SDL2_TTF) $(SDL2)
SDL_HEADER  = -F ~/Library/Frameworks $(SDL2_HEADER_MIXER) $(SDL2_HEADER) $(SDL2_HEADER_IMG) $(SDL2_HEADER_TTF)
endif

all : $(NAME)

%.o: %.c $(HEADER_0) $(HEADER_1) $(HEADER_2) $(HEADER_3)
	    $(CC) -c $(WFLAGS) -I $(LIB_INCLUDES) -I $(SRC_INCLUDES) $(SDL_HEADER) $< -o $@

$(NAME1) : $(OBJ1) $(HEADER_1) $(HEADER_0) $(HEADER_3)
	    make -C libft
		    $(CC) -o $(NAME1) $(OBJ1) $(WFLAGS) $(LFLAGS) $(SDL) $(SDL_HEADER)

$(NAME2) : $(OBJ2) $(HEADER_2) $(HEADER_0)
	make -C libft
	$(CC) -o $(NAME2) $(OBJ2) $(WFLAGS) $(LFLAGS)

clean :
	rm -rf $(OBJ1) $(OBJ2)

lclean :
	make -C libft/ clean

fclean : clean
	rm -f $(NAME1) $(NAME2)

lfclean :
	make -C libft/ fclean

re : fclean all

lre :
	make -C libft/ re

sdl :
ifneq (, $(findstring darwin, $(SYS)))
	rm -rf /tmp/libsdl2
	mkdir -p ~/Library/Frameworks
	git clone https://rliou-ke@bitbucket.org/rliou-ke/sdl2.git /tmp/libsdl2
	cp -r /tmp/libsdl2/SDL2* ~/Library/Frameworks/.
	rm -rf /tmp/libsdl2
else
	@echo "Error: make sdl is only available on Mac OSX El Capitan"
	@echo "You have to install SDL2 library yourself in order to use it on a GNU/Linux distribution"
endif

.PHONY: all clean fclean re lclean lfclean lre sdl
