#include"Maze.h"
#include"Stack.h"
#include"Stack.cpp"
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

bool mark[RANGE][RANGE];
using namespace std;
bool InitMaze(Maze &maze)
{
    ifstream infile("data.txt",ios::in);
    if(!infile.is_open())
    {
        cout << "文件不能打开！" <<endl;
        exit(ERROR);
    }
    int x = 0;
    int row = 0;
    int col = 0;
    infile >> row;
    infile >> col;
    maze.row = row;
    maze.col = col;
    for(int i = 1;i <= row;i++)
        for(int j = 1;j <= col;j++)
            maze.arr[i][j] = ' ';
    for(int i = 0;i <= row+1;i++)
    {
        maze.arr[i][0] = 30;
        maze.arr[i][col+1] = 30;
    }
    for(int i = 0;i <= col+1;i++)
    {
        maze.arr[0][i] = 30;
        maze.arr[row+1][i] = 30;
    }
    for(int i = 1;i <= row;i++)
       {
            for(int j = 1;j <= col;j++)
        {
            infile >> x;
            if(x == 1)
            {
                maze.arr[i][j] = 30;
            }
        }
       }
    infile.close();
}

bool nextpos(Position &a,Position &b,int row,int col)
{
    a.x = -1;
    if(b.y+1 <= col && mark[b.x][b.y+1] == FALSE)//右
    {
        a.x = b.x;
        a.y = b.y+1;
        return OK;
    }
    if(b.x+1 <= row && mark[b.x+1][b.y] == FALSE)//下
    {
        a.x = b.x+1;
        a.y = b.y;
        return OK;
    }


    if(b.y-1 > 0 && mark[b.x][b.y-1] == FALSE)//左
    {
        a.x = b.x;
        a.y = b.y-1;
        return OK;
    }
    if(b.x-1 > 0 && mark[b.x-1][b.y] == FALSE)//上
    {
        a.x = b.x-1;
        a.y = b.y;
        return OK;
    }

}

bool MazePath(Maze &maze,Position start,Position end,Stack S)
{
    InitStack(S);
    Position now = start;
    Position e;
    bool found = FALSE;
    for(int i = 0;i <= maze.row+1;i++)
        for(int j = 0;j <= maze.col+1;j++)
            {
                if(maze.arr[i][j] == 30)
                    mark[i][j] = TRUE;
                else
                    mark[i][j] = FALSE;
            }//初始化mark数组，0表示未访问过，1表示是墙，2表示留下了足迹
    PushStack(S,now);
    mark[now.x][now.y] = 2;//留下足迹
    while(S.nodenum != 0 && !(now.x == end.x && now.y == end.y))
    {
        PopStack(S,e);
        PushStack(S,e);//取得栈顶元素
        nextpos(now,e,maze.row,maze.col);//找下一个位置，若都被访问过，将now.x赋值为-1
        if(now.x == -1)
        {
            PopStack(S,e);//回溯到上一个节点
            continue;
        }
        mark[now.x][now.y] = 2;//留下足迹
        PushStack(S,now);
    }
    if(now.x == end.x && now.y == end.y)
        found = TRUE;
    else
        found = FALSE;
    while(S.nodenum != 0)
    {
        PopStack(S,e);
        maze.arr[e.x][e.y] = '*';
    }//栈中的元素即为路径输入到maze中
    StackTraverse(S);
    return found;
}

void PrintMaze(Maze &maze)
{
    for(int i = 0;i <= maze.row+1;i++)
    {
        for(int j = 0;j <= maze.col+1;j++)
            cout << maze.arr[i][j] << " ";
        cout << endl;
    }
}


