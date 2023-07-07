#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_types.h"
#include "node.h"
#include "snake.h"

struct Snake
{
	usint len;
	Node *head_p;
	Node *tail_p;
};

Snake *Snake_Allocate(void)
{
	return (Snake *)malloc(sizeof(Snake));
}

Snake *Snake_Construct(Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	snake_p->len = 0;
	snake_p->head_p = NULL;
	snake_p->tail_p = NULL;
	return snake_p;
}

Snake *New_Snake(void)
{
	return Snake_Construct(Snake_Allocate());
}

usint Snake_GetLength(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return snake_p->len;
}

Node *Snake_GetHeadPtr(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	return snake_p->head_p;
}

Node *Snake_GetTailPtr(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	return snake_p->tail_p;
}

usint Snake_GetTailY(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetY(Snake_GetTailPtr(snake_p));
}

usint Snake_GetTailX(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetX(Snake_GetTailPtr(snake_p));
}

char Snake_GetTailHeading(const Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return '\0';
	}

	return Node_GetHeading(Snake_GetTailPtr(snake_p));
}

usint Snake_GetAppendX(Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetFollowerX(
		Snake_GetTailPtr(snake_p),
		Node_FollowerHeadingToRelPos(
			Snake_GetTailPtr(snake_p),
			Snake_GetTailHeading(snake_p)));
}

usint Snake_GetAppendY(Snake *snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetFollowerY(
		Snake_GetTailPtr(snake_p),
		Node_FollowerHeadingToRelPos(
			Snake_GetTailPtr(snake_p),
			Snake_GetTailHeading(snake_p)));
}

Snake *Snake_Append(Snake *snake_p)
{
	if (Snake_GetLength(snake_p) == 0)
	{
		return NULL;
	}

	Node *newNode_p = New_Node(
		Snake_GetAppendY(snake_p),
		Snake_GetAppendX(snake_p),
		Snake_GetTailHeading(snake_p),
		Snake_GetTailPtr(snake_p),
		NULL);
	Node_SetNextNodePtr(Snake_GetTailPtr(snake_p), newNode_p);
	snake_p->tail_p = newNode_p;
	(snake_p->len)++;
	return snake_p;
}
