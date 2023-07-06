#ifndef SNAKE_H
#define SNAKE_H

typedef unsigned short int usint;

typedef struct Node Node;

typedef struct Snake Snake;

Node *Node_Allocate(void);

Node *Node_Construct(Node *node_p, usint y, usint x, char heading, Node *prev_p, Node *next_p);

Node *New_Node(usint y, usint x, char heading, Node *prev_p, Node *next_p);

usint Node_GetFollowerY(const Node *followedNode_p, char relPos);

usint Node_GetFollowerX(const Node *followedNode_p, char relPos);

char Node_FollowerHeadingToRelPos(const Node *followedNode_p, char heading);

Snake *Snake_Allocate(void);

Snake *Snake_Construct(Snake *snake_p);

Snake *New_Snake(void);

usint Snake_GetLength(const Snake *snake_p);

Node *Snake_GetHeadPtr(const Snake *snake_p);

Node *Snake_GetTailPtr(const Snake *snake_p);

usint Snake_GetTailY(const Snake *snake_p);

usint Snake_GetTailX(const Snake *snake_p);

char Snake_GetTailHeading(const Snake *snake_p);

usint Snake_GetAppendX(Snake *snake_p);

usint Snake_GetAppendY(Snake *snake_p);

Snake *Snake_Append(Snake *snake_p);

#endif