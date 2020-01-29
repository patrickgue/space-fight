#include <stdlib.h>
#include <stdio.h>

#include "vga.h"
#include "sprite.h"
#include "sprites.h"
#include "text.h"
#include "game.h"
#include "keyboard.h"
#include "menu.h"

void show_menu(int x, int y, int w, int h, char selections[11][32], int selections_size, int selection, char *title) {
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
    if(selection == index) {
      rect_fill(x+4,y+19+(index * 10),w-8,10,104);
      print_char(x+5, y+20+(index * 10), selections[index], 0xf);
    }
    else {
      print_char(x+5, y+20+(index * 10), selections[index], 104);
    }
  }
}


void splash_screen()
{

  splash_background();
  rect_fill(19,38,50,1,36);

  
  print_large(21,30,"SPACE", 104);
  
  rect_fill(19,53,50,1,36);
  print_large(21,45,"FIGHT", 104);

  print_narrow(19,180,"Press Enter to continue", 104);
  
  render_sprite_rotate(120,60,96,40,splash,5);
  show_buffer();

  release_pressed(KEY_ENTER);

  while(!is_pressed(KEY_ENTER))
    update_pressed_keys();
  while(is_pressed(KEY_ENTER))
    update_pressed_keys();

}


void splash_background()
{
  int x, y;
  
  for(x = 0; x < SCREEN_WIDTH; x++) {
    for(y = 0; y < SCREEN_HEIGHT; y++) {
      int c = 76 + ((x * y * 17.0) / (320.0 * 200));
      putpixel(x, y, c);
    }
  }
}

void show_help()
{
  bool show_help_loop = true;
  int help_selection = 0;
  int index;
  int max_height = 17;

  while(show_help_loop) {
    clear_buffer(0x64);
    rect_fill(19,18,320-40,1,36);
    print_large(20,10,"HELP", 104);

    rect_fill(19,175,320-40,1,36);
    print_char(20,177,"Esc: back   Cursor Keys: scroll", 104);

    
    for(index = 0; index < max_height; index++) {
      if(help_text[index + help_selection][0] == '#') {
	print_char(20, 22 + (index * 9), help_text[index + help_selection] + 1, 104);
      }
      else 
	print_narrow(20, 22 + (index * 9), help_text[index + help_selection], 104);
    }

    update_pressed_keys();
    if(is_pressed_single(KEY_ESC))
       show_help_loop = false;

    if(help_selection > 0 && is_pressed_single(KEY_UP))
      help_selection--;

    if(help_selection < help_text_length - max_height && is_pressed_single(KEY_DOWN))
      help_selection++;
    
    show_buffer();
  }
}
