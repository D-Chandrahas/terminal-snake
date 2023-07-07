#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "my_types.h"
#include "node.h"

struct Node
{
    usint y;
    usint x;
    char heading;
    Node *prev_p;
    Node *next_p;
};

Node *Node_Allocate(void)
{
    return (Node *)malloc(sizeof(Node));
}

Node *Node_Construct(Node *node_p, usint y, usint x, char heading, Node *prev_p, Node *next_p)
{
    if (node_p == NULL)
    {
        return NULL;
    }

    node_p->y = y;
    node_p->x = x;
    node_p->heading = heading;
    node_p->prev_p = prev_p;
    node_p->next_p = next_p;
    return node_p;
}

Node *New_Node(usint y, usint x, char heading, Node *prev_p, Node *next_p)
{
    return Node_Construct(Node_Allocate(), y, x, heading, prev_p, next_p);
}

usint Node_GetY(const Node *node_p)
{
    if (node_p == NULL)
    {
        return -1;
    }

    return node_p->y;
}

bool Node_SetY(Node *node_p, usint y)
{
    if (node_p == NULL)
    {
        return false;
    }

    node_p->y = y;
    return true;
}

usint Node_GetX(const Node *node_p)
{
    if (node_p == NULL)
    {
        return -1;
    }

    return node_p->x;
}

bool Node_SetX(Node *node_p, usint x)
{
    if (node_p == NULL)
    {
        return false;
    }

    node_p->x = x;
    return true;
}

char Node_GetHeading(const Node *node_p)
{
    if (node_p == NULL)
    {
        return '\0';
    }

    return node_p->heading;
}

bool Node_SetHeading(Node *node_p, char heading)
{
    if (node_p == NULL)
    {
        return false;
    }

    node_p->heading = heading;
    return true;
}

Node *Node_GetPrevNodePtr(const Node *node_p)
{
    if (node_p == NULL)
    {
        return NULL;
    }

    return node_p->prev_p;
}

bool Node_SetPrevNodePtr(Node *node_p, Node *prev_p)
{
    if (node_p == NULL)
    {
        return false;
    }

    node_p->prev_p = prev_p;
    return true;
}

Node *Node_GetNextNodePtr(const Node *node_p)
{
    if (node_p == NULL)
    {
        return NULL;
    }

    return node_p->next_p;
}

bool Node_SetNextNodePtr(Node *node_p, Node *next_p)
{
    if (node_p == NULL)
    {
        return false;
    }

    node_p->next_p = next_p;
    return true;
}

usint Node_GetFollowerY(const Node *followedNode_p, char relPos)
{
    if (followedNode_p == NULL)
    {
        return -1;
    }

    if (relPos == 'u')
    {
        return followedNode_p->y - 1;
    }
    else if (relPos == 'd')
    {
        return followedNode_p->y + 1;
    }
    else if (relPos == 'l' || relPos == 'r')
    {
        return followedNode_p->y;
    }
    else
    {
        return -1;
    }
}

usint Node_GetFollowerX(const Node *followedNode_p, char relPos)
{
    if (followedNode_p == NULL)
    {
        return -1;
    }

    if (relPos == 'l')
    {
        return followedNode_p->x - 1;
    }
    else if (relPos == 'r')
    {
        return followedNode_p->x + 1;
    }
    else if (relPos == 'u' || relPos == 'd')
    {
        return followedNode_p->x;
    }
    else
    {
        return -1;
    }
}

char Node_FollowerHeadingToRelPos(const Node *followedNode_p, char heading)
{
    if (followedNode_p == NULL)
    {
        return '\0';
    }

    if (heading == 'u')
    {
        return 'd';
    }
    else if (heading == 'd')
    {
        return 'u';
    }
    else if (heading == 'l')
    {
        return 'r';
    }
    else if (heading == 'r')
    {
        return 'l';
    }
    else
    {
        return '\0';
    }
}