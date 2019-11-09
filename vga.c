#include <dos.h>
#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <conio.h>

#include "game.h"

#include "vga.h"

/* double buffer */
byte far *double_buffer;

/* Pointer to VGA memory */
byte *VGA=(byte *)0xA0000000L;




void init_double_buffer()
{
  double_buffer = (byte*) malloc(320 * 200);
  if(double_buffer == NULL) {
    printf("Not enough memory\n");
    exit(1);
  }
}


void clear_buffer(byte c)
{
  memset(double_buffer, c, SCREEN_SIZE);
}


void free_double_buffer()
{
  free(double_buffer);
}

void set_mode(byte mode)
{
  union REGS regs;

  regs.h.ah = SET_MODE;
  regs.h.al = mode;
  int86(VIDEO_INT, &regs, &regs);
}


void putpixel(int x, int y, int c)
{
  double_buffer[(y<<8) + (y<<6) + x] = c;
}

void put_row(int x, int y, byte *color, byte size)
{
  byte far *p;

  p=double_buffer + y*SCREEN_WIDTH +x;

  _fmemcpy(p, color, size);

}

void rect_fill(int x, int y, int width, int height, byte colour)
{
  byte far *p;
	
  p=double_buffer + y*SCREEN_WIDTH +x;
  while ( height--) {
    _fmemset(p, colour, width);
    p+=SCREEN_WIDTH;
  }
}


void show_buffer()
{
  memcpy((void*)VGA, (void*)double_buffer,SCREEN_SIZE);
}
