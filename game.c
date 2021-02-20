#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#ifdef __DOS__
#include <dos.h>
#else
#include <raylib.h>
#endif
//TODO: handle sound

#include "game.h"
#include "keyboard.h"
#include "menu.h"
#include "sprite.h"
#include "sprites.h"
#include "vga.h"
#include "text.h"

int map_coordinate(int x_orig, int x_offset, int y_orig, int map_size)
{
    int map_y = (y_orig - 0x12)/0xc; /* y / tile height */
    int map_x = ((x_orig - x_offset) - (map_y * 0x6)) / 0x14; /* (x + perspective_offset) / tile height */
    return map_x + (map_size * map_y);
}

void draw_map(byte *map, int map_size, int x)
{
    int map_x, map_y;
    for(map_x = map_size-1; map_x >= 0; map_x--)
    {
        if(x + (map_x * 0x14) + (0x6 * 0xb) + 32 > 0 && x + (map_x * 0x14) < SCREEN_WIDTH + 32)
        {
            for(map_y = 0; map_y < 11; map_y++)
            {
                int map_x_pos = x+(map_x * 0x14) + (map_y * 0x6);
                byte tile = map[map_x + (map_size * map_y)];

                if(tile == 1)
                {
                    render_sprite(map_x_pos, map_y * 0xc+18,32,32, cube);
                }
                else if (tile == 2)
                {
                    render_sprite(map_x_pos, map_y * 0xc+18+16, 32, 16, turret);
                }
                else if (tile == 3)
                {
                    render_sprite(map_x_pos, map_y * 0xc+18+16, 32, 16, base);
                }
            }
        }
    }
}

int remove_bullet(bullet bullets[MAX_BULLETS], int index, int total)
{
    bullets[index] = bullets[--total];
    return total;
}

void draw_spacecraft(int spacecraft_speed, int y, int spacecraft_r)
{
    if(spacecraft_speed == 0)
        render_sprite_rotate(0x40,y,16,16,spaceship1, spacecraft_r);
    else if(spacecraft_speed < 10)
        render_sprite_rotate(0x40,y,16,16,spaceship2, spacecraft_r);
    else
        render_sprite_rotate(0x40,y,16,16,spaceship3, spacecraft_r);


}

