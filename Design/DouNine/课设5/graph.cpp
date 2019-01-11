/*
[问题描述]
　　小明和小芳出去乡村玩，小明负责开车，小芳来导航。
　　小芳将可能的道路分为大道和小道。大道比较好走，每走1公里小明会增加1的疲劳度。
	小道不好走，如果连续走小道，小明的疲劳值会快速增加，连续走s公里小明会增加s2的疲劳度。
　　例如：有5个路口，1号路口到2号路口为小道，2号路口到3号路口为小道，3号路口到4号路口为大道，
	4号路口到5号路口为小道，相邻路口之间的距离都是2公里。如果小明从1号路口到5号路口，
	则总疲劳值为(2+2)2+2+22=16+2+4=22。
	现在小芳拿到了地图，请帮助她规划一个开车的路线，使得按这个路线开车小明的疲劳度最小。
[基本要求]
输入格式：
　　输入的第一行包含两个整数n, m，分别表示路口的数量和道路的数量。路口由1至n编号，
	小明需要开车从1号路口到n号路口。
接下来m行描述道路，每行包含四个整数t, a, b, c，表示一条类型为t，连接a与b两个路口，长度为c公里的双向道路。
其中t为0表示大道，t为1表示小道。保证1号路口和n号路口是连通的。
输出格式
输出一个整数，表示最优路线下小明的疲劳度。
样例输入
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
样例输出
76
样例说明
　　从1走小道到2，再走小道到3，疲劳度为5^2=25；然后从3走大道经过4到达5，疲劳度为20+30=50；最后从5走小道到6，疲劳度为1。总共为76。
课程设计要求：
（1）要求从文本文件中输入；
（2）采用适当的数据结构存储由输入数据中的道路所形成的图结构；
（3）编写尽可能优的算法，处理好连续走小道造成的疲劳值的指数增长（提示：基于迪杰斯特拉算法进行改进即可完成本题）；
（4）除严格按题目要求进行输出以外，还要求输出最优路线的路径，以及从出发点到各个点的最小疲劳值。
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<stack>

using namespace std;

typedef struct 
{
	char type;
	int weight;
}Arc;

typedef struct 
{
	int pre;	// 最短路径的上一个点 
	int length;	// 到该点(数组下标为对应序号的点)到起始点的最短路径长度 
	bool final;	// 是否在最小路径中 
}Djs;

// 全局变量 
FILE *fp;
char fileName[] = "data.txt";
int n = 0, m = 0;
Arc **graph;
Djs *dj = NULL; 


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

// 初始化函数 
void Init() 
{
	
	//printf("--------->Init()\n");
	fileOpen("r");
	fscanf(fp, "%d%d", &n, &m);
	// 初始化图 
	graph = (Arc**)malloc(sizeof(Arc*) * (n+1));
	for (int i=0; i<=n; i++) 
	{
		graph[i] = (Arc*)malloc(sizeof(Arc) * (n+1));
	}
	for (int i=0; i<=n; i++) 
	{
		for (int j=0; j<=n; j++) 
		{
			graph[i][j].type = 0;
			graph[i][j].weight = 0;
		}
	}
	
	// 根据数据给图赋值 
	int x = 0, y = 0, type = 0, weight = 0;
	for (int i=1; i<=m; i++) 
	{
		fscanf(fp, "%d%d%d%d", &type, &x, &y, &weight);
		graph[x][y].type = type;
		graph[x][y].weight = weight;
		graph[y][x] = graph[x][y];
	}
	
	// 初始化迪杰斯特拉算法数据结构 
	dj = (Djs*)malloc(sizeof(Djs) * (n+1));
	for (int i=1; i<=n; i++) 
	{
		dj[i].final = false;
		dj[i].pre = 1;
		if (graph[1][i].type) dj[i].length = graph[1][i].weight * graph[1][i].weight;
		else dj[i].length = graph[1][i].weight;
	}
	dj[1].final = true;
	
	//printf("<--------------\n");
}

// 结束函数
void Finish() 
{
	
	for (int i=0; i<=n; i++) 
	{
		free(graph[i]);
	}
	free(graph);
	free(dj);
	fileClose();
} 

// 辅助函数，求某点到起始点的长度
int getLength(int end, int pre) 
{
	//cout<<"===============\n";
	int length = 0, cur = end, sum = 0;
	while (cur != 1) 
	{
		//cout<<pre<<"===="<<cur<<"===="<<graph[pre][cur].type<<endl;
		if (graph[pre][cur].type) 
		{
			sum += graph[pre][cur].weight;
			//cout<<"sum:"<<sum<<endl;
		}
		else 
		{
			length += sum*sum + graph[pre][cur].weight;
			sum = 0;
			//cout<<"length:"<<length<<endl;
		}
		cur = pre;
		pre = dj[cur].pre;
	}
	length += sum*sum + graph[pre][cur].weight;
	//cout<<"======="<<length<<"======="<<endl;
	return length;
}

// 根据迪杰斯特拉求最短路径 
void FindDjs() 
{
	
	// 到n-1，因为起始点已经为true 
	for (int i=1; i<=n-1; i++) 
	{
		int min = INT_MAX, minPos = i;
		for (int j=1; j<=n; j++) 
		{
			if (dj[j].length && !dj[j].final && dj[j].length<min) 
			{
				min = dj[j].length;
				minPos = j;
			}
		}
		dj[minPos].final = true;
		for (int j=1; j<=n; j++) 
		{
			// graph[minPos][j].weight不为0，则说明j位置顶点跟这个新点相邻 
			int newLength = getLength(j, minPos);
			if (!dj[j].final && graph[minPos][j].weight && 
				(!dj[j].length || dj[j].length && newLength < dj[j].length)) 
			{
				dj[j].length = newLength;
				dj[j].pre = minPos;
			}
		}
//		for (int j=1; j<=n; j++) {
//			printf("%d %d %d\n", dj[j].pre, dj[j].length, dj[j].final);
//		}
	}
}


int main() 
{
	
	Init();
	
//	for (int i=0; i<n; i++) {
//		for (int j=0; j<n; j++) {
//			printf("%d(%d)  ", graph[i][j].weight, graph[i][j].type);
//		}
//		printf("\n");
//	}
//	printf("\n");
//	
//	for (int i=1; i<=n; i++) {
//		printf("%d %d %d\n", dj[i].pre, dj[i].length, dj[i].final);
//	}
//	printf("\n");
	
	FindDjs();
	
	printf("%d\n\n", dj[n].length);
	
	stack<int> res;
	int cur = n, pre = dj[cur].pre;
	while (cur != 1) 
	{
		res.push(cur);
		cur = pre;
		pre = dj[cur].pre;
	}
	res.push(cur);
	printf("%d", res.top());
	res.pop();
	while (!res.empty()) 
	{
		printf("--->%d", res.top());
		res.pop();
	}	
	printf("\n\n");
	
	for (int i=1; i<=n; i++) 
	{
		printf("1------>%d: %d\n", i, dj[i].length);
	}
	
	Finish();
}
