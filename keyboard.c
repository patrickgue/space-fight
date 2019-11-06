#include "keyboard.h"
#include "game.h"
#include <stdbool.h>
#include <bios.h>


bool key_pressed(int code)
{
  if(_bios_keybrd(_KEYBRD_READY)) {
    if ( ((_bios_keybrd (_KEYBRD_READ) >> 8) & 0xff) == code) {
      return true;
    }
    else {
      return false;
    }
  }
}

int current_key_pressed()
{
  if(_bios_keybrd(_KEYBRD_READY)) {
    return ((_bios_keybrd (_KEYBRD_READ) >> 8) & 0xff);
  }
  else {
    return -1;
  }
}

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
