#include "heading.h"

char get_opposite_heading(const char heading)
{
	switch (heading)
	{
	case 'u':
		return 'd';
	case 'd':
		return 'u';
	case 'l':
		return 'r';
	case 'r':
		return 'l';
	default:
		return '\0';
	}
}