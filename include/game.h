#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "my_types.h"

void init_term(void);

void init_window(void);

void set_game_area_limits(void);

void draw_borders(bool extra_right_border);

void init_game(void);

void game_over_screen(void);

void end_game(void);

char arrowkey_to_heading(const int ch);

void tick_snake(Snake *const snake_p);

void sleep_ms(const int milliseconds);

bool inside_bounds(const Snake *const snake_p);

void draw_snake(const Snake *const snake_p, const usint tail_y, const usint tail_x, bool keep_prev_tail);

void draw_food(const Food *const food_p);

bool is_occupied_by_snake(const Snake *const snake_p, const usint y, const usint x);

bool check_ate_food(const Food *const food_p, const Snake *const snake_p);

void spawn_food(Food *const food_p, const Snake *const snake_p);

#endif