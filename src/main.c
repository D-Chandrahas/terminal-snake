#include <ncurses.h>
#include "utils.h"
#include "snake.h"
#include "game.h"

int main()
{
	init_game();
	nodelay(stdscr, TRUE);

	Snake *snake_p = New_Snake();
	Snake_Init(snake_p, LINES / 2, COLS / 2, 'r');
	for (int i = 1; i <= 7; i++)
	{
		Snake_Append(snake_p);
	}

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

		if (inside_bounds(snake_p))
		{
			tick_snake(snake_p);
			render_frame(snake_p);
		}
		else
		{
			game_over_screen();
			break;
		}
	}
	end_game();
	return 0;
}