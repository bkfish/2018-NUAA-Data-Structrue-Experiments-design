#include<iostream>
#include<stdlib.h>
using namespace std;

// 链式结点 
typedef struct LNode{
	int data;
	LNode *next;
}LNode, *LinkList;


//遍历函数
void ListTraverse(LinkList list) {
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("第%d位值为：%d\n", i, p->data); 
		p = p->next;
		i++;
	}
}
		
//初始化线性表 
bool InitList(LinkList &list, int num) {
	if(list = (LNode*)malloc(sizeof(LNode))) {
		list->data = 0;
		list->next = NULL;
		LNode *temp, *p=list;
		for(int i = 1; i <= num; i++) {
			temp = (LNode*)malloc(sizeof(LNode));
			temp->data = i;
			p->next = temp;
			p = temp;
			list->data++;
		}
		p->next = NULL;
		printf("================链式表倒置前===============\n");
		ListTraverse(list);
		return true;
	}
	else return false;
}

//销毁线性表
bool DestroyList(LinkList &list) {
	if(list) {
		LNode *temp, *p = list->next;
		while(p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		free(list);
		return true;
	}
	else return false;
}

//在线性表的第i位插入e值
bool ListInsert(LinkList &list, int i, LNode *e) {
	if(!list) return false;			//判断表是否为空  
	if(i <= 0 || i > list->data+1) return false;		//判断i是否有效
	
	LNode *last = list, *p = list->next;
	int j = 1;
	while(p && j++!=i) {							//优化
		last = p;
		p = last->next;
	}
	last->next = e;
	e->next = p;
	list->data++;
	return true;
}


int main() { 
	LinkList list;//顺序表头 
	
	int num;
	printf("请输入链式表元素的个数：");
	scanf("%d", &num);
	
	if(InitList(list, num)) printf("初始化链式表成功\n");
	else printf("初始化链式表失败\n");
	
	LNode *next = NULL, *p = list->next;
	list->data = 0;
	list->next = NULL;
	while(p) {
		next = p->next;
		if(!ListInsert(list, 1, p)) {
			printf("插值失败\n");
			break;
		}
		p = next;
	}
	
	printf("================链式表倒置后===============\n");
	ListTraverse(list);
	
	if(DestroyList(list)) printf("链表销毁成功\n");
	else printf("链表销毁失败\n"); 
}
