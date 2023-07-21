#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "my_types.h"
#include "node.h"

typedef struct Snake Snake;

Snake *Snake_Allocate(void);

Snake *Snake_Construct(Snake *const snake_p);

Snake *New_Snake(void);

void Snake_Destruct(Snake *const snake_p);

void Snake_Deallocate(Snake *const snake_p);

void Delete_Snake(Snake *const snake_p);

usint Snake_GetLength(const Snake *const snake_p);

void Snake_SetLength(Snake *const snake_p, const usint len);

void Snake_IncrementLength(Snake *const snake_p);

char Snake_GetHeading(const Snake *const snake_p);

void Snake_SetHeading(Snake *const snake_p, const char heading);

Node *Snake_GetHeadPtr(const Snake *const snake_p);

void Snake_SetHeadPtr(Snake *const snake_p, const Node *const head_p);

Node *Snake_GetTailPtr(const Snake *const snake_p);

void Snake_SetTailPtr(Snake *const snake_p, const Node *const tail_p);

usint Snake_GetTailY(const Snake *const snake_p);

usint Snake_GetTailX(const Snake *const snake_p);

Snake *Snake_Init(Snake *const snake_p, const usint y, const usint x, const char heading);

Snake *Snake_Append(Snake *const snake_p, const usint y, const usint x, const char heading);

#endif