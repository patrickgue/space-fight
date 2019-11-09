#include <stdlib.h>

#include "vga.h"
#include "sprite.h"
#include "sprites.h"
#include "text.h"

void show_menu(int x, int y, int w, int h, char selections[11][32], int selections_size, int *selection, char *title) {
  int index;
  
  rect_fill(x+4,y+4,w-8,h-8,0xf);
  render_sprite(x,    y,    4,4, corner);
  render_sprite_rotate(x+w-4,y,    4,4, corner,1);
  render_sprite_rotate(x+w-4,y+h-4,4,4, corner,2);
  render_sprite_rotate(x,    y+h-4,4,4, corner,3);
  /* left */
  for(index = 4; index < h - 4; index++) {
    render_sprite(x,y+index,4,1,border);
  }

  /* top */
  for(index = 4; index < w - 4; index++) {
    render_sprite_rotate(x+index,y,4,1,border,1);
  }

  /* right */
  for(index = 4; index < h - 4; index++) {
    render_sprite_rotate(x+w-4,y+index,4,1,border,2);
  }

  /* bottom */
  for(index = 4; index < w - 4; index++) {
    render_sprite_rotate(x+index,y+h-4,4,1,border,3);
  } 
  rect_fill(x+4,y+13,w-8,1,36);
  print_large(x+5,y+5,title, 104);
  
  
  for(index = 0; index < selections_size; index++) {
    if(*selection == index) {
      rect_fill(x+4,y+19+(index * 10),w-8,10,104);
      print_char(x+5, y+20+(index * 10), selections[index], 0xf);
    }
    else {
      print_char(x+5, y+20+(index * 10), selections[index], 104);
    }
  }
}
