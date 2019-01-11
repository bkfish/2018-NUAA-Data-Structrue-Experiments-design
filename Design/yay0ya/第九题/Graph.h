#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#define INFINITY -1
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1 
typedef int Status;
typedef int VertexType;
typedef int VRType;
typedef int InfoType;
typedef enum {DG,DN,UDG,UDN}GraphKind;
typedef struct ArcCell{
	VRType adj;//VRType 是顶点关系类型，对无权图，用1或0
	//表示响铃否，对带权图，则为权值类型。
	InfoType *info;//该弧相关信息的指针 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量 
	AdjMatrix arcs;//邻接矩阵 
	int  vexnum,arcnum;//图的当前顶点数和弧数 
	GraphKind kind;//图的种类标志 
}MGraph;
Status LocateVex(MGraph G,VertexType u){
	//图G存在，u和G中顶点有相同的特征
//若G中存在顶点u，则返回该顶点在图中位置；否则返回其他信息
	int i,temp;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==u){//如果这俩个顶点相同 
			temp=i;//用temp记录住其位置; 
			return temp;//返回该点在列表中的位置 
		}
	}
	return -1;//不存在该点，返回-1 
}

void caculate(MGraph G,int j){
	int loc=LocateVex(G,j);
	int flag=0;
	for(int i=0;i<G.vexnum;i++){
		if(G.arcs[loc][i].adj==1)
			flag++;
	}
	cout<<"Cc("<<j<<")"<<"="
		<<setiosflags(ios::fixed)
		<<setprecision(2)<<(double)(flag+1)/G.vexnum<<endl;
} 

Status CreateUDG(MGraph &G){//构造无向图 
	//采用数组（邻接矩阵）表示法，构造无向图G；
	int i,j,k;
	fstream file;
	file.open("test.txt",ios::in);
	if(!file.is_open()){
		cout<<"文件打开失败\n";
		return 0;
	}
	VertexType v1,v2;
	file>>G.vexnum;
	file>>G.arcnum;//分别输入端点数和边数 
	for(i=0;i<G.vexnum;i++) G.vexs[i]=i+1;//构造顶点向量
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//对邻接矩阵进行初始化	
	}
	for(k=0;k<G.arcnum;k++){
		file>>v1;
		file>>v2;
		i=LocateVex(G,v1); j=LocateVex(G,v2);//确定v1与v2在G中的位置
		G.arcs[i][j].adj=1;
		G.arcs[j][i].adj=1; 
	}
	int K;
	file>>K;
	int number[K]={};
	for(i=0;i<K;i++){
		file>>number[i];	
		caculate(G,number[i]);
	}
		 
}//构造无向图 
