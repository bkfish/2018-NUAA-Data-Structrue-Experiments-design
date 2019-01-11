//第六次上机第一题
#include<iostream>
using namespace std;
#include"Queue.h"
#include<stdlib.h>
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
Status CreateDG(MGraph &G){//构造有向图 
	//采用数组（邻接矩阵）表示法，构造无向网G；
	int i,j,k;
	VertexType v1,v2; 
	cout<<"请输入 顶点数，边数"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//输入顶点数与弧数 
	cout<<"请输入顶点值"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//构造顶点向量
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//对邻接矩阵进行初始化	
	}
	cout<<"输入边两端的端点值（默认第一个输入点为弧尾，第二个为弧头）"<<endl;
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d",&v1,&v2);
		i=LocateVex(G,v1); j=LocateVex(G,v2);//确定v1与v2在G中的位置
		G.arcs[i][j].adj=1; 
	}	 
}//构造有向图
Status CreateDN(MGraph &G){//构造有向网
	 int i,j,k,w;
	VertexType v1,v2;
	cout<<"输入端点数，边数"<<endl; 
	scanf("%d%d",&G.vexnum,&G.arcnum);//输入顶点数与弧数 
	cout<<"输入端点值"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//构造顶点向量
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//对邻接矩阵进行初始化	
	}
	cout<<"输入边的两个端点，同时输入边的权值（默认第一个输入点为弧尾，第二个为弧头）"<<endl;
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d%d",&v1,&v2,&w);//输入边的两个顶点，以及边上的权值 
		i=LocateVex(G,v1); j=LocateVex(G,v2);//确定v1与v2在G中的位置
		G.arcs[i][j].adj=w; 
	}	
}//构造有向网 
Status CreateUDG(MGraph &G){//构造无向图 
	//采用数组（邻接矩阵）表示法，构造无向图G；
	int i,j,k;
	VertexType v1,v2;
	cout<<"输入端点数，边数"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//输入顶点数与弧数 
	cout<<"请输入顶点值"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//构造顶点向量
	cout<<"输入边两端的端点值"<<endl;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//对邻接矩阵进行初始化	
	}
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d",&v1,&v2);
		i=LocateVex(G,v1); j=LocateVex(G,v2);//确定v1与v2在G中的位置
		G.arcs[i][j].adj=1;
		G.arcs[j][i].adj=1; 
	}	 
}//构造无向图 
Status CreateUDN(MGraph &G){//构造无向网
	 int i,j,k,w;
	VertexType v1,v2; 
	cout<<"输入端点数，边数"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//输入顶点数与弧数 
	cout<<"请输入顶点值"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//构造顶点向量
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//对邻接矩阵进行初始化	
	}
	cout<<"输入边的两个端点，同时输入边的权值"<<endl;
	for(k=0;k<G.arcnum;k++){
		cin>>v1;
		cin>>v2;
		cin>>w;//输入边的两个顶点，以及边上的权值 
		i=LocateVex(G,v1); j=LocateVex(G,v2);//确定v1与v2在G中的位置
		G.arcs[i][j].adj=w;
		G.arcs[j][i].adj=w; 
	}	
}//构造无向网
Status CreateGraph(MGraph &G){
//V是图的顶点集，VR是图中弧的集合
//按V和VR的定义构造图G
	int n;
	cout<<"请输入图的类型：1.DG,2.DN,3.UDG,4.UDN\n"; 
	cin>>n;
	switch(n){
		case 1:G.kind=DG;break;
		case 2:G.kind=DN;break;
		case 3:G.kind=UDG;break;
		case 4:G.kind=UDN;break;
	}
	switch(G.kind){
		case DG:return CreateDG(G);
		case DN:return CreateDN(G);
		case UDG:return CreateUDG(G);
		case UDN:return CreateUDN(G);
		default:return ERROR; 
	}
	return OK;	
}
 
Status DestroyGraph(MGraph &G){
	if(!G.vexnum)//如果中间不存在任何顶点，认为不存在该图；
		return ERROR;
	else{
		free(G.arcs);
		free(G.vexs);//释放掉顶点和弧的空间
		G.vexnum=G.arcnum=0;//将定点数和边数置为0
		return OK; 
	} 
}//图G存在，销毁图G

Status GetVex(MGraph G,VertexType v){//图G存在，v是G中某个顶点
//返回V的值
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){
			 return v;
		}
	}
	return -1;//不存在该点，返回-1 
}
Status PutVex(MGraph &G,VertexType v,int value){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){
			G.vexs[i]=value;
			return OK;
		}
	}
	return ERROR;
}
//图G存在，v是G中的某个顶点
//对V赋值Value
Status FirstAdjVex(MGraph G,VertexType v)
{//返回图G中第v个顶点的第一个邻接点
	int i,j=-1;//可能是顶点自身到自身
for(i=0;i<G.vexnum;i++)
	{
		if(!G.arcs[v][i].adj||G.arcs[v][i].adj==INFINITY)//第v个顶点的第i个邻接顶点
		j++;
		else
			{
				j++;
				break;
			}
	}
	if(i==G.vexnum-1&&!G.arcs[v][i].adj||G.arcs[v][i].adj==INFINITY)
		return -1;
	return j;
}

