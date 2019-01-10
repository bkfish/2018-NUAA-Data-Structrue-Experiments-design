/*11、【2】迷宫问题（选做）（栈与队列），（深度搜索，广度搜索）
[问题描述]
利用栈操作实现迷宫问题求解。
[基本要求]
（1）从文件中读取数据，生成模拟迷宫地图，不少于10行10列。
（2）给出任意入口和出口，显示输出迷宫路线。
*/
#include"Maze.h" //函数声明 
#include"Maze.cpp" //函数定义 
#include"Position.h" //点存储 
#include"Stack.h" //自己编写一个栈 
#include<iostream>
using namespace std;
int main()
{
    Maze maze;
    Stack S;
    Position start;
    Position end;
    start.x = 1;
    start.y = 1;
    end.x = 10;
    end.y = 10;
    InitMaze(maze);
    cout << "原迷宫：" << endl << endl;
    PrintMaze(maze);
    cout  << endl << "********************" << endl;
    cout << "*   请输入起点：   *" << endl;
    cout << "********************" << endl << endl;
    cout << "x:" ;
    cin >> start.x;
    cout << "y:" ;
    cin >> start.y;
    cout  << endl << "********************" << endl;
    cout << "*   请输入终点：   *" << endl;
    cout << "********************" << endl << endl;
    cout << "x:" ;
    cin >> end.x;
    cout << "y:" ;
    cin >> end.y;
    if(MazePath(maze,start,end,S))
    {
        cout << endl << endl << "迷宫的解：(*代表路线)" << endl << endl;
        PrintMaze(maze);
    }
    else
    {
        cout << endl << "********************" << endl;
        cout << "*   此迷宫无解！   *" << endl;
        cout << "********************" << endl;
    }
     system("pause");
    return 0;
   
}
