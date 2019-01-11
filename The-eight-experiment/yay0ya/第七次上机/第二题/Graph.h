#include<iostream>
using namespace std;
#include"Stack.h"
#define MAX_VERTEX_NUM 20
typedef int InfoType;
typedef int VertexType;
typedef int Status; 
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;
}ArcNode;
typedef struct VNode{
	VertexType data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
	int kind;
}ALGraph;
Status Locatevex(ALGraph G,VertexType v1){
	for(int i=0;i<G.vexnum;i++){
		if(G.vertices[i].data==v1)
		return i;
	}
	 return -1;
}
Status CreateDG(ALGraph &G){
	int i,j,k;
	VertexType v1,v2;
	cout<<"输入顶点数 边数\n";
	cin>>G.vexnum;
	cin>>G.arcnum;
	cout<<"输入顶点的值\n";
	for(i=0;i<G.vexnum;i++){
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;//默认第一条边为空指针 指空 
	}
	cout<<"输入边两端的端点值（默认第一个是弧尾，第二个是弧头）\n";
	for(k=0;k<G.arcnum;k++){
		int flag=0;
		cin>>v1;
		cin>>v2;
		i=Locatevex(G,v1);
		j=Locatevex(G,v2);
		while(i==-1){
			cout<<"重新输入弧尾"<<endl;
			cin>>v1;
			i=Locatevex(G,v1);
		}
		while(j==-1){
			cout<<"重新输入弧头"<<endl;
			cin>>v2;
			j=Locatevex(G,v2);
		}
		ArcNode *p;
		if(G.vertices[i].firstarc==NULL)//如果这个第一条边的指针指向空 
			{
				p=new ArcNode;
				G.vertices[i].firstarc=p;
				p->adjvex=j; 
				p->nextarc=NULL;
				flag=1;
		}
		if(G.vertices[i].firstarc!=NULL&&flag==0){
			p=G.vertices[i].firstarc;
			while(p->nextarc!=NULL){
				p=p->nextarc;//一直走到最末尾 
			}
			ArcNode *q;
			q=new ArcNode;
			p->nextarc=q;
			q->adjvex=j;
			q->nextarc=NULL; 
		}
	}
	 
}//构造了有向图的链表 
Status CreateUDG(ALGraph &G){
	int i,j,k;
	VertexType v1,v2;
	cout<<"输入顶点数 边数"<<endl;
	cin>>G.vexnum;
	cin>>G.arcnum;
	cout<<"输入顶点的值"<<endl;
	for(i=0;i<G.vexnum;i++){
		cin>>G.vertices[i].data;
		G.vertices[i].firstarc=NULL;//默认第一条边为空指针 指空 
	}
	cout<<"输入边两端的端点值\n";
	for(k=0;k<G.arcnum;k++){
		cin>>v1;
		cin>>v2;
		i=Locatevex(G,v1);
		j=Locatevex(G,v2);
		while(i==-1){
			cout<<"重新输入v1"<<endl;
			cin>>v1;
			i=Locatevex(G,v1);
		}
		while(j==-1){
			cout<<"重新输入v2"<<endl;
			cin>>v2;
			j=Locatevex(G,v2);
		}
		ArcNode *p;
		if(G.vertices[i].firstarc==NULL)//如果这个第一条边的指针指向空 
			{
				p=new ArcNode;
				G.vertices[i].firstarc=p;
				p->adjvex=j; 
				p->nextarc=NULL;
		}
		if(G.vertices[i].firstarc!=NULL){
			p=G.vertices[i].firstarc;
			while(p->nextarc!=NULL){
				p=p->nextarc;//一直走到最末尾 
			}
			ArcNode *q;
			q=new ArcNode;
			p->nextarc=q;
			q->adjvex=j;
			q->nextarc=NULL; 
		}
		if(G.vertices[j].firstarc==NULL)
			{
				p=new ArcNode;
				G.vertices[j].firstarc=p;
				p->adjvex=i;
				p->nextarc=NULL;
			}
		if(G.vertices[j].firstarc!=NULL){
			p=G.vertices[j].firstarc;
			while(p->nextarc!=NULL){
				p=p->nextarc;
			}
			ArcNode *q;
			q=new ArcNode;
			p->nextarc=q;
			q->adjvex=i;
			q->nextarc=NULL;
			free(q);
		}
		free(p);	
	}
	 
}//构造了无向图的链表
Status FindInDegree(ALGraph G,int indegree[]){
	ArcNode *p;
	for(int i=0;i<G.vexnum;i++){
		p=G.vertices[i].firstarc;
		if(p!=NULL){
			while(p!=NULL){
				indegree[p->adjvex]++;
				p=p->nextarc;
			}
		}
	}
	return 1;
}
Status CreateGraph(ALGraph &G){
	cout<<"输入你想创建的图类型，1.有向图，2.无向图\n";
	int n;
	cin>>n;
	switch(n){
		case 1:CreateDG(G);break;
		case 2:CreateUDG(G);break;
		default:cout<<"输入错误，程序结束"<<endl;exit(0);
	} 
}
Status TopologicalSort(ALGraph G){
	int indegree[G.vexnum]={};
	FindInDegree(G,indegree);
	SqStack S;
	ArcNode *p;
	InitStack(S);
	for(int i=0;i<G.vexnum;i++){
		if(!indegree[i]) Push(S,i);
	}
	int count=0;
	int temp,k;
	while(!StackEmpty(S)){
		Pop(S,temp);
		cout<<G.vertices[temp].data<<" ";
		count++;
		for(p=G.vertices[temp].firstarc;p!=NULL;p=p->nextarc){
			k=p->adjvex;
			if(!(--indegree[k])) Push(S,k);
		}//for
	}//while
	if(count<G.vexnum) return -1;
	else return 1;
}//TopologicalSort