//图G存在，v是G中的某个顶点
//返回v的第一个邻接顶点，若顶点在G中没有邻接顶点，则返回空
Status NextAdjVex(MGraph G,VertexType v,VertexType w){
	//图G存在，v是G中某个顶点，w是v的邻接顶点
//返回v的（相对于w的）下一个邻接顶点，若w是v的最后一个邻接点，则返回空
	int i,j,k;
	if(!G.vexnum)//如果G的顶点数为0默认不存在
	 	return ERROR;//返回错误
 	i=LocateVex(G,G.vexs[v]);j=LocateVex(G,G.vexs[w]);//返回v与w两个值在表中的位置
	if(j==-1||i==-1||i==j){
		return ERROR;
	}
	for(k=j+1;k<G.vexnum;k++){
		if(G.arcs[i][k].adj!=INFINITY){
			return k;//返回k的值 
		}
	}  
	return ERROR;//输出错误	  
} 

Status InsertVex(MGraph &G,VertexType v)
//图G存在，v和图中顶点有相同特征
//在图G中增添新顶点v
{
	G.vexs[G.vexnum]=v;
	G.vexnum++;//图中的顶点数加一；
	return OK; 
 } 
Status DeleteVex(MGraph &G,VertexType v)
//图G存在，v是G中的某个顶点
//删除G中顶点v及其相关的弧
{
	int i,j;
	if(!G.vexnum)//如果顶点数为0
		return ERROR;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){//存在该点
		 for(j=0;j<G.vexnum;j++){
		 	G.arcs[i][j].adj=INFINITY;
		 	G.arcs[j][i].adj=INFINITY;//将所有与i相关的弧删除 
		 	G.arcnum-=1;
		 }
		 for(j=i;j<G.vexnum;j++){
		 	G.vexs[j]=G.vexs[j+1];//所有顶点向上移动，覆盖删除点的位置 
		 }
		 G.vexnum-=1;
		 return OK;//操作成功	
		}
	}
	return ERROR;//返回错误 不存在这个点	 
 } 
Status InsertArc(MGraph &G,VertexType v,VertexType w)
//图G存在，v和w是G中的两个顶点
//在图中增添弧<v,w>，若G是无向，则还增添对称弧<w,v>
{
	int i,j,k;
	i=LocateVex(G,v);j=LocateVex(G,w);//查找出v，w在图中的位置 
	if(G.kind==UDG){
		G.arcs[i][j].adj=G.arcs[j][i].adj=1;//有连接其信息置一 
		G.arcnum+=1;
		return OK;
	}
	if(G.kind==DG){
		G.arcs[i][j].adj=1;
		G.arcnum+=1;
		return OK;
	} 
	if(G.kind==DN){
		scanf("%d",&k);//输入权值
		G.arcs[i][j].adj=k;
		G.arcnum+=1;
		return OK; 
	}
	if(G.kind==UDN){
		scanf("%d",&k);//输入权值
		G.arcs[i][j].adj=k;
		G.arcs[j][i].adj=k;
		G.arcnum+=1;
		return OK;
		
	}
	return ERROR;
}
Status DeleteArc(MGraph &G,VertexType v,VertexType w)
//图G存在，v和w是G中两个顶点
//在G中删除<v,w>，若G是无向的，则还需删除对称弧<w,v>
{
	int i,j;
	if(!G.vexnum) return ERROR;
	i=LocateVex(G,v);j=LocateVex(G,w);//定位两个顶点在图中的位置 
	switch(G.kind){
		case DG:{
			G.arcs[i][j].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case DN:{
			G.arcs[i][j].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case UDG:{
			G.arcs[i][j].adj=G.arcs[j][i].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case UDN:{
			G.arcs[i][j].adj=G.arcs[j][i].adj=INFINITY;
			G.arcnum--;
			break;
		}
		default:return ERROR;
	}
	return OK; 
	}
void VisitFunc(VertexType v){
	printf("%d ",v);
}
void DFS(MGraph G,int v,bool *visited){
	int w; 
	visited[v]=1;
	VisitFunc(G.vexs[v]);//访问第v个顶点
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)){
		if(!visited[w]) DFS(G,w,visited);//对没有访问过的顶点调用DFS 
	} 
}
Status DFSTraverse(MGraph G){
//对图进行深度优先遍历。在遍历过程中，对每个顶点调用函数Visit一次，且仅一次
//一旦Visit（）失败，则操作失败
	int i;
	bool visited[G.vexnum];
	for(i=0;i<G.vexnum;++i){
		visited[i]=0;
	}
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]) DFS(G,i,visited);
	}
}
Status BFSTraverse(MGraph G){
	//进行广度优先搜索 
	int i,w,temp,u;
	bool visited[G.vexnum];
	LinkQueue Q;
	InitQueue(Q);//创建一个数组
	for(i=0;i<G.vexnum;i++) visited[i]=0;
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]){//i尚未被访问 
			visited[i]=1;
			VisitFunc(G.vexs[i]);
			EnQueue(Q,i);
			while(!QueueEmpty(Q)){//数组不为空 
				DeQueue(Q,u);
				for(w=FirstAdjVex(G,G.vexs[u]);w>=0;w=NextAdjVex(G,G.vexs[u],G.vexs[w]))
				{
					if(!visited[w]){
						visited[w]=1; VisitFunc(G.vexs[w]);
						EnQueue(Q,w);
					}//oif
				}//while
			} //if
		}
	} 
	
}

