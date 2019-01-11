#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;
void Create(LinkList &l,int n){
	LNode *p;
	l=(LNode*)malloc(sizeof(LNode));
	for(int i=0;i<n;i++){
		p=(LNode*)malloc(sizeof(LNode));
		p->next=l;
		l=p;
	}
	p=l->next;
	cout<<"请输入该放入该链表的值\n"; 
	for(int i=0;i<n;i++){
		cin>>p->data;
		p=p->next;
	}
	p=NULL;
}
void SortLink(LinkList &l,int n){
	LNode *p,*q,*qre,*rear,*pre;//rear尾指针,pre前值的指针，head头指针 
	int min=l->next->data;
	int i=0;
	qre=(LNode*)malloc(sizeof(LNode));
	rear=(LNode*)malloc(sizeof(LNode));
	p=l->next;
	while(i<n-1){
		p=p->next;
		i++;
	}
	q=qre;
	p->next=rear;
	pre=l;
	p=l->next;
	while(l->next!=rear){
		while(p!=rear){
			if(p->data<min){
				min=p->data;
			}
			pre=p;
			p=p->next;
		}
		pre=l;
		p=l->next;
		while(p->data!=min){
			pre=p;
			p=p->next;
		}
		pre->next=p->next;
		q->next=p;
		q=p;
		min=l->next->data;
		pre=l;
		p=l->next;
	}
	q->next=rear;
	l=qre;
	q=l->next;
	while(q!=rear){
		cout<<q->data<<" ";
		q=q->next;
	}
	cout<<endl;
	rear->next=NULL;
} 
void Intersection(LinkList&a,int n,LinkList b,int m){
	LNode *pa,*pb,*prea,*preb,*c,*cp;;
	int i=0,max=0,flag=0;;
	c=(LNode*)malloc(sizeof(LNode));
	cp=c;
	if(n>m)
	max=n;
	else
	max=m;
	preb=b;
	prea=a;
	pa=a->next;
	pb=b->next;
	while(i<max){
		if(pa->data>pb->data){
			pb=pb->next;
		}
	
		if(pa->data==pb->data){
			cp->next=pa;
			cp=pa;	
			flag++;
			pb=pb->next;
		}
		if(pa->data<pb->data){
			pa=pa->next;
		}
		if(pa->next==NULL){
			break;
		}	
		if(pb->next==NULL){
			break;
		}
		i++;
	}
	i=0;
	cp=c->next;
	cout<<"输出并集\n"; 
	while(i<flag){
		cout<<cp->data<<" ";
		cp=cp->next; 
		i++;
	}
	
}
