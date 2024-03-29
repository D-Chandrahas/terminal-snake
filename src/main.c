#include <ncurses.h>
#include "utils.h"
#include "heading.h"
#include "snake.h"
#include "game.h"

int main()
{
	init_game();

	Snake *snake_p = New_Snake();
	Snake_Init(snake_p, LINES / 2, COLS / 2, 'r');

	int ch = 0;
	usint prev_TailX = -1, prev_TailY = -1;
	bool ate_food = false;
	while ((ch = getch()) != KEY_ESC)
	{
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
			// if ate food snake append prev tail
			if (ch == 'f')
			{
				ate_food = true;
				Snake_Append(snake_p, prev_TailY, prev_TailX);
				// new food
			}
			draw_snake(snake_p, prev_TailY, prev_TailX, ate_food);
		}
		else
		{
			game_over_screen();
			break;
		}
		sleep_ms(250);
	}

	end_game();

	return 0;
}
