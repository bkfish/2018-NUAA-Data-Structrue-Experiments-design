/**
 * 行车路线 ：C++
 *
 * @author Kitty
 * @date 2019/1/8
5、行车路线  (必做)（图）
[问题描述]
　　小明和小芳出去乡村玩，小明负责开车，小芳来导航。
　　小芳将可能的道路分为大道和小道。大道比较好走，每走1公里小明会增加1的疲劳度。小道不好走，如果连续走小道，小明的疲劳值会快速增加，连续走s公里小明会增加s2的疲劳度。
　　例如：有5个路口，1号路口到2号路口为小道，2号路口到3号路口为小道，3号路口到4号路口为大道，4号路口到5号路口为小道，相邻路口之间的距离都是2公里。如果小明从1号路口到5号路口，则总疲劳值为(2+2)2+2+22=16+2+4=22。
现在小芳拿到了地图，请帮助她规划一个开车的路线，使得按这个路线开车小明的疲劳度最小。
[基本要求]
输入格式：
　　输入的第一行包含两个整数n, m，分别表示路口的数量和道路的数量。路口由1至n编号，小明需要开车从1号路口到n号路口。
接下来m行描述道路，每行包含四个整数t, a, b, c，表示一条类型为t，连接a与b两个路口，长度为c公里的双向道路。其中t为0表示大道，t为1表示小道。保证1号路口和n号路口是连通的。
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
　　从1走小道到2，再走小道到3，疲劳度为52=25；然后从3走大道经过4到达5，疲劳度为20+30=50；最后从5走小道到6，疲劳度为1。总共为76。
课程设计要求：
（1）要求从文本文件中输入；
（2）采用适当的数据结构存储由输入数据中的道路所形成的图结构；
（3）编写尽可能优的算法，处理好连续走小道造成的疲劳值的指数增长（提示：基于迪杰斯特拉算法进行改进即可完成本题）；
（4）除严格按题目要求进行输出以外，还要求输出最优路线的路径，以及从出发点到各个点的最小疲劳值。
 *思想首先还是套用迪杰斯特拉算法的模板
直接用二维数组来构建图
设置了两个数组d_long、d_short,分别保存每个结点到出发点的大道路径之和、
小道路径之和。其次，更新点权的时候，需要考虑两个来源，一个来源就是上一个结点的d_short值，
一个来源就是上一个结点的d_long值。在更新过程中要特别注意，会有多条连续的小道相连的情况，
还有可能就是大道、小道相互交错的情况，这也是我为什么要设置pre数组来保存路径上每个结点的前驱结点。 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream> 
using namespace std;
#define MAX 999 //假设最多这么多站点 
#define INF 9999999  //初始最初距离，表现为无穷大 
struct Node
{
    long long length;//记录道的长度
    int type;//记录道的类型
};
struct Node Graph[MAX][MAX]; //邻接矩阵储存 
//sum_long、sum_short,分别保存每个结点到出发点的大道路径之和、小道路径之和
long long sum_short[MAX];
long long sum_short_square[MAX];
long long sum_long[MAX];
long long d[MAX]; 
int pre[MAX]; //pre数组来保存路径上每个结点的前驱结点
int visited[MAX]; //储存已经访问的地方 
int ans=INF;
long long square(long long x)
{
    return x*x;
}
void Dijkstra(int s,int n)
{
    memset(visited,0,sizeof(visited));//初始化数据
    fill(sum_long,sum_long+MAX,INF);
    fill(sum_short,sum_short+MAX,INF);
    fill(sum_short_square,sum_short_square+MAX,INF);
    fill(pre,pre+MAX,0);
    fill(d,d+MAX,INF);
    d[s]=0;
    sum_long[s]=0;
    sum_short[s]=0;
    while(true)
    {
        int u=-1;
        long long mini=INF;//走到当前节点最小值 
        for(int i=1;i<=n;i++)
        {
            if(visited[i]==0&&d[i]<mini) //d[i]走到了i 就能赋值 否者break 相当于更新了mini,找到下一个点u 
            {
                u=i;//遍历点 如果没走过就是u为（1，2，3，4，5，6） 
                mini=d[i];//记录当前的最小数 （0，9，25，45，66，76） 
            }
        }
        if(u==-1) break;
        visited[u]=1; //此点走过 
        cout<<u<<"->";
        for(int v=1;v<=n;v++) //到达u寻找v 
        {
            if(Graph[u][v].length!=INF&&visited[v]==0) //有路 并且另外一个点没走过 
            {
                if(Graph[u][v].type==1)//小路 
                {
                    long long d1=INF;
                    long long d2=INF;
                    if(sum_short[u]!=INF)//如果有小道与源结点相连,即前面有小路 
                    {
                        //需要处理一种特殊情况，就是大道、小道交错出现的情况
                        if(pre[u]==0) d1=square(sum_short[u]+Graph[u][v].length);
                        else d1=sum_long[pre[u]]+square(sum_short[u]+Graph[u][v].length);//可能出现a通过大道与b相连，b通过小道与c相连
                                                                               //c通过小道与d相连的情况
                    }
                    if(sum_long[u]!=INF)//如果前面是大路 
                        d2=square(Graph[u][v].length)+sum_long[u];
                    if(d1<d2)
                    {
                        sum_short[v]=min(sum_short[v],sum_short[u]+Graph[u][v].length);//更新结点对应的小道点权
                        sum_short_square[v]=min(d1,sum_short_square[v]);
                    }
                    else
                    {
                        sum_short[v]=min(sum_short[v],Graph[u][v].length);//由于上一条道路是大道，所以这里需要从头开始考虑小道的点权
                        sum_short_square[v]=min(d2,sum_short_square[v]);
                        pre[v]=u;//记录当前结点的前驱结点
                    }
                    d[v]=min(sum_short_square[v],sum_long[v]);
                }
                else//当前道路是大道
                {
  
                    long long d1=INF;
                    long long d2=INF;
                    if(sum_long[u]!=INF)  d1=sum_long[u]+Graph[u][v].length;
                    if(sum_short[u]!=INF) d2=sum_short_square[u]+Graph[u][v].length;
                    long long mini=min(d1,d2);
                    sum_long[v]=min(sum_long[v],mini);
                    d[v]=min(sum_short_square[v],sum_long[v]);
                }
            }
        }
    }
    return;
}
 
int main()
{
    int n,m;
    int t,a,b;
    long long c;
    ifstream infile("input.txt");
    //scanf("%d %d",&n,&m);
    infile>>n>>m;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            Graph[i][j].length=INF;
            Graph[j][i].length=INF;
        }
    }
    for(int i=0;i<m;i++)
    {
        infile>>t>>a>>b>>c;
        //scanf("%d%d%d%lld",&t,&a,&b,&c);
        if(t==1)//小道
        {
            Graph[a][b].length=c;
            Graph[b][a].length=c;
            Graph[a][b].type=1;
            Graph[b][a].type=1;
        }
        else
        {
            Graph[a][b].length=c;
            Graph[b][a].length=c;
            Graph[a][b].type=0;
            Graph[b][a].type=0;
        }
    }
    infile.close(); 
    cout<<"到达终点路线为：\n";
    Dijkstra(1,n);
    cout<<"\n"<<endl;
    for(int i=1;i<=n;i++)
    cout<<"到达第"<<i<<"个路口的最小疲劳值为："<<d[i]<<endl; 
    cout<<endl;
    printf("到达最后为： %lld\n",d[n]);
    cout<<endl;
    system("pause");
    return 0;
}
/*
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
* 
*/
