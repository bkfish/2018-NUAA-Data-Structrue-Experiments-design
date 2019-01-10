#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	int x1, y1, x2, y2;
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
	int n, m;
	scanf("%d%d", &n, &m);
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->next = NULL;
	
	LNode *temp;
	for(int i=0; i<n; i++) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d%d%d%d", &temp->x1, &temp->y1, &temp->x2, &temp->y2);
		temp->data = i+1;
		temp->next = list->next;
		list->next = temp;
	}
	ListTraverse(list);
	
	int x, y;
	LNode *prior, *p;
	int flag;
	for(int i=0; i<m; i++) {
		scanf("%d%d", &x, &y);
		p = list->next;
		prior = list;
		flag = 0;
		while(p) {
			if(p->x1<=x && p->x2>=x && p->y1<=y && p->y2>=y) {
				// printf("%d %d %d %d\n", p->x1, p->y1, p->x2, p->y2);
				flag = p->data;
				prior->next = p->next;
				p->next = list->next;
				list->next = p;
				break;
			}
			else {
				prior = p;
				p = prior->next;
			}
		}
		if(flag) printf("%d\n", flag);
		else printf("IGNORED\n");
	}
	
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
} 






