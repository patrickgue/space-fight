#include "sprite.h"

#include "text.h"
#include "font.h"



void print_char(int x, int y, char *text, byte color)
{
    int i = 0, xo = 0;
    while(text[i] != '\0') {
	byte *ch = font[text[i] - 0x20];
	render_sprite_one_c(x + xo, y,8,8, ch, color);
	xo+=8;
	i++;
    }
}

void print_narrow(int x, int y, char *text, byte color)
{
    int i = 0, xo = 0;
    while(text[i] != '\0') {
	byte *ch = font_narrow[text[i] - 0x20];
	render_sprite_one_c(x + xo, y,6,8, ch, color);
	xo+=6;
	i++;
    }
}


void print_large(int x, int y, char *text, byte color)
{
    int i = 0, xo = 0;
    while(text[i] != '\0') {
	if(text[i] >= 0x41 && text[i] < 0x41 + 26) {
	    byte *ch = large_font[text[i] - 0x41];
	    render_sprite_one_c(x + xo, y,8,10, ch, color);
	}
	xo+=8;
	i++;
    }
}
