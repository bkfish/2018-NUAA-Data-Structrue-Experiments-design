#include"Stack.h"
#include"Position.h" //存放方向
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define etype Position
using namespace std;

bool InitStack(Stack &S)
{
    S.top = (SNode *)malloc(sizeof(SNode));
    S.base = S.top;
    if(!S.top)
    {
        cout << "OVERFLOW!" << endl;
        exit(OVERFLOW);
    }
    S.top->next = NULL;
    S.base->next = NULL;
    S.nodenum = 0;
    return OK;
}
bool PushStack(Stack &S,etype &e)
{
    if(!S.top || !S.base)
        return ERROR;
    SNode *NewNode = (SNode *)malloc(sizeof(SNode));
    NewNode->seat.x = e.x;
    NewNode->seat.y = e.y;
    NewNode->seat.direction = e.direction;
    NewNode->next = S.top;
    S.top = NewNode;
    S.nodenum++;
    return OK;
}
bool PopStack(Stack &S,etype &e)
{
    if(!S.top || !S.base || S.base == S.top)
        return ERROR;
    e.x = S.top->seat.x;
    e.y = S.top->seat.y;
    e.direction = S.top->seat.direction;
    SNode *node = S.top;
    S.top = S.top->next;
    free(node);
    S.nodenum--;
    return OK;
}
bool visits(etype &e)
{
    cout << "此节点的坐标为:" << "x:"<< e.x << "  y:" << e.y << endl;
    return OK;
}
bool StackTraverse(Stack &S)
{
    if(!S.top || !S.base || S.nodenum == 0)
        return ERROR;
    SNode *top = S.top;
    while(top != S.base)
    {
        visits(top->seat);
        top = top->next;
    }
    return OK;
}
