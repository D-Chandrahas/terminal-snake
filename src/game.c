#include <locale.h>
#include <ncurses.h>
#include "snake.h"
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
	nodelay(stdscr, TRUE);
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
	nodelay(stdscr, FALSE);
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

void tick_snake(Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return;
	}

	Node *curr_p = Snake_GetTailPtr(snake_p);
	Node *prev_p = Node_GetPrevNodePtr(curr_p);
	Node *head_p = Snake_GetHeadPtr(snake_p);
	while (curr_p != head_p)
	{
		Node_SetX(curr_p, Node_GetX(prev_p));
		Node_SetY(curr_p, Node_GetY(prev_p));
		curr_p = prev_p;
		prev_p = Node_GetPrevNodePtr(curr_p);
	}

	Node_SimpleMove(head_p, Snake_GetHeading(snake_p), 1);
}

#ifdef _WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

// Credit: https://stackoverflow.com/a/28827188
// cross-platform sleep function
void sleep_ms(const int milliseconds)
{
#ifdef _WIN32
	Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
#else
	if (milliseconds >= 1000)
		sleep(milliseconds / 1000);
	usleep((milliseconds % 1000) * 1000);
#endif
}

bool inside_bounds(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return false;
	}

	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	const int head_x = Node_GetX(head_p);
	const int head_y = Node_GetY(head_p);
	return (head_x >= 0 && head_x < COLS && head_y >= 0 && head_y < LINES);
}

void render_frame(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return;
	}

	clear();
	for(Node *curr_p = Snake_GetHeadPtr(snake_p); curr_p != NULL; curr_p = Node_GetNextNodePtr(curr_p))
	{
		mvaddstr(Node_GetY(curr_p), Node_GetX(curr_p), "██");
	}
	refresh();
	return;
}