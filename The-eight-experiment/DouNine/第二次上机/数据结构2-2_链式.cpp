#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	LNode *next;
}*LinkList;

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
	printf("==================================\n\n");
};

int main() {
	
	// 初始化 
	LinkList listA = (LNode*)malloc(sizeof(LNode));
	listA->next = NULL;
	LinkList listB = (LNode*)malloc(sizeof(LNode));
	listB->next = NULL;
	printf("请输入A、B线性表中元素个数：");
	scanf("%d%d", &listA->data, &listB->data);
	
	LNode *p, *temp;
	printf("\n请递增有序输入A线性表中的数据：");
	p = listA;
	for(int i=0; i<listA->data; i++) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		p->next = temp;
		p = p->next;
	}
	p->next = NULL;
	//ListTraverse(listA);
	
	printf("请递增有序输入B线性表中的数据：");
	p = listB;
	for(int i=0; i<listB->data; i++) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		p->next = temp;
		p = p->next;
	}
	p->next = NULL;
	//ListTraverse(listB);
	
	
	// 将B、C取交集 
	LNode *pA = listA->next, *pB = listB->next;
	LNode *priorA = listA, *priorB = listB;
	while(pA && pB) {
		if(pA->data == pB->data) {
			priorB->next = pB->next;
			free(pB);
			pB = priorB->next;
			
			priorA = pA;
			pA = priorA->next;
		}
		else if(pA->data < pB->data) {
			priorA->next = pA->next;
			free(pA);
			pA = priorA->next;
		}
		else {
			priorB->next = pB->next;
			free(pB);
			pB = priorB->next;
		}
	}
	while(pA) {
		temp = pA;
		pA = pA->next;
		free(pA);
	}
	priorA->next = NULL;
	printf("取交集结束:\n");
	ListTraverse(listA);
	
	
	// 销毁链表 
	p = listA;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	
	p = listB;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
} 





