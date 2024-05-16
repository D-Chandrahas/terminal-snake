#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "my_types.h"

void init_term(void);

void init_window(void);

void set_game_area_limits(void);

void draw_borders(void);

void init_game(void);

void game_start_screen(void);

void display_at_top(const char *name, const usint value);

void game_over_screen(const usint score);

void end_game(void);

char arrowkey_to_heading(const int ch);

void tick_snake(Snake *const snake_p);

void sleep_ms(const int milliseconds);

bool inside_bounds(const Snake *const snake_p);

usint taxicab_distance(const Snake *const snake_p, const Food *const food_p);

usint euclidean_distance(const Snake *const snake_p, const Food *const food_p);

void draw_snake(const Snake *const snake_p, const char state, const usint prev_tail_y, const usint prev_tail_x, const usint distance, const usint threshold);

void draw_food(const Food *const food_p);

bool is_occupied_by_snake(const Snake *const snake_p, const usint y, const usint x);

bool check_ate_food(const Food *const food_p, const Snake *const snake_p);

void spawn_food(Food *const food_p, const Snake *const snake_p);

void feed_snake(Snake *const snake_p, usint quantity);

#endif