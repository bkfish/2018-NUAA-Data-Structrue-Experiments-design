#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*Linklist;
bool InitList_L(Linklist &l,int i){
	LNode *p; int j=0;
	l=NULL;
	for(j=0;j<i+1;j++){
		p=(LNode*)malloc(sizeof(LNode));
		p->next=l;
		l=p;
	}
}//创造一个链表
int main(){
	cout<<"请输入一个n值\n";
	int n;
	int flag=0;
	cin>>n;
	Linklist l;
	LNode *p;
	InitList_L(l,n);
	p=l->next;
	for(int i=0;i<n;i++){
		cin>>p->data;
		p=p->next;
	} 
	LNode *q;
	q=l->next;
	p=q->next;
	for(int i=1;i<n-1;i++){
		if(p->data<q->data&&p->data<p->next->data)	
			flag++;
		if(p->data>q->data&&p->data>p->next->data)
			flag++;
		q=p;
		p=p->next;	
	}
	cout<<flag;
	return 0;
}
