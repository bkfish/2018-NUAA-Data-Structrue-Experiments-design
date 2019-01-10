#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	LNode *next;
}*LinkList;

int main() {
	
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->next = NULL;
	
	int n = 0;
	//printf("«Î ‰»În£∫");
	scanf("%d", &n);
	
	LNode *temp, *p, *pre;
	int i; 
	for(i=0; i<n; i++) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		
		p = list->next;
		pre = list;
		while(p && p->data<temp->data) {
			pre = p;
			p = pre->next;
		}
		temp->next = p;
		pre->next = temp;
	}
	
	LNode *next;
	p = list->next;
	int account = 0;
	while(p) {
		next = p->next;
		if(next && (next->data - p->data)==1) account++;
		p = p->next;
	}
	printf("%d", account);
	
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
}
