#include <locale.h>
#include <ncurses.h>
#include "game.h"

void init_term(void)
{
	setlocale(LC_ALL, ".UTF-8");
}

void init_window(void)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	clear();
	move(0, 0);
	refresh();
	return;
}

void init_game(void)
{
	init_term();
	init_window();
	return;
}

void game_over_screen(void)
{
	clear();
	mvaddstr(LINES / 2, COLS / 2 - 5, "GAME OVER");
	mvaddstr(LINES / 2 + 1, COLS / 2 - 5, "Press any key to exit");
	refresh();
	getch();
	return;
}

void end_game(void)
{
	clear();
	refresh();
	endwin();
	return;
}

char arrowkey_to_heading(const int ch)
{
	switch (ch)
	{
	case KEY_LEFT:
		return 'l';
	case KEY_RIGHT:
		return 'r';
	case KEY_UP:
		return 'u';
	case KEY_DOWN:
		return 'd';
	default:
		return '\0';
	}
}