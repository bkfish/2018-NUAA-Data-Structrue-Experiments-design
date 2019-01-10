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
	
	
	// 开始递增合并操作
	LNode *pA = listA->next, *pB = listB->next;
	LNode *priorA = listA;
	while(pA && pB) {
		if(pA->data > pB->data) {
			priorA->next = pB;
			listB->next = pB->next;
			pB->next = pA;
			priorA = pB;
			pB = listB->next;
		}
		else {
			priorA = pA;
			pA = pA->next;
		}
	}
	if(pB) {
		priorA->next = pB;
		listB->next = NULL;
	}
	free(listB);
	
	
	// 开始倒置
	p = listA->next;
	listA->next = NULL;
	while(p) {
		temp = p;
		p = p->next;
		temp->next = listA->next;
		listA->next = temp;
	} 
	ListTraverse(listA);
	
	
	// 销毁链表 
	p = listA;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
} 





