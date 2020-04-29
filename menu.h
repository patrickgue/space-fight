#ifndef MENU_H
#define MENU_H

#include "game.h"

static char help_text[23][46] =
{
    "#Description:",
    "",
    "Space Fight is a game where you ",
    "have to fight a alien invasion",
    "",
    "#Keys in the menu:",
    "",
    "Cursor Keys:    select previous or next entry",
    "Enter:          select menu entry",
    "",
    "#Keys in the game",
    "",
    "Cursor Keys:    control the spaceship",
    "Spacebar:       fire bullet",
    "Esc:            pause game",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
};
static int help_text_length = 23;//14;


void show_menu(int, int, int, int, char selections[11][32], int size, int selection, char*);

void splash_screen();

void splash_background();

void show_help();

#endif
