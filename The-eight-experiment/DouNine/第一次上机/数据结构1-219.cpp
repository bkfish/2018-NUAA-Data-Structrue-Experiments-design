#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	LNode *next;
}LNode, *LinkList;

//遍历函数
void ListTraverse(LinkList list) {
	printf("\n================遍历==============\n");
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("第%d位值为：%d\n", i, p->data); 
		p = p->next;
		i++;
	}
}
		
int main() {
	// 初始化链表 
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	list->next = NULL;
	LNode *p, *temp;
	p = list;
	int i = 0;
	while(i<20) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = 2*i+4;
		p->next = temp;
		p = p->next;
		i++;
	}
	p->next = NULL;
	ListTraverse(list);
	
	// 输入上下界 
	int mink = 0, maxk = 0;
	printf("\n请分别输入mink、maxk:");
	scanf("%d%d", &mink, &maxk);
	
	// 开始删除元素
	LNode *prior;
	prior = list;
	p = list->next;
	while(p && p->data<=mink) {
		prior = p;
		p = p->next;
	} 
	temp = prior;
	while(p && p->data<maxk) {
		prior = p;
		p = p->next;
		free(prior);
	}
	temp->next = p;
	ListTraverse(list);
	
	//销毁链表 
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
}
