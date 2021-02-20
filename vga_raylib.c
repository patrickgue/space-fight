//
// Created by Patrick Günthard on 20.02.21.
//

#include "vga.h"

#include "log.h"
#include "game.h"

byte main_buffer[320 * 200];
byte double_buffer[320 * 200];

void set_mode(byte mode)
{
    log_debug("setup raylib");
}


void init_double_buffer()
{

}

void clear_buffer(byte color)
{}

void free_double_buffer()
{}

void putpixel(int x, int y, int c)
{}

void put_row(int x, int y, byte *c, byte size)
{}

void rect_fill(int x, int y, int w, int h, byte color)
{}

void show_buffer()
{
    memcpy((void*)main_buffer, (void*)double_buffer,SCREEN_SIZE);
}
