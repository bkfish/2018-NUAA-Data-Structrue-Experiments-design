#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	LNode *next;
}LNode, *LinkList;

// 遍历函数
void ListTraverse(LinkList list) {
	printf("\n================遍历==============\n");
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("第%d位值为：%d\n", i, p->data); 
		p = p->next;
		i++;
	}
	printf("====================================\n\n");
}

// 在已排好序的链表中插入一个结点 
void InsertList(LinkList &list, LNode *temp) {
	LNode *prior = list, *p = list->next;
	while(p && p->data < temp->data) {
		prior = p;
		p = p->next;
	}
	prior->next = temp;
	temp->next = p;
} 

int main() {
	
	int n = 0;
	printf("请输入线性表的数据个数：");
	scanf("%d", &n);
	
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	list->next = NULL;
	
	// 输入数据 
	LNode *temp, *p = list;
	printf("请依次输入线性表中的数据：\n");
	int i = 0;
	while(i<n) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		p->next = temp;
		p = p->next;
		i++;
	} 
	p->next = NULL;
	ListTraverse(list);
	
	// 依次取出结点并插入已排序的链表 
	p = list->next;
	list->next = NULL;
	while(p) {
		temp = p;
		p = p->next;
		InsertList(list, temp);
	}
	ListTraverse(list);
	
	//销毁链表 
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
}




