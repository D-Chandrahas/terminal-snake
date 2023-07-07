#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "my_types.h"
#include "node.h"

typedef struct Snake Snake;

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