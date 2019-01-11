#include<iostream>
using namespace std;
#include"Stack.h"
#include<fstream>
#define MAX_VERTEX_NUM 20
#define MAX 32767
int count=0;
typedef int Status;
typedef int VertexType;
typedef int VRType;
typedef int InfoType;
typedef struct ArcCell{
	bool type;//
	VRType adj;//VRType  表示网之间的权值 
	//表示响铃否，对带权图，则为权值类型。
	InfoType *info;//该弧相关信息的指针 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量 
	AdjMatrix arcs;//邻接矩阵 
	int  vexnum,arcnum;//图的当前顶点数和弧数 
}MGraph;
Status Initarray(MGraph &G,int n){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			G.arcs[i][j].adj=MAX;//将矩阵中所有的权弧置为最大值，进行初始化 
			G.arcs[i][j].type=0;//一开始先设置为大道 
		}
	}
	return 1; 
}
Status findroad(MGraph G,int road[],int n){
	if(road[n]==G.vexnum){
		count++;
		fstream file;
		file.open("road.txt",ios::out|ios::app);
		if(!file.is_open())
		{
			cout<<"文件打开失败\n";
			return 0;
		}
		for(int i=0;i<=n;i++){
			file<<road[i];
			file<<" "; 
		}
		file.close();
	}
	else{
		int temp=road[n];
		for(int i=1;i<=G.vexnum;i++){
			if(G.arcs[temp][i].adj!=MAX){
				{
					road[n+1]=i;
					findroad(G,road,n+1);
				}
			}
		}
	}
}
Status roadadd(int &he,int road[],int n,MGraph G){
	SqStack S;
	InitStack(S);//用栈来记录是否连续
	Push(S,road[0]);//将一个值压入栈 
	int temp1=0,temp2=0;
	int littleroad=0;
	for(int i=1;i<=n;i++){
		temp2=road[i];
		GetTop(S,temp1);//取栈顶元素赋给temp1 
		if(G.arcs[temp1][temp2].type==1){
			littleroad+=G.arcs[temp1][temp2].adj;//将小路的值相加 
		}
		if(G.arcs[temp1][temp2].type==0){
			he+=littleroad*littleroad;
			he+=G.arcs[temp1][temp2].adj;
			littleroad=0;
			}
		if(i==n){
			he+=littleroad*littleroad;
			littleroad=0;
		}
		Push(S,road[i]);//将该元素顶点压入栈	
		}
		return 1;
		
}
Status roadout(int i,MGraph G){
	fstream file;
	int road[G.vexnum];
	file.open("road.txt",ios::in);
	for(int j=0;j<=i;j++){
		for(int t=0;t<G.vexnum;t++){
			file>>road[t];
			if(road[t]==G.vexnum){
				break;
			}
		}
	}
	int j=0;
	cout<<endl;
	while(road[j]!=G.vexnum){
		cout<<"路口"<<road[j]<<"到路口"<<road[j+1]<<" ";
		j++; 
	}
	return 1;
}
Status miniout(MGraph G){
	int add[count]={};
	int road[G.vexnum];
	int record=0;
	fstream file;
	file.open("road.txt",ios::in);
	for(int i=0;i<count;i++){
		for(int j=0;j<G.vexnum;j++){
		file>>road[j];//将文件中的数据读出来；
		if(road[j]==G.vexnum){
			  roadadd(add[i],road,j,G);//如果到达这个路口六
			break;//跳出这个循环 
		}
		 
	}
	}
	int min=add[0];
	for(int i=0;i<count;i++){
		if(add[i]<min)
			{
				min=add[i];
				record=i;
				}
	}
	cout<<min;
	file.close();
	roadout(record,G);
} 
