#include <ncurses.h>
#include "utils.h"
#include "heading.h"
#include "snake.h"
#include "game.h"
#include "food.h"

#define SNAKE_INIT_LEN 4
#define DEFAULT_SPEED 5

int main()
{
	usint speed = DEFAULT_SPEED;
	init_game();
	game_start_screen();

	usint score = 0;
	display_at_top("SCORE", score);

	Snake *snake_p = New_Snake();
	Snake_Init(snake_p, (LINES/2) + (LINES/2)%2 - 1, (COLS/2) + (COLS/2)%2 - 1, 'r');
	feed_snake(snake_p, SNAKE_INIT_LEN - 1);
	draw_snake(snake_p, -1, -1, false, true);

	int ch = 0;
	usint prev_TailX = -1, prev_TailY = -1;
	Food food;
	spawn_food(&food, snake_p);
	bool ate_food = false;
	while ((ch = getch()) != KEY_ESC)
	{
		if(ch == '[' || ch == ']')
		{
			nodelay(stdscr, false);
			display_at_top("SPEED", speed);
			while ((ch = getch()) != KEY_ESC)
			{
				if(ch == '[' || ch == ']')
				{
					speed += ch - 92;
					if (speed < 1){speed = 1;}
					display_at_top("SPEED", speed);
				}
			}
			nodelay(stdscr, true);
			display_at_top("SCORE", score);
			sleep_ms(500);
			continue;
		}
		ate_food = false;
		prev_TailX = Snake_GetTailX(snake_p);
		prev_TailY = Snake_GetTailY(snake_p);

		const char inp_heading = arrowkey_to_heading(ch);
		const char snake_heading = Snake_GetHeading(snake_p);
		if (inp_heading != '\0' && inp_heading != snake_heading && inp_heading != get_opposite_heading(snake_heading))
		{
			Snake_SetHeading(snake_p, inp_heading);
		}

		tick_snake(snake_p);

		if (inside_bounds(snake_p) && !Snake_SelfCollision(snake_p))
		{
			if (check_ate_food(&food, snake_p))
			{
				ate_food = true;
				Snake_Append(snake_p, prev_TailY, prev_TailX);
				display_at_top("SCORE", ++score);
				spawn_food(&food, snake_p);
			}
			draw_snake(snake_p, prev_TailY, prev_TailX, ate_food, false);
		}
		else
		{
			game_over_screen(score);
			break;
		}
		sleep_ms(1000/speed);
	}

	Delete_Snake(snake_p);
	end_game();

	return 0;
}
