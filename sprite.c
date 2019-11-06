#include "sprite.h"
#include "vga.h"


void _render_sprite(int x, int y, int w, int h, byte *sprite) {
  int ix, iy;
  for(ix = 0; ix < w; ix++) {
    for(iy = 0; iy < h; iy++) {
      byte c =  sprite[(iy * 16) + ix];
      if(c != 0x10 && x + ix >= 0 && x + ix < SCREEN_WIDTH
	 && y + iy >= 0 && ix < SCREEN_HEIGHT)
	putpixel(x + ix, y + iy, c);
    }
  }
}

void render_sprite(int x, int y, byte *sprite)
{
  _render_sprite(x,y,16,16,sprite);
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


