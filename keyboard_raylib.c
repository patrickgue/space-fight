#include <stdbool.h>
#include <raylib.h>
#include <stdio.h>
#include "keyboard.h"
#include "log.h"

bool currently_pressed[0x80];

void init_keyboard()
{
    log_debug("Init Keyboard");
    SetExitKey(KEY_BACKSPACE);
}

void update_pressed_keys(void)
{
    int key_pressed = GetKeyPressed();
    int index;
    for(index = 0; index < 0x80; index++)
    {
        currently_pressed[index] = false;
    }
    currently_pressed[key_pressed] = true;
}

bool is_pressed(word b)
{
    return IsKeyDown(b);
}

bool is_pressed_single(word b)
{
    if (IsKeyPressed(b)) {
        // WHILE_WAIT(IsKeyDown(b));
        return true;
    }
    return false;
}

void release_pressed(word scancode)
{
    currently_pressed[scancode] = false;
}

byte read_scancode()
{
    int key_pressed = GetKeyPressed();
    int index = 0;
    printf("0x%02x\n", key_pressed);
    for (index = 0; index < 80; index++)
    {
        currently_pressed[index] = false;
    }
    currently_pressed[key_pressed] = true;
    return (byte)key_pressed;
}

void free_keyb_buf()
{

}

void reset_keyboard()
{
    log_debug("Unused");
}