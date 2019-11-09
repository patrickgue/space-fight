#ifndef SPRITE_H
#define SPRITE_H

#include "game.h"

void render_sprite(int x, int y, int w, int h, byte *);
void render_sprite_rotate(int x, int y, int w, int h, byte *, byte r);
void render_sprite_no_check(int x, int y, int w, int h, byte *);

void render_sprite_one_c(int x, int y, int w, int h, byte *sprite, byte color);

#endif
