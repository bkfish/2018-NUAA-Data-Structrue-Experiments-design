#include<iostream>
using namespace std;
#include"stack.h"
int main(){
	SqStack s;
	int i,n;
	InitStack(s);
	cout<<"判断栈是否为空\n";
	if(StackEmpty(s)) cout<<"是"<<endl;
	else cout<<"不是"<<endl;
	cout<<"input one number of stack"<<endl;
	cin>>n;
	for(int j=0;j<n;j++){
		cin>>i;
		Push(s,i);
	}
	cout<<"the top number of the stack is";
	GetTop(s,i);
	cout<<i<<endl;
	i=StackLength(s);
	cout<<"the length of stack is"<<i<<endl;
	Pop(s,i);
	cout<<"pop one number,the number is"<<i<<endl;
	i=StackLength(s);
	cout<<"the top number of the stack is";
	GetTop(s,i);
	cout<<"now the length of stack is"<<i<<endl;
	ClearStack(s);
	cout<<"clear the stack"<<endl; 
	i=StackLength(s);
	cout<<"now the length of stack is"<<i<<endl;
	DestroyStack(s);
	cout<<"DestroyStack"<<endl;
	Traverse(s);	 
}
