#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 顺序表头 
typedef struct {
	int *head;
	int length;
}SqList;

// 指针结点 
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode,*LinkList;


int main() {
	
	int m = 0, n = 0; 
	printf("请依次输入n、m:\n");
	scanf("%d%d", &n, &m); 
	
	printf("\n============顺序结构实现==============\n");
	// 定义顺序链表
	SqList List;
	List.head = (int*)malloc(sizeof(int) * n);
	List.length = n;
	 
	// 初始化数组值 
	int i = 0;
	while(i < n) {
		List.head[i] = i+1;
		i++;
	}
	
	// 进行数组元素出列 
	i = 0;
	int num = 1;
	while(List.length) {
		if(List.head[i%n]) {
			if(num%m == 0) {
				printf("第%d号出列\n", List.head[i%n]);
				List.head[i%n] = 0;
				List.length--;
			}
			num++;
		}
		i++;
	}
	
	// 释放空间 
	free(List.head);
	
	
	
	printf("\n============链式结构实现==============\n");
	// 定义链表 
	LinkList head;
	// 定义使用到的指针 
	LNode *p, *temp;
	// 创建头结点 
	head = (LNode*)malloc(sizeof(LNode));
	head->data = n;
	
	// 创建链表，并为每个结点设立数值 
	p = head;
	i = 0;
	while(i++ < n) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i;
		p->next = temp;
		p = p->next;
	}
	p->next = NULL;
	
	// 进行链表元素出列
	num = 1;
	LNode *last = head;
	while(head->data) {
		if(!(last->next)) last = head;
		p = last->next;
		if(num%m == 0) {
			printf("第%d号出列\n", p->data);
			head->data--;
			last->next = p->next;
			free(p);
		}
		else last = last->next;
		num++;
	} 
	
	// 释放头结点
	free(head); 
}


