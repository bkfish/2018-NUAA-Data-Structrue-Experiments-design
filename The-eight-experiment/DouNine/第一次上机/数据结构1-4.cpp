#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	LNode *next;
}*LinkList, LNode;

//在pos位置插入e 
bool insertLinkList(LinkList &list, int pos, LNode *e){
	if(pos>list->data+1 || pos<=0) return false;
	
	int i = 1;
	LNode *p = list->next, *prior = list;
	while(p && i<pos){
		prior = p;
		p = prior->next;
		i++;
	}
	prior->next = e;
	e->next = p;
	list->data++;
	return true;
}

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
}

int main(){
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	
	//初始化 
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	LNode *temp, *p = list;
	for(int i=0; i<n; i++){
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i+1;					//将学号赋给结点的数据域 
		p->next = temp;
		p = p->next;
		list->data++;
	}
	p->next = NULL;
	ListTraverse(list);
	
	//开始排队 
	int num = 0, pos = 0;
	int j = 0;
	LNode *prior = NULL;
	for(int i=1; i<=m; i++){
		scanf("%d%d", &num, &pos);
		p = list->next;
		prior = list;
		j = 1;
		while(p){
			if(p->data == num){				//找到等于该学号的结点 
				prior->next = p->next;		//将该结点取出 
				list->data--;
				if(!insertLinkList(list, j+pos, p)) {	//再将该结点插入新位置 
					printf("insert error!\n");
				}
			}
			prior = p;
			p = prior->next;
			j++;
		} 
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
