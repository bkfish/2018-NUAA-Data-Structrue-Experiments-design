#include"information.h"
#include<fstream>
typedef char ElemType;
//控制所有在队列中的商铺信息，对商铺的整体进行修改 
typedef struct LNode{
	ElemType data;
	int lengths;
	struct LNode *next;
}LNode,*LinkList;
bool InitList_L(LinkList &l,int i){
	LNode *p; int j=0;
	l=NULL;
	if(i>MAXSIZE) return ERROR;
	for(j=0;j<i+1;j++){
		p=(LNode*)malloc(sizeof(LNode));
		p->next=l;
		l=p;
	}
	l->lengths=i;
	return OK;
}
bool DestroyTriplet(LinkList &L){
	LNode *p;
	if(L=NULL)
		return 0;
	while(L){
		p=L->next;
		free(L);
		L=p;
	}
	return 1;
}
bool ClearList(LinkList &L){
	LNode *p,*q;
	if(L=NULL)
	return 0;
	p=L->next;
	while(p!=NULL){
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL;
	return 1;
}
bool GetElem_L(LinkList &L,int i,ElemType&e){
	LNode *p=L->next;
	int j=0;
	while((p->next)&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i)
		return ERROR;
	e=p->data;
		return OK;
}
int LocateElem(LinkList L,ElemType e){
	LNode *p=L->next; 
	int j=1;
	while(p->data){
		if(e==p->data) return j;
		j++;
		p=p->next;
	}
	return 0;
}
bool PriorElem_L(LinkList L,ElemType cur_e,ElemType &pre_e){
	LNode *p,*q;
	int flag=0;
	p=L->next;
	if(cur_e==p->data) {
	printf("没有前值\n");
	return ERROR;
	}
	while(cur_e!=p->data){
		q=p;
		p=p->next;
	}
	pre_e=q->data;
	return OK;
}
bool NextElem_L(LinkList L,ElemType cur_e,ElemType &next_e){
	LNode *p;
	int j;
	p=L->next;
	for(j=0;j<L->lengths-1;j++){
		p=p->next;
	} 
	if(cur_e==p->data) printf("该值没有后值\n");
	p=L->next;
	while(p->data!=cur_e)
	p=p->next;
	next_e=p->next->data;
	return OK;
}
bool ListCreat(LinkList &L,int i,ElemType e){
	int j=0;
	LNode *p;
	p=L->next;
	for(j=0;j<i;j++){
		p=p->next;
	}
	p->data=e;
	return OK;
}
bool ListInsert(LinkList &L,int i,ElemType e){
	int j=0;
	LNode *p,*r,*q;
	r=(LNode*)malloc(sizeof(LNode));
	q=L;
	p=L->next;
	r->data=e;
	for(j=0;j<i-1;j++){
		q=p;
		p=p->next;
	}
	q->next=r;
	r->next=p;
	L->lengths++;
	return OK;
}
bool ListDelete_L(LinkList &L,int i,ElemType &e){
	LNode *p=L->next,*q; int j=0;
	while(p->next&&j<i-1){
		p=p->next;
		++i;
	}
	if(p->next||j>i-1) return ERROR;
	q=p->next; p->next=q->next;
	e=q->data;
	free(q);
	return OK;
}
void ListDatastore(LinkList &L)//对数据进行存储。从文件中读取
{
	fstream file;
	file.open("data.txt",ios::in|ios::out);
 } 
