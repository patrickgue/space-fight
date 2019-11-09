/**
 
 */
#include "sprite.h"
#include "vga.h"

#include <mem.h>

/* copy sprite to video buffer */
void render_sprite(int x, int y, int w, int h, byte *sprite) {
  int ix = 0, iy = 0;

  for(ix = 0; ix < w; ix++) {
    for(iy = 0; iy < h; iy++) {
      byte c = sprite[(iy * w) + ix];
      if(c != 0xff && x + ix >= 0 && x + ix < SCREEN_WIDTH
	 && y + iy >= 0 && ix < SCREEN_HEIGHT) {
	  putpixel(x + ix, y + iy, c);
      }

    }
  }
  
}

/* copy rotated sprite to video buffer */
void render_sprite_rotate(int x, int y, int w, int h, byte *sprite, byte r) {
  int ix = 0, iy = 0;

  for(ix = 0; ix < w; ix++) {
    for(iy = 0; iy < h; iy++) {
      byte c = sprite[(iy * w) + ix];
      if(c != 0xff && x + ix >= 0 && x + ix < SCREEN_WIDTH
	 && y + iy >= 0 && ix < SCREEN_HEIGHT) {
	if(r == 0) {
	  putpixel(x + ix, y + iy, c);
	}
	else if(r == 1) {
	  putpixel(x + (h-iy-1), y + ix,c);
	  
	}
	else if(r == 2) {
	  putpixel(x + w - ix -1, y + h - iy - 1, c);
	}
	else if(r == 3) {
	  putpixel(x+iy, y+ (w-ix-1) , c);
	}

	
	else if(r == 4) {
	  putpixel(x + w - ix - 1, y + iy, c);
	}
	else if(r == 5) {
	  putpixel(x + ix, y + h - iy -1, c);
	}
      }

    }
  }
  
}

/* render sprite without checking if it overflows the screen (for additional performance) */
void render_sprite_no_check(int x, int y, int w, int h, byte *sprite) {
  int ix = 0, iy = 0;

  for(ix = 0; ix < w; ix++) {
    for(iy = 0; iy < h; iy++) {
      byte c = sprite[(iy * w) + ix];
      putpixel(x + ix, y + iy, sprite[(iy * w) + ix]);
    }
  }
  
}






void render_sprite_one_c(int x, int y, int w, int h, byte *sprite, byte color)
{
  int ix, iy;
  for(ix = 0; ix < w; ix++) {
    for(iy = 0; iy < h; iy++) {
      byte c =  sprite[(iy * w) + ix];
      if(c == 1)
	putpixel(x + ix, y + iy, color);
    }
  }
}
