#include <locale.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "snake.h"
#include "game.h"
#include "utils.h"

#define FOOD L"🍰" //L"\ud83c\udf70"
#define SNAKE_FACE L"👀" //L"\ud83d\udc40"
#define SNAKE_BODY L"██" //L"\u2588\u2588"
#define SNAKE_OPEN_MOUTH L"👄" //L"\ud83d\udc44"
#define SNAKE_HAPPY L"😋" //L"\ud83d\ude0b"
#define SNAKE_DEAD L"☠️" //L"\u2620\ufe0f"

#define HAPPY_TIME 3

usint GAME_X_MIN, GAME_X_MAX, GAME_Y_MIN, GAME_Y_MAX;
usint GAME_LEFT_BORDER, GAME_RIGHT_BORDER, GAME_TOP_BORDER, GAME_BOTTOM_BORDER;

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

	GAME_LEFT_BORDER = GAME_X_MIN - 1;
	GAME_RIGHT_BORDER = GAME_X_MAX + 2;
	GAME_TOP_BORDER = GAME_Y_MIN - 1;
	GAME_BOTTOM_BORDER = GAME_Y_MAX + 1;
	return;
}

void draw_borders(void)
{
	move(0, 0);
	for (usint i = 0; i <= GAME_RIGHT_BORDER; i++)
	{
		addch('-');
	}

	move(LINES - 1, 0);
	for (usint i = 0; i <= GAME_RIGHT_BORDER; i++)
	{
		addch('-');
	}
	
	for (usint i = 0; i < LINES; i++)
	{
		mvaddch(i, 0, '|');
	}

	for (usint i = 0; i < LINES; i++)
	{
		mvaddch(i, GAME_RIGHT_BORDER, '|');
	}

	refresh();
	return;
}

void init_game(void)
{
	init_term();
	init_window();
	set_game_area_limits();
	draw_borders();
	display_at_top("SCORE", 0);
	srand(time(NULL));
	return;
}

void game_start_screen(void)
{
	mvaddstr(LINES / 2 - 3, COLS / 2 - 10, "Use Arrows or WASD to turn");
	mvaddstr(LINES / 2 - 1, COLS / 2 - 20, "Press '[' or ']' to increase/decrease speed");
	mvaddstr(LINES / 2, COLS / 2 - 10, "and enter to confirm");
	mvaddstr(LINES / 2 + 2, COLS / 2 - 20, "Current score/speed at the top left corner");
	mvaddstr(LINES / 2 + 3, COLS / 2 - 10, "Press any key to start...");
	refresh();
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
	mvaddstr(LINES / 2 - 3, COLS / 2 - 10, "                          ");
	mvaddstr(LINES / 2 - 1, COLS / 2 - 20, "                                           ");
	mvaddstr(LINES / 2, COLS / 2 - 10, "                    ");
	mvaddstr(LINES / 2 + 2, COLS / 2 - 20, "                                          ");
	mvaddstr(LINES / 2 + 3, COLS / 2 - 10, "                         ");
	move(0, 0);
	refresh();
	return;
}

void display_at_top(const char *name, const usint value)
{
	attron(A_REVERSE);
	mvprintw(0, 0, "%s %hu", name, value);
	attroff(A_REVERSE);
	for(int x = getcurx(stdscr); x <= GAME_RIGHT_BORDER; ++x)
	{
		addch('-');
	}
	mvaddch(0, GAME_RIGHT_BORDER, '|');
	move(0, 0);
	refresh();
	return;
}

void game_over_screen(const usint score)
{
	// clear();
	mvaddstr(LINES / 2 - 1 , COLS / 2 - 5, "GAME OVER");
	mvprintw(LINES / 2, COLS / 2 - 7, "Your score: %hu", score);
	mvaddstr(LINES / 2 + 1, COLS / 2 - 10, "Press ESC key to exit");
	refresh();
	nodelay(stdscr, FALSE);
	while (getch() != KEY_ESC){}
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
	case KEY_LEFT: case 'a':
		return 'l';
	case KEY_RIGHT: case 'd':
		return 'r';
	case KEY_UP: case 'w':
		return 'u';
	case KEY_DOWN: case 's':
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
	const usint head_x = Node_GetX(head_p);
	const usint head_y = Node_GetY(head_p);
	return (head_x >= GAME_X_MIN && head_x <= GAME_X_MAX && head_y >= GAME_Y_MIN && head_y <= GAME_Y_MAX);
}

