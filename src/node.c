#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_types.h"
#include "heading.h"
#include "node.h"

struct Node
{
	usint y;
	usint x;
	char heading;
	Node *prev_p;
	Node *next_p;
};

Node *Node_Allocate(void)
{
	return (Node *)malloc(sizeof(Node));
}

Node *Node_Construct(
	Node *const node_p,
	const usint y,
	const usint x,
	const char heading,
	const Node *const prev_p,
	const Node *const next_p)
{
	if (node_p == NULL)
	{
		return NULL;
	}

	Node_SetY(node_p, y);
	Node_SetX(node_p, x);
	Node_SetHeading(node_p, heading);
	Node_SetPrevNodePtr(node_p, prev_p);
	Node_SetNextNodePtr(node_p, next_p);
	return node_p;
}

Node *New_Node(
	const usint y,
	const usint x,
	const char heading,
	const Node *const prev_p,
	const Node *const next_p)
{
	return Node_Construct(Node_Allocate(), y, x, heading, prev_p, next_p);
}

bool Node_Destruct(Node *const node_p)
{
	if (node_p == NULL)
	{
		return false;
	}

	Node_SetY(node_p, -1);
	Node_SetX(node_p, -1);
	Node_SetHeading(node_p, '\0');
	Node_SetPrevNodePtr(node_p, NULL);
	Node_SetNextNodePtr(node_p, NULL);

	return true;
}

bool Node_Deallocate(Node **const node_pp)
{
	if (node_pp == NULL)
	{
		return false;
	}

	free(*node_pp);
	*node_pp = NULL;

	return true;
}

bool Delete_Node(Node **const node_pp)
{
	if (node_pp == NULL)
	{
		return false;
	}

	if (!Node_Destruct(*node_pp))
	{
		return false;
	}
	if (!Node_Deallocate(node_pp))
	{
		return false;
	}

	return true;
}

usint Node_GetY(const Node *const node_p)
{
	if (node_p == NULL)
	{
		return -1;
	}

	return node_p->y;
}

bool Node_SetY(Node *const node_p, const usint y)
{
	if (node_p == NULL)
	{
		return false;
	}

	node_p->y = y;
	return true;
}

usint Node_GetX(const Node *const node_p)
{
	if (node_p == NULL)
	{
		return -1;
	}

	return node_p->x;
}

bool Node_SetX(Node *const node_p, const usint x)
{
	if (node_p == NULL)
	{
		return false;
	}

	node_p->x = x;
	return true;
}

char Node_GetHeading(const Node *const node_p)
{
	if (node_p == NULL)
	{
		return '\0';
	}

	return node_p->heading;
}

bool Node_SetHeading(Node *const node_p, const char heading)
{
	if (node_p == NULL)
	{
		return false;
	}

	node_p->heading = heading;
	return true;
}

Node *Node_GetPrevNodePtr(const Node *const node_p)
{
	if (node_p == NULL)
	{
		return NULL;
	}

	return node_p->prev_p;
}

bool Node_SetPrevNodePtr(Node *const node_p, const Node *const prev_p)
{
	if (node_p == NULL)
	{
		return false;
	}

	node_p->prev_p = prev_p;
	return true;
}

Node *Node_GetNextNodePtr(const Node *const node_p)
{
	if (node_p == NULL)
	{
		return NULL;
	}

	return node_p->next_p;
}

bool Node_SetNextNodePtr(Node *const node_p, const Node *const next_p)
{
	if (node_p == NULL)
	{
		return false;
	}

	node_p->next_p = next_p;
	return true;
}

usint Node_GetFollowerY(const Node *const followedNode_p, const char relPos)
{
	if (followedNode_p == NULL)
	{
		return -1;
	}

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
		return -1;
	}
}

usint Node_GetFollowerX(const Node *const followedNode_p, const char relPos)
{
	if (followedNode_p == NULL)
	{
		return -1;
	}

	if (relPos == 'l')
	{
		return followedNode_p->x - 2;
	}
	else if (relPos == 'r')
	{
		return followedNode_p->x + 2;
	}
	else if (relPos == 'u' || relPos == 'd')
	{
		return followedNode_p->x;
	}
	else
	{
		return -1;
	}
}

char Node_FollowerHeadingToRelPos(const char heading)
{
	return get_opposite_heading(heading);
}