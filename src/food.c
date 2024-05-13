#include "my_types.h"
#include "food.h"


usint Food_GetY(const Food *const food_p)
{
    return food_p ? food_p->y : -1;
}

void Food_SetY(Food *const food_p, const usint y)
{
    if (food_p)
    {
        food_p->y = y;
    }
    return;
}

usint Food_GetX(const Food *const food_p)
{
    return food_p ? food_p->x : -1;
}

void Food_SetX(Food *const food_p, const usint x)
{
    if (food_p)
    {
        food_p->x = x;
    }
    return;
}

