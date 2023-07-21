#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_types.h"
#include "node.h"

struct Node
{
	usint y;
	usint x;
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
	const Node *const prev_p,
	const Node *const next_p)
{
	Node_SetY(node_p, y);
	Node_SetX(node_p, x);
	Node_SetPrevNodePtr(node_p, prev_p);
	Node_SetNextNodePtr(node_p, next_p);

	return node_p;
}

Node *New_Node(
	const usint y,
	const usint x,
	const Node *const prev_p,
	const Node *const next_p)
{
	return Node_Construct(Node_Allocate(), y, x, prev_p, next_p);
}

void Node_Deallocate(Node *const node_p)
{
	free(node_p);
	return;
}

void Delete_Node(Node *const node_p)
{
	Node_Deallocate(node_p);
	return;
}

usint Node_GetY(const Node *const node_p)
{
	return node_p ? node_p->y : -1;
}

void Node_SetY(Node *const node_p, const usint y)
{
	if (node_p != NULL)
	{
		node_p->y = y;
	}
	return;
}

usint Node_GetX(const Node *const node_p)
{
	return node_p ? node_p->x : -1;
}

void Node_SetX(Node *const node_p, const usint x)
{
	if (node_p != NULL)
	{
		node_p->x = x;
	}
	return;
}

Node *Node_GetPrevNodePtr(const Node *const node_p)
{
	return node_p ? node_p->prev_p : NULL;
}

void Node_SetPrevNodePtr(Node *const node_p, const Node *const prev_p)
{
	if (node_p != NULL)
	{
		node_p->prev_p = prev_p;
	}
	return;
}

Node *Node_GetNextNodePtr(const Node *const node_p)
{
	return node_p ? node_p->next_p : NULL;
}

void Node_SetNextNodePtr(Node *const node_p, const Node *const next_p)
{
	if (node_p != NULL)
	{
		node_p->next_p = next_p;
	}
	return;
}

void Node_SimpleMove(Node *const node_p, const char heading, const usint steps)
{
	switch (heading)
	{
	case 'u':
		Node_SetY(node_p, Node_GetY(node_p) - steps);
		break;
	case 'd':
		Node_SetY(node_p, Node_GetY(node_p) + steps);
		break;
	case 'l':
		Node_SetX(node_p, Node_GetX(node_p) - 2 * steps);
		break;
	case 'r':
		Node_SetX(node_p, Node_GetX(node_p) + 2 * steps);
		break;
	}
	return;
}