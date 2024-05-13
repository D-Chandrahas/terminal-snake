#ifndef FOOD_H
#define FOOD_H

#include "my_types.h"

struct Food
{
    usint y;
    usint x;
};
typedef struct Food Food;

usint Food_GetY(const Food *const food_p);

void Food_SetY(Food *const food_p, const usint y);

usint Food_GetX(const Food *const food_p);

void Food_SetX(Food *const food_p, const usint x);

#endif