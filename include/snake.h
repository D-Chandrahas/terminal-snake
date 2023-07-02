#ifndef SNAKE_H
#define SNAKE_H


typedef unsigned short int usint;

typedef struct Node Node;

typedef struct Snake Snake;



void Node_construct (Node *node_p, usint y, usint x, char dir, Node *prev_p, Node *next_p);

void Snake_construct (Snake *snake_p);

void Snake_append (Snake *snake_p, usint y, usint x, char dir);



#endif