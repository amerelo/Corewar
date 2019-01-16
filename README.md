# Corewar

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/3e5c9afd45a14ab5ada8fd5cb71f65f5)](https://app.codacy.com/app/amerelo/Corewar?utm_source=github.com&utm_medium=referral&utm_content=amerelo/Corewar&utm_campaign=Badge_Grade_Settings)

42 Project

>	2 parts project involving the parsing / compilation of an asm written “champion” 
followed by the creation of a virtual machine where these champions can crush each other. 
A nice GUI was built using SDL to enjoy the fight. 

The only external C functions allowed were write, malloc, free, open, close, read (except for SDL).

This project is not actively maintained.

### Dependencies ###
 
Install SDL2 by downloading in your packaging manager as root

Arch

* ` pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf `

Fedora

* ` dnf install SDL2-devel SDL2_image-devel SDL2_mixer-devel SDL2_ttf-devel `

Debian/Ubuntu

* ` apt-get install libsdl2-2.0-0  libsdl2-image-dev libsdl2-ttf-dev  libsdl2-mixer-dev `


Or install by compiling sources

* ` http://libsdl.org/release/SDL2-2.0.4.tar.gz `

* ` https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz `

* ` https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.tar.gz `

* ` https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz `

You might need to add the following line in your shell in case some error while loading shared libraries happens to appear

* ` export LD_LIBRARY_PATH=/usr/local/lib `

### Usage Example ###

* ` make `

* ` ./asm mushrooms/Legendary_mushroom.s `

* ` ./asm test_files/helltrain.s `

* ` ./corewar mushrooms/Legendary_mushroom.cor test_files/helltrain.cor -h -g `

* Hit <Space> to start / pause / resume the fight.

* Hit <Escape> for help menu.
