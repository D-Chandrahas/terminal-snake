#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include "my_types.h"

typedef struct Node Node;

Node *Node_Allocate(void);

Node *Node_Construct(
	Node *const node_p,
	const usint y,
	const usint x,
	const Node *const prev_p,
	const Node *const next_p);

Node *New_Node(
	const usint y,
	const usint x,
	const Node *const prev_p,
	const Node *const next_p);

void Node_Deallocate(Node *const node_p);

void Delete_Node(Node *const node_p);

usint Node_GetY(const Node *const node_p);

void Node_SetY(Node *const node_p, const usint y);

usint Node_GetX(const Node *const node_p);

void Node_SetX(Node *const node_p, const usint x);

Node *Node_GetPrevNodePtr(const Node *const node_p);

void Node_SetPrevNodePtr(Node *const node_p, const Node *const prev_p);

Node *Node_GetNextNodePtr(const Node *const node_p);

void Node_SetNextNodePtr(Node *const node_p, const Node *const next_p);

void Node_SimpleMove(Node *const node_p, const char heading, const usint steps);

void Node_AutoSimpleMove(Node *const node_p);

#endif