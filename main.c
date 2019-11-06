#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>



#include "vga.h"
#include "keyboard.h"
#include "sprite.h"
#include "sprites.h"


int main(int argc, char **argv)
{
  int x = 20,y = 20, i, j, spacecraft = 0;
  bool loop = true;
  int map[32] = {0,0,0,20,0,0,0,60,0,0,0,0,0,0,30,0,0,40,0,0,0,0,50,0,0,120,0,0,100,0,0,80};
  int mapsize = 32;
  int bullet_x[100] =
    {
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    }, bullet_y[100], bullet_count = 0;
  

  
  init_double_buffer();

  set_mode(VGA_256_COLOR_MODE);

  
  while (loop) {
    clear_buffer(0x9);

    for(i = 0; i < mapsize; i++) {
      if(map[i] != 0) {
	  render_sprite(i*16+x,map[i],mapelm);
	  render_sprite(i*16+x,map[i] + 16,mapelm2);
      }
    }
    

    

    if(spacecraft == 0)
      render_sprite(30,y,spaceship1);
    else if(spacecraft < 10)
      render_sprite(30,y,spaceship2);
    else
      render_sprite(30,y,spaceship3);
  

    for(i = 0; i < 100; i++) {
      if(bullet_x[i] > 0) {
	putpixel(bullet_x[i], bullet_y[i], 14);
	bullet_x[i]++;
	if(bullet_x[i] > 320)
	  bullet_x[i] = -1;
      }
    }
    

    switch(read_scancode()) {
    case KEY_ESC:
      loop = false;
      printf("exit loop\n");
      break;
    case KEY_LEFT:
      x++;
      break;
    case KEY_RIGHT:
      x--;
      spacecraft = 20;
      break;
    case KEY_UP:
      y-=2;
      break;
    case KEY_DOWN:
      y+=2;
      break;
    case KEY_SPACEBAR:
      bullet_x[bullet_count] = 43, bullet_y[bullet_count] = y + 7;
      bullet_count++;
      if(bullet_count > 99) {
	bullet_count = 0;
      }
      break;
    default:
      break;
    }
    show_buffer();


    free_double_buffer();
    if(spacecraft > 0)
      spacecraft--;

    x-=2;

    if(x < -1 * mapsize * 16)
      x = 320;

  }
  
  set_mode(TEXT_MODE);
  return 1;
}
