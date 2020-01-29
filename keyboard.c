#include "keyboard.h"
#include "game.h"
#include <stdbool.h>
#include <bios.h>
#include <mem.h>

#include "log.h"



bool currently_pressed[0x80];

byte read_scancode() {
  byte res;
  _asm {
    in al, 60h
    mov res, al
    in al, 61h
    or al, 128
    out 61h, al
    xor al, 128
    out 61h, al
  }
  return res;
}




void free_keyb_buf() {
    *(char*)(0x0040001A) = 0x20;
    *(char*)(0x0040001C) = 0x20;
}

void init_keyboard()
{
  _fmemset(currently_pressed, false, 0x80);
}

void update_pressed_keys()
{
  int scancode = read_scancode();

  if(scancode > 0x80) {
    currently_pressed[scancode - 0x80] = false;
  }
  else {
    currently_pressed[scancode] = true;
  }

}

bool is_pressed(byte scancode) {
  return currently_pressed[scancode];
}

bool is_pressed_single(byte scancode) {
  if(is_pressed(scancode)) {
    while(is_pressed(scancode))
      update_pressed_keys();
    return true;
  }
  else {
    return false;
  }
}



void release_pressed(byte scancode)
{
  currently_pressed[scancode] = false;
}
