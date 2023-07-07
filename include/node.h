#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include "my_types.h"

typedef struct Node Node;

Node *Node_Allocate(void);

Node *Node_Construct(Node *node_p, usint y, usint x, char heading, Node *prev_p, Node *next_p);

Node *New_Node(usint y, usint x, char heading, Node *prev_p, Node *next_p);

usint Node_GetY(const Node *node_p);

bool Node_SetY(Node *node_p, usint y);

usint Node_GetX(const Node *node_p);

bool Node_SetX(Node *node_p, usint x);

char Node_GetHeading(const Node *node_p);

bool Node_SetHeading(Node *node_p, char heading);

Node *Node_GetPrevNodePtr(const Node *node_p);

bool Node_SetPrevNodePtr(Node *node_p, Node *prev_p);

Node *Node_GetNextNodePtr(const Node *node_p);

bool Node_SetNextNodePtr(Node *node_p, Node *next_p);

usint Node_GetFollowerY(const Node *followedNode_p, char relPos);

usint Node_GetFollowerX(const Node *followedNode_p, char relPos);

char Node_FollowerHeadingToRelPos(const Node *followedNode_p, char heading);

#endif