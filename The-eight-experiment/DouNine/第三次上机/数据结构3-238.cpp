#include<stdio.h>
#include<stdlib.h>

typedef struct DLNode {
	int data, freq;
	DLNode *pre, *next;
}*DLinkList;

bool locate(DLinkList dList, int num) {
	DLNode *pre = dList, *p = dList->next;
	while(p&&p->data!=num) {
		pre = p;
		p = pre->next;
	}
	if(p) {
		p->freq++;
		pre->next = p->next;
		if(p->next) p->next->pre = pre;
		DLNode *temp = p;
		
		pre = dList, p = dList->next;
		while(p&&p->freq>temp->freq) {
			pre = p;
			p = pre->next;
		}
		pre->next = temp;
		temp->next = p;
		
		p->pre = temp;
		temp->pre = pre;
		
		return true;
	}
	else return false;
}

int main() {
	DLinkList dList = (DLNode*)malloc(sizeof(DLNode));
	dList->pre = dList->next = NULL;
	dList->data = 0;
	
	int n = 0;
	printf("请输入链表长度：");
	scanf("%d", &n);
	
	DLNode *temp, *p = dList;
	for(int i=0; i<n; i++) {
		temp = (DLNode*)malloc(sizeof(DLNode));
		temp->data = i+1;
		temp->freq = 0;
		temp->pre = p;
		p->next = temp;
		p = temp;
	}
	p->next = NULL;
	DLNode *last = p;
	
	p = dList->next;
	while(p) {
		printf("data=%d, freq=%d  ", p->data, p->freq);
		p = p->next;
	}
	printf("\n");
	
	
	int i = 0, num = 0;
	printf("请输入依次十个点击的序号：\n");
	while(i<10) {
		scanf("%d", &num);
		if(!locate(dList, num)) printf("不存在这个数：%d\n", num);
		i++;
		
		p = dList->next;
		while(p) {
			printf("data=%d, freq=%d  ", p->data, p->freq);
			p = p->next;
		}
		printf("\n");
	} 
	
	
	p = dList;
	while(p) {
		temp = p;
		p = p->next;
		free(p);
	}
}


