#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <mem.h>

#include "vga.h"
#include "game.h"
#include "keyboard.h"
#include "log.h"
#include "menu.h"
#include "map.h"




int main(int argc, char **argv)
{

  
    byte *map;

    int map_size = map1_size;
    bool main_menu_loop = true;
  

    char main_menu[3][32] =
	{
	    "Play",
	    "Help",
	    "Exit"
	};
    byte main_menu_option_length = 3;
    byte main_menu_selection = 0;
  
    if(argc > 1 && strcmp(argv[1], "-d") == 0)
	debug = true;

    init_log();
    init_keyboard();
  
    init_double_buffer();

    set_mode(VGA_256_COLOR_MODE);


    if(!debug) {
	splash_screen();
    
    }
    else {
	while(is_pressed(KEY_ENTER));
    }
  
    while(main_menu_loop) {
	clear_buffer(104);
	show_menu(0x20, 0x20, 0x100, 0x88, main_menu, main_menu_option_length, main_menu_selection, "SPACE FIGHTER");
    
	if(main_menu_selection > 0 && is_pressed_single(KEY_UP))
	    main_menu_selection--;
	if(main_menu_selection < main_menu_option_length - 1 && is_pressed_single(KEY_DOWN))
	    main_menu_selection++;

	if(is_pressed_single(KEY_ENTER)) {
	    switch(main_menu_selection) {
	    case 0:
		map = (byte*) malloc(map_size * 11);
		_fmemcpy(map, map1, map_size * 11);
		game(map, map_size);
		release_pressed(KEY_ENTER);
		break;
	    case 1:
		show_help();
		break;
	    case 2:
		main_menu_loop = false;
		break;
	    }

	}
    
	show_buffer();
    
    }



    reset_keyboard();
    free_double_buffer();
    set_mode(TEXT_MODE);
    close_log();
    free_keyb_buf();

    return 1;
}
