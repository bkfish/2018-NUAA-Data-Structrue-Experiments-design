#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include"Position.h"
#define etype Position
typedef struct SNode
{
    Position seat;
    struct SNode *next;
}SNode;

typedef struct
{
    SNode *base;
    SNode *top;
    int nodenum;
}Stack;
bool InitStack(Stack &S);
bool PushStack(Stack &S,etype &e);
bool PopStack(Stack &S,etype &e);
bool visits(etype &e);
bool StackTraverse(Stack &S);


#endif // STACK_H_INCLUDED
