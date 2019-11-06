#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "vga.h"
#include "keyboard.h"
#include "sprite.h"
#include "sprites.h"


int main(int argc, char **argv)
{
  int x = 20,y = 20, i, j;
  bool loop = true;

  byte background[256];

  for(i = 0; i < 16; i++) {
    for(j = 0; j < 16; j++) {
      background[i + (j * 16)] = (j + i) % 2 == 0 ? 0xf : 0x4; 
    }
  }

  init_double_buffer();
  init_keyboard();

  set_mode(VGA_256_COLOR_MODE);
  
  while (loop) {


    //render_sprite_small(x,y,test);
    
    /*for(i = 0; i < 20; i++) {
      for(j = 0; j < 13; j++){
	render_sprite(i*16,j*16,background);
      }
      }*/

    clear_buffer();
    
    render_sprite(20,20,pyramid);
    render_sprite(x,y,test2);

    if(key_pressed(KEY_SPACEBAR)) {
      putpixel(20,80,0xf);
    }

    
    switch(get_scan()) {
    case KEY_ESC:
      loop = false;
      printf("exit loop\n");
      break;
    case KEY_LEFT:
      x--;
      break;
    case KEY_RIGHT:
      x++;
      break;
    case KEY_UP:
      y--;
      break;
    case KEY_DOWN:
      y++;
      break;
    default:
      show_buffer();
      break;
    }



  }
  
  free_double_buffer();
  set_mode(TEXT_MODE);
  deinit_keyboard();
  return 1;
}