void game(byte *map, int map_size)
{
    bool pause = false;
    bool loop = true;

    char pause_menu[2][32] =
            {
                    "Continue",
                    "Exit",
            };
    int menu_selection = 0;
    int x = 0,y = 0x20, i, spacecraft = 0,spacecraft_r = 0;
    int fps = 0, fpsd = 0;
    time_t timestamp;
    char fpst[40];

    ufo *ufos = malloc(0);
    int ufos_size = 0;
    ufo new_ufo;

    bullet *bullets = (bullet*) malloc(sizeof(bullet) * MAX_BULLETS);
    int bullets_index = 0;
    bullet new_bullet;
    int coordinate;

    for(i = 0; i < map_size * SCREEN_HEIGHT; i++) {
        if(map[i] == 9) {
            ufos = (ufo*) realloc(ufos, (ufos_size + 1) * sizeof(ufo));
            new_ufo.y = i / map_size;
            new_ufo.x = i - (SCREEN_HEIGHT * new_ufo.y);
            new_ufo.direction = 0;
            new_ufo.life = 3;

            ufos[ufos_size++] = new_ufo;
        }
    }

    time(&timestamp);

    WHILE_WAIT(loop) {
        clear_buffer(0x9);


        rect_fill(0,10,SCREEN_WIDTH,8,55);
        rect_fill(0,18,SCREEN_WIDTH,16,53);
        draw_map(map, map_size, x);

        for(i = 0; i < ufos_size; i++) {
            if(ufos[i].direction == 0) {
                ufos[i].y++;
                if(ufos[i].y > SCREEN_HEIGHT - 0x22)
                    ufos[i].direction = 1;
            }
            else {
                ufos[i].y--;
                if(ufos[i].y <= 0x12)
                    ufos[i].direction = 0;
            }

            render_sprite(ufos[i].x + x, ufos[i].y, 16, 16, ufo_sprite);
        }

        draw_spacecraft(spacecraft, y, spacecraft_r);




        rect_fill(0,SCREEN_HEIGHT - 24,SCREEN_WIDTH,8,55);
        rect_fill(0,SCREEN_HEIGHT - 16,SCREEN_WIDTH,16,53);

        if(debug) {
            sprintf(fpst, "FPS: %d | %02x %02x | %d | %d", fpsd, x,y, pause, bullets_index);
            print_narrow(4,SCREEN_HEIGHT - 12,fpst,0xF);
        }

        if(!pause) {

            if(spacecraft > 0)
                spacecraft--;


            x-=2;
            if(x < -1 * (map_size * 20 + SCREEN_WIDTH + 100))
                x = 320;
            fps++;

            for(i = 0; i < bullets_index; i++) {
                switch(bullets[i].direction) {
                    case 0:
                        bullets[i].x += 2;
                        break;
                    case 1:
                        bullets[i].y += 4;
                        break;
                    case 4:
                        bullets[i].x -= 2;
                        break;
                    case 3:
                        bullets[i].y -= 4;
                        break;
                }

                coordinate = map_coordinate(bullets[i].x, x, bullets[i].y - 16, map_size);

                if(bullets[i].x > 320 || bullets[i].x < 0 ||
                   bullets[i].y > 200 || bullets[i].y < 0) {
                    bullets_index = remove_bullet(bullets, i, bullets_index);
                }
                else if(map[coordinate] >  0) {
                    bullets_index = remove_bullet(bullets, i, bullets_index);
                    if(map[coordinate] == 2) {
                        map[coordinate] = 0;
#ifdef __DOS__
                        sound(200);
			delay(100);
			nosound();
#endif
                    }
                }
                    //else if(bullets[i].x
                else {
                    putpixel(bullets[i].x, bullets[i].y, 66);
                }
            }




            if(time(NULL) > timestamp) {
                fpsd = fps;
                fps = 0;
                time(&timestamp);
            }


            spacecraft_r = 0;
            if(is_pressed(KEY_LEFT)) {
                x+=1;
                spacecraft_r = 4;
                release_pressed(KEY_RIGHT);
            }

            if(is_pressed(KEY_RIGHT)) {
                x-=1;
                spacecraft_r = 0;
                release_pressed(KEY_LEFT);
            }

            if(is_pressed(KEY_UP)) {
                if(y > 0x1a)
                    y-=3;
                spacecraft_r = 3;
                release_pressed(KEY_DOWN);
            }

            if(is_pressed(KEY_DOWN)) {
                if(y < 0xa9)
                    y+=3;
                spacecraft_r = 1;
                release_pressed(KEY_UP);
            }

            if(is_pressed(KEY_ESCAPE)) {
                pause = true;
            }

            if(is_pressed(KEY_SPACE)) {
                if(spacecraft_r == 0) {
                    new_bullet.x = 0x4a;
                    new_bullet.y = y+6;
                }
                else if(spacecraft_r == 1) {
                    new_bullet.x = 0x48;
                    new_bullet.y = y+0xa;
                }
                else if(spacecraft_r == 4) {
                    new_bullet.x = 0x40;
                    new_bullet.y = y+6;
                }
                else if(spacecraft_r == 3) {
                    new_bullet.x = 0x48;
                    new_bullet.y = y;
                }

                new_bullet.direction = spacecraft_r;
                new_bullet.type = SPACESHIP_BULLET;
                if(bullets_index >= MAX_BULLETS -1) {
                    bullets_index = remove_bullet(bullets, 0, bullets_index);
                }
                bullets[bullets_index++] = new_bullet;
#ifdef __DOS__
                sound(200);
			delay(100);
			nosound();
#endif
            }

            if(is_pressed(KEY_LEFT) || is_pressed(KEY_RIGHT)
               || is_pressed(KEY_UP) || is_pressed(KEY_DOWN)) {
                spacecraft = 20;
            }
        }
        else {
            if(menu_selection > 0 && is_pressed_single(KEY_UP)) {
                menu_selection--;
            }

            if(menu_selection < 1 && is_pressed_single(KEY_DOWN)) {
                menu_selection++;
            }

            if(is_pressed(ACTION_KEY)) {
                if(menu_selection == 0) {
                    pause = false;
                }
                else if(menu_selection == 1) {
                    loop = false;
#ifdef __DOS__      // we need to wait until key is released
                    while(is_pressed(ACTION_KEY));
#endif

                }
            }
            show_menu(0x20, 0x20, 0x100, 0x88, pause_menu, 2, menu_selection, "PAUSED");
        }
        show_buffer();
    }
}
