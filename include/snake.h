#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "my_types.h"
#include "node.h"

typedef struct Snake Snake;

Snake *Snake_Allocate(void);

Snake *Snake_Construct(Snake *const snake_p);

Snake *New_Snake(void);

bool Snake_Destruct(Snake *const snake_p);

bool Snake_Deallocate(Snake **const snake_pp);

bool Delete_Snake(Snake **const snake_pp);

usint Snake_GetLength(const Snake *const snake_p);

bool Snake_SetLength(Snake *const snake_p, const usint len);

bool Snake_IncrementLength(Snake *const snake_p);

Node *Snake_GetHeadPtr(const Snake *const snake_p);

bool Snake_SetHeadPtr(Snake *const snake_p,const Node *const head_p);

Node *Snake_GetTailPtr(const Snake *const snake_p);

bool Snake_SetTailPtr(Snake *const snake_p,const Node *const tail_p);

usint Snake_GetTailY(const Snake *const snake_p);

usint Snake_GetTailX(const Snake *const snake_p);

char Snake_GetTailHeading(const Snake *const snake_p);

char Snake_GetHeading(const Snake *const snake_p);

char Snake_SetHeading(Snake *const snake_p, const char heading);

usint Snake_GetAppendX(const Snake *const snake_p);

usint Snake_GetAppendY(const Snake *const snake_p);

bool Snake_Init(Snake *const snake_p, const usint y, const usint x, const char heading);

bool Snake_Append(Snake *const snake_p);

#endif