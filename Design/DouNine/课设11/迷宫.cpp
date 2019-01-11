/*
[问题描述]
利用栈操作实现迷宫问题求解。
[基本要求]
（1）从文件中读取数据，生成模拟迷宫地图，不少于10行10列。
（2）给出任意入口和出口，显示输出迷宫路线。
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<stack>
#include<queue>
#include<windows.h>

using namespace std;

// 深度搜索时的结构体 
typedef struct 
{
	char comDir; // 记录来的方向 
	char perDir; // 记录上次走过的方向，1上，2右，3下，4左 
	int x, y;
}Record;

// 广度搜索时的结构体 
typedef struct 
{
	int x, y;
}Point;


// 全局变量 
FILE *fp;
char fileName[] = "data1.txt";
int length = 0, width = 0;
int **maze = NULL;
int speed = 0; 

// 打开文件 
void fileOpen(char *method) 
{
	
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() 
{
	
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// 初始化 
void Init() 
{
	fileOpen("r");
	
	fscanf(fp, "%d%d", &length, &width);
	maze = (int**)malloc(sizeof(int*) * width);
	for (int i=0; i<width; i++) 
	{
		int *temp = (int*)malloc(sizeof(int) * length);
		for (int j=0; j<length; j++) 
		{
			fscanf(fp, "%d", &temp[j]);
		}
		maze[i] = temp;
	}
	
	fileClose();
}

// 重置
void Reset() 
{
	fileOpen("r");
	
	fscanf(fp, "%d%d", &length, &width);
	for (int i=0; i<width; i++) 
	{
		for (int j=0; j<length; j++) 
		{
			fscanf(fp, "%d", &maze[i][j]);
		}
	}
	
	fileClose();
}

// 结束
void Finish() 
{
	for (int i=0; i<width; i++) 
	{
		free(maze[i]);
	}
	free(maze);
}

// 将光标移动到x,y位置 
void SetPos(int x, int y)
{
   COORD point = { x, y };//光标要设置的位置x,y
   HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
   SetConsoleCursorPosition(HOutput, point);//设置光标位置
}

// 打印地图
void Show() 
{
	for (int i=0; i<width; i++) 
	{
		for (int j=0; j<length; j++) 
		{
			//↑↓← →
			if (maze[i][j] == 2) 
			{
				SetPos(3*j, i);
				printf(" * ");
			} 
			else if (maze[i][j] == 0) 
			{
				SetPos(3*j, i);
				printf("   ");
			}
		}
		printf("\n");
	}
	Sleep(1);
}

// 打印原始地图
void ShowOrigin()
{
	system("cls");
	for (int i=0; i<width; i++) 
	{
		for (int j=0; j<length; j++) 
		{
			if (maze[i][j] == 1) 
			{
				printf("AAA");
			}
			else if (maze[i][j] == 0) 
			{
				printf("   ");
			}
		}
		printf("\n");
	}
} 

// 深度优先
void DFS(int startX, int startY, int finishX, int finishY) 
{
	Record temp;
	temp.x = startX;
	temp.y = startY;
	if (temp.x == 0) temp.comDir = 1;
	else if (temp.x == length-1) temp.comDir = 3;
	else if (temp.y == 0) temp.comDir = 4;
	else if (temp.y == width-1) temp.comDir = 2;
	temp.perDir = 0;
	maze[temp.x][temp.y] = 2;
	
	stack<Record> s;
	s.push(temp);
	while (!s.empty()) 
	{
		Record cur = s.top(), next;
		s.pop();
		//printf("%d,%d---%d %d\n", cur.x, cur.y, cur.comDir, cur.perDir);
		if (cur.x == finishX && cur.y == finishY) break;
		cur.perDir++;
		bool hasPath = false;
		while (cur.perDir <= 4) 
		{
			if (cur.perDir == cur.comDir) 
			{
				cur.perDir++;
				continue;
			}
			
			switch (cur.perDir) 
			{
				case 1: 
				{
					if (maze[cur.x-1][cur.y] == 0) 
					{
						next.x = cur.x-1;
						next.y = cur.y;
						next.perDir = 0;
						next.comDir = 3;
						s.push(cur);
						s.push(next);
						maze[next.x][next.y] = 2;
						hasPath = true;
					}
					break;
				}
				case 2: 
				{
					if (maze[cur.x][cur.y+1] == 0) 
					{
						next.x = cur.x;
						next.y = cur.y+1;
						next.perDir = 0;
						next.comDir = 4;
						s.push(cur);
						s.push(next);
						maze[next.x][next.y] = 2;
						hasPath = true;
					}
					break;
				}
				case 3: 
				{
					if (maze[cur.x+1][cur.y] == 0) 
					{
						next.x = cur.x+1;
						next.y = cur.y;
						next.perDir = 0;
						next.comDir = 1;
						s.push(cur);
						s.push(next);
						maze[next.x][next.y] = 2;
						hasPath = true;
					}
					break;
				}
				case 4: 
				{
					if (maze[cur.x][cur.y-1] == 0) 
					{
						next.x = cur.x;
						next.y = cur.y-1;
						next.perDir = 0;
						next.comDir = 2;
						s.push(cur);
						s.push(next);
						maze[next.x][next.y] = 2;
						hasPath = true;
					}
					break;
				}
			}
			if (hasPath) break;
			cur.perDir++;
		}
		if (cur.perDir == 5) 
		{
			s.push(cur);
			maze[cur.x][cur.y] = 0;
		}
		Show();
	}
}

// 广度优先
void BFS(int startX, int startY, int finishX, int finishY) 
{
	queue< Point > q;
	Point start;
	start.x = startX;
	start.y = startY;
	q.push(start);
	
	while (!q.empty()) 
	{
		Point cur = q.front(), next;
		maze[cur.x][cur.y] = 2;
		q.pop();
		if (cur.x > 0 && maze[cur.x-1][cur.y] == 0) 
		{
			next.x = cur.x-1;
			next.y = cur.y;
			q.push(next);
		}
		if (cur.y < length-1 && maze[cur.x][cur.y+1] == 0) 
		{
			next.x = cur.x;
			next.y = cur.y+1;
			q.push(next);
		}
		if (cur.x < width-1 && maze[cur.x+1][cur.y] == 0) 
		{
			next.x = cur.x+1;
			next.y = cur.y;
			q.push(next);
		}
		if (cur.y > 0 && maze[cur.x][cur.y-1] == 0) 
		{
			next.x = cur.x;
			next.y = cur.y-1;
			q.push(next);
		}
		Show();
		if (cur.x == finishX && cur.y == finishY) break;
	}
}


int main() 
{
	Init();
	int startX = 20, startY = 1;
	int finishX = 2, finishY = 20;
	
	ShowOrigin(); 
	printf("\n该迷宫宽：%d，长：%d\n\n", width, length);
	printf("请输入入口坐标(x,y为二维数组的行和列，从0开始)：");
	scanf("%d%d", &startX, &startY);
	printf("请输入出口坐标(x,y为二维数组的行和列，从0开始)：");
	scanf("%d%d", &finishX, &finishY);
//	printf("请输入行走速度(整数，1为10毫秒)：");
//	scanf("%d", &speed);

	system("cls");
	printf("下面展示深度搜索结果......\n");
	Sleep(2000);

	maze[startX][startY] = 0;
	maze[finishX][finishY] = 0;
	ShowOrigin();
	DFS(startX, startY, finishX, finishY);
	
	system("pause");
	Reset();
	
	system("cls");
	printf("下面展示广度搜索结果......");
	Sleep(2000);
	
	maze[startX][startY] = 0;
	maze[finishX][finishY] = 0;
	ShowOrigin();
	BFS(startX, startY, finishX, finishY);
	Finish();
}
