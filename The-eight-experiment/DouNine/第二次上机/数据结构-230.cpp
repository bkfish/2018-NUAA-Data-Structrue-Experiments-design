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
	LinkList listC = (LNode*)malloc(sizeof(LNode));
	listC->next = NULL;
	printf("请输入A、B、C线性表中元素个数：");
	scanf("%d%d%d", &listA->data, &listB->data, &listC->data);
	
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
	
	printf("请递增有序输入C线性表中的数据：");
	p = listC;
	for(int i=0; i<listC->data; i++) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		p->next = temp;
		p = p->next;
	}
	p->next = NULL;
	//ListTraverse(listC);
	
	
	// 将B、C取交集，并将结果放在B中 
	LNode *pB = listB->next, *pC = listC->next;
	LNode *priorB = listB, *priorC = listC;
	while(pC && pB) {
		if(pB->data == pC->data) {
			priorB = pB;
			pB = priorB->next;
			priorC = pC;
			pC = priorC->next;
		}
		else if(pB->data < pC->data) {
			priorB->next = pB->next;
			free(pB);
			pB = priorB->next;
		}
		else {
			priorC = pC;
			pC = priorC->next;
		}
	}
	while(pB) {
		temp = pB;
		pB = pB->next;
		free(pB);
	}
	priorB->next = NULL;
	printf("B、C取交集结束:\n");
	ListTraverse(listB);
	
	
	// 在A中，删去存在于B、C交集中的数
	LNode *pA = listA->next, *priorA = listA;
	pB = listB->next, priorB = listB; 
	while(pA && pB) {
		if(pA->data == pB->data) {
			priorA->next = pA->next;
			free(pA);
			pA = priorA->next;
		}
		else if(pA->data > pB->data) {
			priorB = pB;
			pB = priorB->next;
		}
		else {
			priorA = pA;
			pA = priorA->next;
		}
	}
	printf("A删去交集结束:\n");
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
	p = listC;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
} 





