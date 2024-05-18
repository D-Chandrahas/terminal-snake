#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_types.h"
#include "node.h"
#include "snake.h"

struct Snake
{
	usint len;
	char heading;
	Node *head_p;
	Node *tail_p;
};

Snake *Snake_Allocate(void)
{
	return (Snake *)malloc(sizeof(Snake));
}

Snake *Snake_Construct(Snake *const snake_p)
{
	Snake_SetLength(snake_p, 0);
	Snake_SetHeading(snake_p, '\0');
	Snake_SetHeadPtr(snake_p, NULL);
	Snake_SetTailPtr(snake_p, NULL);

	return snake_p;
}

Snake *New_Snake(void)
{
	return Snake_Construct(Snake_Allocate());
}

void Snake_Destruct(Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return;
	}

	Node *nodeToBeDeleted_p = NULL;
	Node *nodeToBeDeletedNext_p = Snake_GetTailPtr(snake_p);

	for (usint i = Snake_GetLength(snake_p); i > 0; i--)
	{
		nodeToBeDeleted_p = nodeToBeDeletedNext_p;
		nodeToBeDeletedNext_p = Node_GetPrevNodePtr(nodeToBeDeleted_p);
		Delete_Node(nodeToBeDeleted_p);
	}

	Snake_SetLength(snake_p, 0);
	Snake_SetHeading(snake_p, '\0');
	Snake_SetHeadPtr(snake_p, NULL);
	Snake_SetTailPtr(snake_p, NULL);

	return;
}

void Snake_Deallocate(Snake *const snake_p)
{
	free(snake_p);
	return;
}

void Delete_Snake(Snake *const snake_p)
{
	Snake_Destruct(snake_p);
	Snake_Deallocate(snake_p);
	return;
}

usint Snake_GetLength(const Snake *const snake_p)
{
	return snake_p ? snake_p->len : -1;
}

void Snake_SetLength(Snake *const snake_p, const usint len)
{
	if (snake_p != NULL)
	{
		snake_p->len = len;
	}
	return;
}

void Snake_IncrementLength(Snake *const snake_p)
{
	Snake_SetLength(snake_p, Snake_GetLength(snake_p) + 1);
	return;
}

char Snake_GetHeading(const Snake *const snake_p)
{
	return snake_p ? snake_p->heading : '\0';
}

void Snake_SetHeading(Snake *const snake_p, const char heading)
{
	if (snake_p != NULL)
	{
		snake_p->heading = heading;
	}
	return;
}

Node *Snake_GetHeadPtr(const Snake *const snake_p)
{
	return snake_p ? snake_p->head_p : NULL;
}

void Snake_SetHeadPtr(Snake *const snake_p, const Node *const head_p)
{
	if (snake_p != NULL)
	{
		snake_p->head_p = head_p;
	}
	return;
}

Node *Snake_GetTailPtr(const Snake *const snake_p)
{
	return snake_p ? snake_p->tail_p : NULL;
}

void Snake_SetTailPtr(Snake *const snake_p, const Node *const tail_p)
{
	if (snake_p != NULL)
	{
		snake_p->tail_p = tail_p;
	}
	return;
}

usint Snake_GetTailY(const Snake *const snake_p)
{
	return Node_GetY(Snake_GetTailPtr(snake_p));
}

usint Snake_GetTailX(const Snake *const snake_p)
{
	return Node_GetX(Snake_GetTailPtr(snake_p));
}

Snake *Snake_Init(Snake *const snake_p, const usint y, const usint x, const char heading)
{
	Node *newNode_p = New_Node(y, x, NULL, NULL);
	Snake_SetHeading(snake_p, heading);
	Snake_SetHeadPtr(snake_p, newNode_p);
	Snake_SetTailPtr(snake_p, newNode_p);
	Snake_IncrementLength(snake_p);

	return snake_p;
}

Snake *Snake_Append(Snake *const snake_p, const usint y, const usint x)
{
	Node *newNode_p = New_Node(y, x, Snake_GetTailPtr(snake_p), NULL);
	Node_SetNextNodePtr(Snake_GetTailPtr(snake_p), newNode_p);
	Snake_SetTailPtr(snake_p, newNode_p);
	Snake_IncrementLength(snake_p);

	return snake_p;
}

bool Snake_SelfCollision(const Snake *const snake_p)
{
	if (snake_p == NULL)
	{
		return false;
	}

	const Node *const head_p = Snake_GetHeadPtr(snake_p);
	const Node *curr_p = Node_GetNextNodePtr(head_p);
	while (curr_p != NULL)
	{
		if (Node_GetY(head_p) == Node_GetY(curr_p) && Node_GetX(head_p) == Node_GetX(curr_p))
		{
			return true;
		}
		curr_p = Node_GetNextNodePtr(curr_p);
	}

	return false;
}
