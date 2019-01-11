#include<iostream>
using namespace std;
#include<stdlib.h>
#define N 100
typedef struct LNode{
	int data;
	int count;
	struct LNode *next;
}LNode,*Linklist;
int main(){
	int Partition(int *p,int low,int high);
	void Qsort(int *p,int low,int high);
	void SortLink(Linklist &l,int n);
	int *p,n,low,high;
	Linklist l,q;
	int record,count=1;
	cin>>n;
	p=new int [n];
	for(int i=0;i<n;i++){
		cin>>p[i];
	}
	cout<<endl;
	Qsort(p,0,n-1);
	record=p[0];
	l=new LNode;
	l->data=p[n-1];
	l->count=1;
	for(int i=n-2;i>-1;i--){
		if(p[i]!=record){
			q=new LNode;
			q->next=l;
			l=q;
			l->data=p[i];
			l->count=0;
			record=p[i];
			count++;
		}
		if(p[i]==record){
			l->count++;
		}
	}
	SortLink(l,count);
	q=l->next;
	cout<<endl;
	for(int i=0;i<count;i++){
		printf("%d %d\n",q->data,q->count);
		q=q->next;
	}
	return 0;
	
}
void SortLink(Linklist &l,int n){
	LNode *head,*rear,*p,*pre,*q,*qre;
	head=new LNode;
	rear=new LNode;
	q=new LNode;
	qre=q; 
	int max;
	max=l->count;
	head->next=l;
	p=l;
	int i=0;
	while(i<n-1){
		p=p->next;
		i++;
	}
	p->next=rear;
	pre=head;
	p=head->next;
	while(head->next!=rear){
		while(p!=rear){
			if(p->count>max)
			max=p->count;
			pre=p;
			p=p->next;
		}
		pre=head;
		p=head->next;
		while(p!=rear){
			if(p->count==max){
				pre->next=p->next;
				q->next=p;
				q=p;
				break;
			}
			pre=p;
			p=p->next;	
		}
		max=head->next->count;
		pre=head;
		p=pre->next;	
	}
	l=qre;
}
int Partition(int *p,int low,int high){
	int record=low;
	int flag=p[low];
	while(low<high){
		while(low<high&&p[high]>=flag) 
			high--;
		p[low]=p[high];
		while(low<high&&p[low]<=flag) 
			low++;
		p[high]=p[low];
	}
	p[low]=flag;
	return low;
}
void Qsort(int *p,int low,int high){
	int record;
	if(low<high){
		record=Partition(p,low,high);
		Qsort(p,low,record-1);
		Qsort(p,record+1,high);
	}
}