usint taxicab_distance(const Snake *const snake_p, const Food *const food_p)
{
	if (snake_p == NULL || food_p == NULL)
	{
		return -1;
	}

	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	return abs((int)Node_GetX(head_p) - Food_GetX(food_p))/2 + abs((int)Node_GetY(head_p) - Food_GetY(food_p));
}

usint euclidean_distance(const Snake *const snake_p, const Food *const food_p)
{
	if (snake_p == NULL || food_p == NULL)
	{
		return -1;
	}

	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	return sqrt(pow(((int)Node_GetX(head_p) - Food_GetX(food_p))/2, 2) + pow((int)Node_GetY(head_p) - Food_GetY(food_p), 2));
}


void draw_snake(const Snake *const snake_p, const char state, const usint prev_tail_y, const usint prev_tail_x, const usint distance, const usint threshold)
{
	static char happy_timer = 0;
	if (snake_p == NULL)
	{
		return;
	}

	if(state == 'i')
	{
		const Node *const head_p = Snake_GetHeadPtr(snake_p);
		mvaddwstr(Node_GetY(head_p), Node_GetX(head_p), SNAKE_FACE);
		for(const Node *curr_p = Node_GetNextNodePtr(head_p); curr_p != NULL; curr_p = Node_GetNextNodePtr(curr_p))
		{
			mvaddwstr(Node_GetY(curr_p), Node_GetX(curr_p), SNAKE_BODY);
		}

	}
	else
	{
		const Node *const head_p = Snake_GetHeadPtr(snake_p);
		Node *const prev_head_p = Node_GetNextNodePtr(head_p);
		if (state == 'd')
		{
			mvaddwstr(Node_GetY(prev_head_p), Node_GetX(prev_head_p), SNAKE_DEAD);
		}
		else
		{
			mvaddwstr(Node_GetY(prev_head_p), Node_GetX(prev_head_p), SNAKE_BODY);
			if(distance == 0)
			{
				mvaddwstr(Node_GetY(head_p), Node_GetX(head_p), SNAKE_HAPPY);
				happy_timer = HAPPY_TIME;
			}
			else
			{
				mvaddstr(prev_tail_y, prev_tail_x, "  ");
				if(happy_timer > 0)
				{
					mvaddwstr(Node_GetY(head_p), Node_GetX(head_p), SNAKE_HAPPY);
					--happy_timer;
				}
				else
				{
					mvaddwstr(Node_GetY(head_p), Node_GetX(head_p), distance <= threshold ? SNAKE_OPEN_MOUTH : SNAKE_FACE);
				}
			}
		}
	}
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

	mvaddwstr(Food_GetY(food_p), Food_GetX(food_p), FOOD);
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
	
	usint y = GAME_Y_MIN + (rand() % ((GAME_Y_MAX - GAME_Y_MIN)/2 + 1)) * 2;
	usint x = GAME_X_MIN + (rand() % ((GAME_X_MAX - GAME_X_MIN)/2 + 1)) * 2;
	
	while(is_occupied_by_snake(snake_p, y, x))
	{
		if( (x+=2) > GAME_X_MAX)
		{
			x = GAME_X_MIN;
			if(++y > GAME_Y_MAX)
			{
				y = GAME_Y_MIN;
			}
		}
	}

	Food_SetY(food_p, y);
	Food_SetX(food_p, x);

	draw_food(food_p);
	return;
}

void feed_snake(Snake *const snake_p, usint quantity)
{
	if (snake_p == NULL || quantity < 1)
	{
		return;
	}

	for ( ; quantity > 0; quantity--)
	{
		Snake_Append(snake_p, Snake_GetTailY(snake_p), Snake_GetTailX(snake_p) - 2);
	}

	return;
}