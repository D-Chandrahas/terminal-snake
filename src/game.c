#include <locale.h>
#include <ncurses.h>

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