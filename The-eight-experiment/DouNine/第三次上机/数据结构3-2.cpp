#include <stdio.h>
#include <stdlib.h>

typedef struct QNode{
	int data;
	struct QNode *next;
}*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue &Q) {
	Q.front = (QNode*)malloc(sizeof(QNode));
	Q.rear = Q.front;
}

void ClearQueue(LinkQueue &Q) {
	QNode *p = Q.front->next, *temp;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	Q.rear = Q.front;
}

void DestoryQueue(LinkQueue &Q) {
	ClearQueue(Q);
	free(Q.front);
}

bool QueueEmpty(LinkQueue Q) {
	if(Q.front == Q.rear) return true;
	else return false;
}

int QueueLength(LinkQueue Q) {
	QNode *p = Q.front->next;
	int account = 0;
	while(p) {
		account++;
		p = p->next;
	}
	return account;
}

bool GetHead(LinkQueue Q,int &e) {
	QNode *p = Q.front->next;
	if(p) {
		e = p->data;
		return true;
	}
	else return false;
}

void EnQueue(LinkQueue &Q,int e) {
	QNode *temp = (QNode*)malloc(sizeof(QNode));
	temp->data = e;
	temp->next = NULL;
	Q.rear->next = temp;
	Q.rear = temp;
}

bool DeQueue(LinkQueue &Q,int &e) {
	QNode *p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	free(p);
}

void QueueTraverse(LinkQueue Q) {
	printf("=================遍历队列==================\n");
	QNode *p = Q.front->next;
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n===========================================\n");
}

int main() {
	LinkQueue Q;
	InitQueue(Q);
	printf("队列初始化成功\n");
	
	for(int i=0; i<10; i++) {
		EnQueue(Q, i);
	}
	QueueTraverse(Q);
	
	int temp = 0;
	DeQueue(Q, temp);
	printf("删去队头元素\n");
	QueueTraverse(Q);
	
	GetHead(Q, temp);
	printf("队列头元素为：%d\n", temp);
	
	EnQueue(Q, temp);
	printf("在队尾加入%d\n", temp);
	QueueTraverse(Q);
	
	DestoryQueue(Q);
	printf("队列销毁成功\n");
} 




