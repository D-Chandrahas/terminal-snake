#include <stdlib.h>
#include "snake.h"

struct Node
{
	usint y;
	usint x;
	char heading;
	Node *prev_p;
	Node *next_p;
};

struct Snake
{
	usint len;
	Node *head_p;
	Node *tail_p;
};

Node *Node_Allocate(void)
{
	return (Node *)malloc(sizeof(Node));
}

Node *Node_Construct(Node *node_p, usint y, usint x, char heading, Node *prev_p, Node *next_p)
{
	node_p->y = y;
	node_p->x = x;
	node_p->heading = heading;
	node_p->prev_p = prev_p;
	node_p->next_p = next_p;
	return node_p;
}

Node *New_Node(usint y, usint x, char heading, Node *prev_p, Node *next_p)
{
	return Node_Construct(Node_Allocate(), y, x, heading, prev_p, next_p);
}

usint Node_GetFollowerY(const Node *followedNode_p, char relPos)
{
	if (relPos == 'u')
	{
		return followedNode_p->y - 1;
	}
	else if (relPos == 'd')
	{
		return followedNode_p->y + 1;
	}
	else if (relPos == 'l' || relPos == 'r')
	{
		return followedNode_p->y;
	}
	else
	{
		return 0;
	}
}

usint Node_GetFollowerX(const Node *followedNode_p, char relPos)
{
	if (relPos == 'l')
	{
		return followedNode_p->x - 1;
	}
	else if (relPos == 'r')
	{
		return followedNode_p->x + 1;
	}
	else if (relPos == 'u' || relPos == 'd')
	{
		return followedNode_p->x;
	}
	else
	{
		return 0;
	}
}

char Node_FollowerHeadingToRelPos(const Node *followedNode_p, char heading)
{
	if (heading == 'u')
	{
		return 'd';
	}
	else if (heading == 'd')
	{
		return 'u';
	}
	else if (heading == 'l')
	{
		return 'r';
	}
	else if (heading == 'r')
	{
		return 'l';
	}
	else
	{
		return '\0';
	}
}

Snake *Snake_Allocate(void)
{
	return (Snake *)malloc(sizeof(Snake));
}

Snake *Snake_Construct(Snake *snake_p)
{
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
	return snake_p->len;
}

Node *Snake_GetHeadPtr(const Snake *snake_p)
{
	return snake_p->head_p;
}

Node *Snake_GetTailPtr(const Snake *snake_p)
{
	return snake_p->tail_p;
}

usint Snake_GetTailY(const Snake *snake_p)
{
	return Snake_GetTailPtr(snake_p)->y;
}

usint Snake_GetTailX(const Snake *snake_p)
{
	return Snake_GetTailPtr(snake_p)->x;
}

char Snake_GetTailHeading(const Snake *snake_p)
{
	return Snake_GetTailPtr(snake_p)->heading;
}

usint Snake_GetAppendX(Snake *snake_p)
{
	return Node_GetFollowerX(
		Snake_GetTailPtr(snake_p),
		Node_FollowerHeadingToRelPos(
			Snake_GetTailPtr(snake_p),
			Snake_GetTailHeading(snake_p)));
}

usint Snake_GetAppendY(Snake *snake_p)
{
	return Node_GetFollowerY(
		Snake_GetTailPtr(snake_p),
		Node_FollowerHeadingToRelPos(
			Snake_GetTailPtr(snake_p),
			Snake_GetTailHeading(snake_p)));
}

Snake *Snake_Append(Snake *snake_p)
{
	if (Snake_Length(snake_p) == 0)
	{
		return NULL;
	}

	Node *newNode_p = New_Node(
		Snake_GetAppendY(snake_p),
		Snake_GetAppendX(snake_p),
		Snake_GetTailHeading(snake_p),
		Snake_GetTailPtr(snake_p),
		NULL);
	snake_p->tail_p->next_p = newNode_p;
	snake_p->tail_p = newNode_p;
	(snake_p->len)++;
	return snake_p;
}
