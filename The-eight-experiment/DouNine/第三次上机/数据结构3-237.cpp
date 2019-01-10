#include<stdio.h>
#include<stdlib.h>

typedef struct DLNode {
	int data;
	DLNode *pre, *next;
}*DLinkList;

int main() {
	DLinkList dList = (DLNode*)malloc(sizeof(DLNode));
	dList->pre = dList->next = NULL;
	dList->data = 0;
	
	int n = 0;
	scanf("%d", &n);
	
	DLNode *temp, *p = dList;
	for(int i=0; i<n; i++) {
		temp = (DLNode*)malloc(sizeof(DLNode));
		temp->data = i+1;
		temp->pre = p;
		p->next = temp;
		p = temp;
	}
	p->next = NULL;
	DLNode *last = p;
	
	p = dList->next;
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	
	DLNode *pre = dList;
	p = dList->next;
	int i = 1;
	while(i<n) {
		if(i%2 == 0) {
			pre->next = p->next;
			if(p->next) p->next->pre = pre;
			
			p->next = last->next;
			last->next = p;
			p->pre = last;
			if(last->next) last->next->pre = p;
		}
		else pre = p;
		p = pre->next;
		i++;
	}
	
	p = dList->next;
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	
	p = dList;
	while(p) {
		temp = p;
		p = p->next;
		free(p);
	}
}


