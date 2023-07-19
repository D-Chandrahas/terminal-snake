#ifndef GAME_H
#define GAME_H

void init_term(void);

void init_window(void);

void init_game(void);

void game_over_screen(void);

void end_game(void);

char arrowkey_to_heading(const int ch);

#endif