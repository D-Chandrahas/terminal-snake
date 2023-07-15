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
	const char heading,
	const Node *const prev_p,
	const Node *const next_p);

Node *New_Node(
	const usint y,
	const usint x,
	const char heading,
	const Node *const prev_p,
	const Node *const next_p);

bool Node_Destruct(Node *const node_p);

bool Node_Deallocate(Node **const node_pp);

bool Delete_Node(Node **const node_pp);

usint Node_GetY(const Node *const node_p);

bool Node_SetY(Node *const node_p, const usint y);

usint Node_GetX(const Node *const node_p);

bool Node_SetX(Node *const node_p, const usint x);

char Node_GetHeading(const Node *const node_p);

bool Node_SetHeading(Node *const node_p, const char heading);

Node *Node_GetPrevNodePtr(const Node *const node_p);

bool Node_SetPrevNodePtr(Node *const node_p, const Node *const prev_p);

Node *Node_GetNextNodePtr(const Node *const node_p);

bool Node_SetNextNodePtr(Node *const node_p, const Node *const next_p);

usint Node_GetFollowerY(const Node *const followedNode_p, const char relPos);

usint Node_GetFollowerX(const Node *const followedNode_p, const char relPos);

char Node_FollowerHeadingToRelPos(const char heading);

#endif