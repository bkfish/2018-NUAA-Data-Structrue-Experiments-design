#include<stdio.h>
#include"LinkList.h"
bool reverseList_L(LinkList &L){
	LNode *p,*q,*s,*head,*end;
	p=L;
	q=(LNode*)malloc(sizeof(LNode));
	head=q;
	while(L->next!=NULL){
		p=L->next;
		s=L;
	while(p->next!=NULL){
		s=p;
		p=p->next;
	}
	s->next=NULL;
	q->next=p;
	q=q->next;
	}
	L=head;
	return OK;
}
int main(){
	LinkList l;
	int i=0,n=0,flag=0;
	char c,temp;

	printf("请输入你想在链表中添加的值的数量\n"); 
	scanf("%d",&n);
	InitList_L(l,n);
	getchar();
	printf("请输入你想录入的值\n"); 
	for(i=0;i<n;i++){
		scanf("%c",&c);
		ListCreat(l,i,c);	
		getchar();
	}
	ListTraverse(l);
	printf("请输入你想插入的值及其位置\n");
	scanf("%c%d",&c,&i);
	ListInsert(l,i,c);
	ListTraverse(l);
	printf("请输入你想得到值的位置\n");
	scanf("%d",&i);
	flag=GetElem_L(l,i-1,c);
	if(flag==-1) printf("输入位置错误\n");
	else
	printf("%c\n",c); 
	if(PriorElem_L(l,c,temp)==1)
	printf("它的前一个值是%c\n",temp);
	if(NextElem_L(l,c,temp))
	printf("它的后一个值是%c\n",temp);
	printf("请输入你想查找的值\n");
	getchar();
	scanf("%c",&c);
	i=LocateElem(l,c);
	printf("您想查找的值的位置在%d\n",i);
	printf("输出逆向元\n");
	reverseList_L(l);
	ListTraverse(l); 
	
}
