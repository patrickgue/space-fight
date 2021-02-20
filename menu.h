#ifndef MENU_H
#define MENU_H

#include "game.h"

#ifdef __DOS__
/* helptext for dos */
static char help_text[15][46] =
{
    "#Description:",
    "",
    "Space Fight is a game where you ",
    "have to fight an alien invasion",
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
    "Esc:            pause game"
};
#else
/* helptext for raylib */
static char help_text[15][46] =
{
    "#Description:",
    "",
    "Space Fight is a game where you ",
    "have to fight an alien invasion",
    "",
    "#Keys in the menu:",
    "",
    "Cursor Keys:    select previous or next entry",
    "Space:          select menu entry",
    "",
    "#Keys in the game",
    "",
    "Cursor Keys:    control the spaceship",
    "Spacebar:       fire bullet",
    "Esc:            pause game"
};
#endif
static int help_text_length = 15;//14;


void show_menu(int, int, int, int, char selections[11][32], int size, int selection, char*);

void splash_screen();

void splash_background();

void show_help();

#endif
