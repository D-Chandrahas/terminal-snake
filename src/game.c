#include <locale.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "game.h"

usint GAME_X_MIN, GAME_X_MAX, GAME_Y_MIN, GAME_Y_MAX;

void init_term(void)
{
	// setlocale(LC_ALL, ".UTF-8");
	setlocale(LC_ALL, "");
	// refresh();
	// curs_set(0);
	// refresh();
	return;
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

void set_game_area_limits(void)
{
	GAME_X_MIN = 1;
	GAME_Y_MIN = 1;
	GAME_X_MAX = COLS - 3 - (COLS % 2);
	GAME_Y_MAX = LINES - 2;
	return;
}

void draw_borders(bool extra_right_border)
{
	move(0, 0);
	for (int i = 0; i < COLS; i++)
	{
		addch('-');
	}

	move(LINES - 1, 0);
	for (int i = 0; i < COLS; i++)
	{
		addch('-');
	}
	
	for (int i = 0; i < LINES; i++)
	{
		mvaddch(i, 0, '|');
	}

	for (int i = 0; i < LINES; i++)
	{
		mvaddch(i, COLS - 1, '|');
	}

	if(extra_right_border)
	{
		for (int i = 0; i < LINES; i++)
		{
			mvaddch(i, COLS - 2, '|');
		}
	}

	refresh();
	return;
}

void init_game(void)
{
	init_term();
	init_window();
	set_game_area_limits();
	draw_borders(COLS % 2);
	srand(time(NULL));
	return;
}

void game_over_screen(void)
{
	clear();
	mvaddstr(LINES / 2 - 1 , COLS / 2 - 5, "GAME OVER");
	mvaddstr(LINES / 2, COLS / 2 - 10, "Press any key to exit");
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
	return (head_x >= GAME_X_MIN && head_x <= GAME_X_MAX && head_y >= GAME_Y_MIN && head_y <= GAME_Y_MAX);
}

void draw_snake(const Snake *const snake_p, const usint tail_y, const usint tail_x, bool keep_prev_tail)
{
	if (snake_p == NULL)
	{
		return;
	}

	// clear();
	// for(Node *curr_p = Snake_GetHeadPtr(snake_p); curr_p != NULL; curr_p = Node_GetNextNodePtr(curr_p))
	// {
	// 	mvaddwstr(Node_GetY(curr_p), Node_GetX(curr_p), L"\u2588\u2588");
	// }

	if(!keep_prev_tail)
	{
		mvaddstr(tail_y, tail_x, "  ");
	}
	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	mvaddwstr(Node_GetY(head_p), Node_GetX(head_p), L"██");//L"\u2588\u2588");

	move(0, 0);
	refresh();
	return;
}

void draw_food(const Food *const food_p)
{
	if (food_p == NULL)
	{
		return;
	}
// todo: add color and diff. char
	mvaddwstr(Food_GetY(food_p), Food_GetX(food_p), L"🍕");
	move(0, 0);
	refresh();
	return;
}

bool is_occupied_by_snake(const Snake *const snake_p, const usint y, const usint x)
{
	if (snake_p == NULL)
	{
		return false;
	}

	for (const Node *curr_p = Snake_GetHeadPtr(snake_p); curr_p != NULL; curr_p = Node_GetNextNodePtr(curr_p))
	{
		if (Node_GetY(curr_p) == y && Node_GetX(curr_p) == x)
		{
			return true;
		}
	}

	return false;
}

bool check_ate_food(const Food *const food_p, const Snake *const snake_p)
{
	if (food_p == NULL || snake_p == NULL)
	{
		return false;
	}

	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	return (Node_GetX(head_p) == Food_GetX(food_p)) && (Node_GetY(head_p) == Food_GetY(food_p));
}

void spawn_food(Food *const food_p, const Snake *const snake_p)
{
	if (food_p == NULL || snake_p == NULL)
	{
		return;
	}

	usint x = 0, y = 0;
	
	do
	{
		y = GAME_Y_MIN + (rand() % ((GAME_Y_MAX - GAME_Y_MIN)/2 + 1)) * 2;
		x = GAME_X_MIN + (rand() % ((GAME_X_MAX - GAME_X_MIN)/2 + 1)) * 2;
	}
	while(is_occupied_by_snake(snake_p, y, x));

	Food_SetY(food_p, y);
	Food_SetX(food_p, x);

	draw_food(food_p);
	return;
}