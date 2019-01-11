#include<stdlib.h>
#include"Stack.h"

typedef BiTNode* QElemType;
typedef int Status; 
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针 
}LinkQueue;
//---基本操作的算法描述（部分）--- 
Status InitQueue(LinkQueue &Q){
	//构造一个空队列Q
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(0);
	Q.front->next=NULL;
	return 1; 
} 
Status DestroyQueue(LinkQueue &Q){
	//销毁队列Q
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return 1; 
}
Status ClearQueue(LinkQueue &Q){
	//将Q清为空队列
	QNode *p;
	p=Q.front; 
	while(Q.front!=Q.rear){
		p=p->next;
		Q.front=p;
		free(p); 
	} 
	Q.front->next=NULL;
	return 1;
}
Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear) return 1;
	else return 0;
}
int QueueLength(LinkQueue Q){
	QNode *p;
	int i=0;
	if(Q.front==Q.rear) return 0;
	p=Q.front->next;
	while(p!=Q.rear){
		i++;
		p=p->next;
	} 
	i++;
	return i;
}
Status GetHead(LinkQueue Q,QElemType &e){
	//若队列不为空，则用e返回Q的队头元素，并返回1，否则返回0
	if(Q.front==Q.rear) return 0;
	e=Q.front->next->data;
	return 1; 
}
Status EnQueue(LinkQueue &Q,QElemType e){
	//插入元素e为Q的新的队尾元素
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(0);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return 1; 
}
Status DeQueue(LinkQueue &Q,QElemType &e){
	//若队列不为空，则删除Q的队头元素。用e返回其值，并返回OK；
	//否则返回ERROR；
	QueuePtr p,q;
	p=Q.front->next;
	if(Q.front==Q.rear) return 0;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return 1;
}
void visited(int q){
	cout<<q<<" ";
}

