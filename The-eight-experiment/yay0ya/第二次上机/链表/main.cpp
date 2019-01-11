#include"Linklist.h"
int main(){
	LinkList a,b;
	int n,m;
	cout<<"请输入a链表中数值的个数\n";
	cin>>n;
	Create(a,n);
	SortLink(a,n); 
	cout<<"请输入b链表中数值的个数\n";
	cin>>m;
	Create(b,m);
	SortLink(b,m);
	Intersection(a,n,b,m);
	return 0;
} 
