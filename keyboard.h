#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include "game.h"

#ifdef __DOS__
#define KEY_ESCAPE 0x01
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x0x09
#define KEY_9 0x0A
#define KEY_0 0x0B
#define KEY_DASH 0x0C
#define KEY_EQU 0x0D
#define KEY_LEFT 0x4B
#define KEY_TAB 0x0F
#define KEY_Q 0x10
#define KEY_W 0x11
#define KEY_E 0x12
#define KEY_R 0x13
#define KEY_T 0x14
#define KEY_Y 0x15
#define KEY_U 0x16
#define KEY_I 0x17
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_BRSL 0x1A
#define KEY_BRSR 0x1B
#define KEY_ENTER 0x1C
#define KEY_CTRL 0x1D
#define KEY_A 0x1E
#define KEY_S 0x1F
#define KEY_D 0x20
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_SEMI 0x27
#define KEY_APO 0x28
#define KEY_APOA 29
#define KEY_LEFT_SHIFT 0x2A
#define KEY_BACKSLASH 0x2B
#define KEY_Z 0x2C
#define KEY_X 0x2D
#define KEY_C 0x2E
#define KEY_V 0x2F
#define KEY_B 0x30
#define KEY_N 0x31
#define KEY_M 0x32
#define KEY_COMMA 0x33
#define KEY_PEROID 0x34
#define KEY_SLASH 0x35
#define KEY_RIGHT_SHIFT 0x36
#define KEY_PRTSC 0x37
#define KEY_ALT 0x38
#define KEY_SPACE 0x39
#define KEY_CAPSLOCK 0x3A
#define KEY_F1 0x3B
#define KEY_F2 0x3C
#define KEY_F3 0x3D
#define KEY_F4 0x3E
#define KEY_F5 0x3F
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_NUMLOCK 0x45
#define KEY_SCROLL LOCK 0x46
#define KEY_HOME 0x47
#define KEY_UP 0x48
#define KEY_PGUP 0x49
#define KEY_DASHN 0x4A
#define KEY_N_LEFT 0x4B
#define KEY_N_5 0x4C
#define KEY_RIGHT 0x4D
#define KEY_PLUS 0x4E
#define KEY_END 0x4F
#define KEY_DOWN 0x50
#define KEY_PGDD 0x51
#define KEY_INS 0x52
#define KEY_DEL 0x53
#define KEY_F11 0x85
#define KEY_F12 0x58
#endif
 

void init_keyboard();
#ifdef __DOS__
static void interrupt update_pressed_keys(void);
#else
void update_pressed_keys(void);
#endif
bool is_pressed(word);
bool is_pressed_single(word);
void release_pressed(word scancode);
byte read_scancode();
void free_keyb_buf();
void reset_keyboard();

#endif
