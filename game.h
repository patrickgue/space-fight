#ifndef GAME_H
#define GAME_H

#include <stdbool.h>


typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

struct s_bullet {
  int x;
  int y;
  bool type; /* false = from spaceship, true = from ufo */
  byte direction;
};
typedef struct s_bullet bullet;
#define SPACESHIP_BULLET false;
#define UFO_BULLET true;

#define MAX_BULLETS 256

struct s_ufo {
  int x;
  int y;
  bool direction;
  byte life;
};

typedef struct s_ufo ufo;

static bool debug = false;

void game(byte *, int);


#endif
