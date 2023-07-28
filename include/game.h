#ifndef GAME_H
#define GAME_H

#include "snake.h"

void init_term(void);

void init_window(void);

void init_game(void);

void game_over_screen(void);

void end_game(void);

char arrowkey_to_heading(const int ch);

void tick_snake(Snake *const snake_p);

void sleep_ms(const int milliseconds);

bool inside_bounds(const Snake *const snake_p);

void render_frame(const Snake *const snake_p);

#endif