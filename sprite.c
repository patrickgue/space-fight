#include "sprite.h"
#include "vga.h"

void render_sprite(int x, int y, byte *sprite)
{
  int w, h;
  for(w = 0; w < 16; w++) {
    for(h = 0; h < 16; h++) {
      byte c =  sprite[(h * 16) + w];
      if(c != 0x10)
	putpixel(x + w, y + h, c);
    }
  }
}


void render_sprite_small(int x, int y, byte *sprite)
{
  int w, h;
  for(w = 0; w < 8; w++) {
    for(h = 0; h < 8; h++) {
      byte c =  sprite[(h * 8) + w];
      if(c != 0x10)
	putpixel(x + w, y + h, c);
    }
  }
}
