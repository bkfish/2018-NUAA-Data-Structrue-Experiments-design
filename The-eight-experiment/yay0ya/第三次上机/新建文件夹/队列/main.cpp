#include <iostream>
using namespace std;
#include"Queue.h"
int main() {
	LinkQueue q;
	InitQueue(q);
	int n,i,elem;
	cout<<"create a queue"<<endl;
	cout<<"input a queue number"<<endl;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>elem;
		EnQueue(q,elem);
	}
	cout<<"the length of queue is"<<QueueLength(q)<<endl;
	cout<<"delete one number the number is"<<endl;
	DeQueue(q,elem);
	cout<<elem<<endl;
	cout<<"the length of queue is"<<QueueLength(q)<<endl; 
	cout<<"now the head of queue is";
	if(GetHead(q,elem))
	cout<<elem<<endl;
	else{
		cout<<"no head"<<endl; 
	}
	cout<<"Traversequeue"<<endl;
	QueueTraverse(q);
}
