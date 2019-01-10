#include<stdio.h>
#include<stdlib.h>
#define INF 0x7fffffff 

typedef struct Node
{
    long long c;
	//长度
    int flag;
	//标识道路的类型，1为小道，0为大道 
}node;

FILE * input;
//文件指针
 
int n,m;
int t,a,b;
long long c;
//用于读取输入的变量

struct Node G[1001][1001];
//邻接矩阵储存道路

long long dd[1001];
long long xd[1001];
long long xd_sq[1001];
//dd和sd分别保存每个结点到出发点的大道路径之和和小道路径之和,区分点为最后的一条路的种类 
long long d[1001];
//保存花费 

int p[1001];
//记录结点的前驱结点
int flag[1001];
//标记是否访问

void Dijkstra(int s,int n)
{
	d[s] = 0;
	dd[s] = 0;
	xd[s] = 0;
	//初始化到起点的花费为0
	
	while(1)
	{
		int x = -1;
        long long min = INF;
        
        for(int i = 1;i <= n;i++)
        {
            if(!flag[i] && d[i] < min)
            //遍历寻找最小花费 
            {
                x = i;
				//记录编号 
                min = d[i];
				//记录当前的最小数
            }
        }
        
        if(x == -1)
		{
			break;
		}
		flag[x] = 1;
		
		for(int i = 1;i <= n;i++)
		//遍历松弛 
        {
            if(G[x][i].c != INF && !flag[i])
			//存在道路且另外一个点没走过 
            {
                if(G[x][i].flag == 1)
                //当前道路是小道
                {
                    long long xdnow = INF;
                    //计算前面走小道的花费 
                    long long ddnow = INF;
                    //计算前面走大道的花费 
                    
                    if(xd[x] != INF)
					//源结点到x有小道 
                    {
                        if(p[x] == 0)
                        //没有前驱结点，也就是并没有交错 
						{
							xdnow = (xd[x] + G[x][i].c) * (xd[x] + G[x][i].c);
						}
                        else
                        //有交错 
						{
							xdnow = dd[p[x]] + (xd[x] + G[x][i].c) * (xd[x] + G[x][i].c);
						}
                    }
                    
                    if(dd[x] != INF)
					//源结点到x有大道
					{
						ddnow = (G[x][i].c) * (G[x][i].c) + dd[x];
					}
					
                    if(xdnow < ddnow)
                    //前面选择走小道 
                    {
                        xd[i] = xd[i] < (xd[x] + G[x][i].c) ? xd[i] : (xd[x] + G[x][i].c);
                        xd_sq[i] = xdnow < xd_sq[i] ? xdnow : xd_sq[i];
                    }
                    else
                    //前面选择走大道 
                    {
                        xd[i] = xd[i] < G[x][i].c ? xd[i] : G[x][i].c;
                        xd_sq[i] = ddnow < xd_sq[i] ? ddnow : xd_sq[i];
                        
                        p[i] = x;
						//记录前驱结点
                    }
                    
                    d[i] = xd_sq[i] < dd[i] ? xd_sq[i] : dd[i];
                    //记录最小花费 
                }
                else
				//当前道路是大道
                {
                    long long xdnow = INF;
                    long long ddnow = INF;
                    
                    if(dd[x] != INF)
                    //源结点到x有大道
					{
						xdnow = dd[x] + G[x][i].c;
					}
                    if(xd[x] != INF)
                    //源结点到x有小道
					{
						ddnow = xd_sq[x] + G[x][i].c;
					}
					
                    long long min2;
                    
					min2 = xdnow < ddnow ? xdnow : ddnow;
                    dd[i] = dd[i] < min2 ? dd[i] : min2;
                    d[i] = xd_sq[i] < dd[i] ? xd_sq[i] : dd[i];
                }
            }
        }
	}
	
	return;
} 

int main()
{
	input = fopen("input.txt","r+");
	
	fscanf(input,"%d %d",&n,&m);
	
	for(int i = 0;i <= n;i++)
    {
        for(int j = 0;j <= n;j++)
        {
            G[i][j].c = INF;
            G[j][i].c = INF;
        }
    }
    //初始化道路的花费
    
    for(int i = 0;i < 1001;i++)
    {
    	dd[i] = INF;
    	xd[i] = INF;
    	xd_sq[i] = INF;
    	p[i] = 0;
    	d[i] = INF;
	}
	
	while(m--)
	{
		fscanf(input,"%d %d %d %lld",&t,&a,&b,&c);
		//printf("%d %d %d %lld\n",t,a,b,c);
		
		if(t==1)
		//小道
        {
            G[a][b].c = c;
            G[b][a].c = c;
            G[a][b].flag = 1;
            G[b][a].flag = 1;
        }
        else
        //大道 
        {
            G[a][b].c = c;
            G[b][a].c = c;
            G[a][b].flag = 0;
            G[b][a].flag = 0;
        }
	}
	
	Dijkstra(1,n);
	//使用Dijkstra算法求单元最短路径 
	
	for(int i = 1;i <= n;i++)
	{
		printf("to %d cost:%d\n",i,d[i]);
	}
	
	fclose(input);
	//关闭文件指针 
	
	return 0;
} 
