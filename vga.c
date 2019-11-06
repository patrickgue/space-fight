#include <dos.h>
#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <conio.h>

#include "game.h"

#include "vga.h"


byte far *screenptr;
byte *VGA=(byte *)0xA0000000L;        /* this points to video memory. */



void init_double_buffer()
{
  screenptr = (byte*) malloc(320 * 200);
  if(screenptr == NULL) {
    printf("Not enough memory\n");
    exit(1);
  }
}


void clear_buffer()
{
  memset(screenptr, 0x0, SCREEN_SIZE);
}


void free_double_buffer()
{
  free(screenptr);
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
  screenptr[x + (y * SCREEN_WIDTH)] = c;
}


void show_buffer()
{
  #ifdef VERTICAL_RETRACE
  //while ((inp(INPUT_STATUS_1) & VRETRACE));
  //  while (!(inp(INPUT_STATUS_1) & VRETRACE));
  #endif
    memcpy((void*)VGA, (void*)screenptr,SCREEN_SIZE);
}
