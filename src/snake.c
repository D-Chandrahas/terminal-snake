#include <stddef.h>
#include "snake.h"


struct Node {
	usint y;
	usint x;
	char dir;
	Node *prev_p;
	Node *next_p;
};

struct Snake {
	usint len;
	Node *head_p;
	Node *tail_p;
};


void Node_construct (Node *node_p, usint y, usint x, char dir, Node *prev_p, Node *next_p) {
	node_p->y = y;
	node_p->x = x;
	node_p->dir = dir;
	node_p->prev_p = prev_p;
	node_p->next_p = next_p;
	return;
}

void Snake_construct (Snake *snake_p) {
	snake_p->len = 0;
	snake_p->head_p = NULL;
	snake_p->tail_p = NULL;
	return;
}

void Snake_append (Snake *snake_p, usint y, usint x, char dir) {
	Node *temp_node_p = (Node *) malloc (sizeof(Node));
	if (snake_p->len == 0) {
		Node_construct (temp_node_p, y, x, dir, NULL, NULL);
		snake_p->head_p = temp_node_p;
	}
	else {
		Node_construct (temp_node_p, y, x, dir, snake_p->tail_p, NULL);
		snake_p->tail_p->next_p = temp_node_p;
	}
	snake_p->tail_p = temp_node_p;
	(snake_p->len)++;
	return;
}


	




