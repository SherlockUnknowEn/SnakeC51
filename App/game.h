#ifndef _game_H
#define _game_H

#include "stdlib.h"

void game_init();
void update_food();
void create_map(unsigned char* map);
void snake_move();
void game_over();
void change_dir(unsigned char d);
unsigned int is_game_over();

#endif

