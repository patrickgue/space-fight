#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>


#include "vga.h"
#include "keyboard.h"
#include "sprite.h"
#include "sprites.h"
#include "text.h"
#include "log.h"
#include "menu.h"


int main(int argc, char **argv)
{
  int x = 0x20,y = 0x20, i, j, spacecraft = 0,spacecraft_r = 0;
  int fps = 0, fpsd = 0;
  time_t timestamp;
  char fpst[40];

  char menu_test[2][32] =
    {
     "Continue",
     "Exit",
    };
  int menu_selection = 0;

  bool pause = false;
  bool loop = true;

  byte map[11][24] =
    {
     {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    };

  int map_size = 24;
  int map_x, map_y;
  int splash_x, splash_y;
  
  init_log();
  init_keyboard();
  time(&timestamp);
  
  init_double_buffer();

  set_mode(VGA_256_COLOR_MODE);

  clear_buffer(0x9);
  //show_buffer();

  for(splash_x = 0; splash_x < SCREEN_WIDTH; splash_x++) {

    for(splash_y = 0; splash_y < SCREEN_HEIGHT; splash_y++) {
      

      int c = 76 + ((splash_x * splash_y) / (320.0 * 200.0) * 17.0);

      putpixel(splash_x, splash_y, c);
      //79 - 93
      
    }

  }
  
  rect_fill(19,38,50,1,36);
  print_large(21,30,"SPACE", 104);
  
  rect_fill(19,53,50,1,36);
  print_large(21,45,"FIGHT", 104);

  print_char(19,180,"Press any key to continue!", 104);
  
  render_sprite_rotate(120,60,96,40,splash,5);
  show_buffer();
  getchar();
  

  
  while (loop) {
    clear_buffer(0x9);

    
    rect_fill(0,10,SCREEN_WIDTH,8,55);
    rect_fill(0,18,SCREEN_WIDTH,16,53);

    for(map_x = map_size-1; map_x >= 0; map_x--) {
      for(map_y = 0; map_y < 11; map_y++) {
	if(map[map_y][map_x] == 1) {
	  render_sprite(x+(map_x * 0x14) + (map_y * 6), map_y * 0xc+18,32,32, cube);
	}
	else if (map[map_y][map_x] == 2) {
	  render_sprite(x+(map_x * 0x14) + (map_y * 6), map_y * 0xc+18+16, 32,16,turret);
	}
      }
    }
      
    /*
      render_sprite(0x20 + x,0x40 + 16,32,16,base,0);
      render_sprite(0x34 + x,0x40,32,32,cube,0);
    
      render_sprite(0x3a + x,0x4c + 16,32,16,base,0);
      render_sprite(0x26 + x,0x4c,32,32,cube,0);
    
      render_sprite(0x2c + x,0x58 + 16,32,16,base,0);
      render_sprite(0x40 + x,0x58 + 16,32,16,turret,0);
    */

    if(spacecraft == 0)
      render_sprite_rotate(0x40,y,16,16,spaceship1, spacecraft_r);
    else if(spacecraft < 10)
      render_sprite_rotate(0x40,y,16,16,spaceship2, spacecraft_r);
    else
      render_sprite_rotate(0x40,y,16,16,spaceship3, spacecraft_r);



    rect_fill(0,SCREEN_HEIGHT - 24,SCREEN_WIDTH,8,55);
    rect_fill(0,SCREEN_HEIGHT - 16,SCREEN_WIDTH,16,53);

    sprintf(fpst, "FPS: %d | %02x %02x | %d", fpsd, x,y, pause);
    print_char(4,SCREEN_HEIGHT - 12,fpst,0xF);

    


    update_pressed_keys();
    if(!pause) {
      

      if(spacecraft > 0)
	spacecraft--;


      x-=2;
      if(x < -320)
	x = 320;
      fps++;

      if(time(NULL) > timestamp) {
	fpsd = fps;
	fps = 0;
	time(&timestamp);
      }

      spacecraft_r = 0;
      if(is_pressed(KEY_LEFT)) {
	x++;
	spacecraft_r = 4;
	release_pressed(KEY_RIGHT);
      }

      if(is_pressed(KEY_RIGHT)) {
	x--;
	spacecraft_r = 0;
	release_pressed(KEY_LEFT);
      }

      if(is_pressed(KEY_UP)) {
	if(y > 0x1a)
	  y-=3;
	spacecraft_r = 3;
	release_pressed(KEY_DOWN);
      }

      if(is_pressed(KEY_DOWN)) {
	if(y < 0xa9)
	  y+=3;
	spacecraft_r = 1;
	release_pressed(KEY_UP);
      }

      if(is_pressed(KEY_ESC)) {
	pause = true;
      }

      if(is_pressed(KEY_LEFT) || is_pressed(KEY_RIGHT)
	 || is_pressed(KEY_UP) || is_pressed(KEY_DOWN)) {
	spacecraft = 20;
      }
    }
    else {
      if(is_pressed(KEY_UP)) {
	if(menu_selection > 0)
	  menu_selection--;
      }

      if(is_pressed(KEY_DOWN)) {
	if(menu_selection < 1)
	  menu_selection++;
      }
      
      if(is_pressed(KEY_ENTER)) {
	if(menu_selection == 0) {
	  pause = false;
	}
	else if(menu_selection == 1) {
	  loop = false;
	}
      }

      show_menu(0x20, 0x20, 0x100, 0x88, menu_test, 2, &menu_selection, "MENU");
    
    }

    show_buffer();



    
  }
  
  set_mode(TEXT_MODE);
  free_double_buffer();
  close_log();
  free_keyb_buf();
  return 1;
}
