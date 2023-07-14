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

Snake *Snake_Construct(Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	Snake_SetLength(snake_p, 0);
	Snake_SetHeadPtr(snake_p, NULL);
	Snake_SetTailPtr(snake_p, NULL);
	return snake_p;
}

Snake *New_Snake(void)
{
	return Snake_Construct(Snake_Allocate());
}

bool Snake_Destruct(Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return false;
	}

	Node *nodeToBeDeleted_p = NULL;
	Node *nodeToBeDeletedNext_p = Snake_GetTailPtr(snake_p);

	for (usint i = Snake_GetLength(snake_p); i > 0; i--)
	{
		nodeToBeDeleted_p = nodeToBeDeletedNext_p;
		nodeToBeDeletedNext_p = Node_GetPrevNodePtr(nodeToBeDeleted_p);
		Delete_Node(&nodeToBeDeleted_p);
	}

	Snake_SetLength(snake_p, 0);
	Snake_SetHeadPtr(snake_p, NULL);
	Snake_SetTailPtr(snake_p, NULL);

	return true;
}

bool Snake_Deallocate(Snake **const snake_pp)
{
	if (snake_pp == NULL)
	{
		return false;
	}

	free(*snake_pp);
	*snake_pp = NULL;

	return true;
}

bool Delete_Snake(Snake **const snake_pp)
{
	if (snake_pp == NULL)
	{
		return false;
	}

	if (!Snake_Destruct(*snake_pp))
	{
		return false;
	}
	if (!Snake_Deallocate(snake_pp))
	{
		return false;
	}

	return true;
}

usint Snake_GetLength(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return 0;
	}

	return snake_p->len;
}

bool Snake_SetLength(Snake *const snake_p, const usint len)
{
	if (snake_p == NULL)
	{
		return false;
	}

	snake_p->len = len;
	return true;
}

bool Snake_IncrementLength(Snake *const snake_p)
{
	return Snake_SetLength(snake_p, Snake_GetLength(snake_p) + 1);
}

Node *Snake_GetHeadPtr(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	return snake_p->head_p;
}

bool Snake_SetHeadPtr(Snake *const snake_p,const Node *const head_p)
{
	if (snake_p == NULL)
	{
		return false;
	}

	snake_p->head_p = head_p;
	return true;
}

Node *Snake_GetTailPtr(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return NULL;
	}

	return snake_p->tail_p;
}

bool Snake_SetTailPtr(Snake *const snake_p,const Node *const tail_p)
{
	if (snake_p == NULL)
	{
		return false;
	}

	snake_p->tail_p = tail_p;
	return true;
}

usint Snake_GetTailY(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetY(Snake_GetTailPtr(snake_p));
}

usint Snake_GetTailX(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return -1;
	}

	return Node_GetX(Snake_GetTailPtr(snake_p));
}

char Snake_GetTailHeading(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return '\0';
	}

	return Node_GetHeading(Snake_GetTailPtr(snake_p));
}

usint Snake_GetAppendX(const Snake *const snake_p)
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

usint Snake_GetAppendY(const Snake *const snake_p)
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

bool Snake_Init(Snake *const snake_p, const usint y, const usint x, const char heading)
{
	if (snake_p == NULL)
	{
		return false;
	}

	Node *newNode_p = New_Node(y, x, heading, NULL, NULL);
	Snake_SetHeadPtr(snake_p, newNode_p);
	Snake_SetTailPtr(snake_p, newNode_p);
	Snake_IncrementLength(snake_p);
	return true;
}

bool Snake_Append(Snake *const snake_p)
{
	if(snake_p == NULL)
	{
		return false;
	}

	if (Snake_GetLength(snake_p) == 0)
	{
		return false;
	}

	Node *newNode_p = New_Node(
		Snake_GetAppendY(snake_p),
		Snake_GetAppendX(snake_p),
		Snake_GetTailHeading(snake_p),
		Snake_GetTailPtr(snake_p),
		NULL);
	Node_SetNextNodePtr(Snake_GetTailPtr(snake_p), newNode_p);
	Snake_SetTailPtr(snake_p, newNode_p);
	Snake_IncrementLength(snake_p);
	return true;
}
