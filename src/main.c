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
	while ((ch = getch()) != KEY_ESC)
	{
		const char inp_heading = arrowkey_to_heading(ch);
		if (inp_heading == '\0')
		{
		}
		else if (({
			const char snake_heading = Snake_GetHeading(snake_p);
			inp_heading == snake_heading || inp_heading == get_opposite_heading(snake_heading); }))
		{
		}
		else
		{
			Snake_SetHeading(snake_p, inp_heading);
		}

		tick_snake(snake_p);
		if (inside_bounds(snake_p))
		{
			render_frame(snake_p);
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
