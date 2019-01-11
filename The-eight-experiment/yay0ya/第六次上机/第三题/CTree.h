#include<iostream>
#include"stack.h"
using namespace std;
#define MAX_TREE_SIZE 20
typedef int ElemType; 
typedef int Status;
typedef struct CSNode{
	ElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;
void CreateTree(CSTree&T){
	int c;
	cin>>c;
	if(c==-1)
		T=NULL;
	else{
		T=new CSNode;
		T->data=c;
		CreateTree(T->nextsibling);
		CreateTree(T->firstchild);
	}
}//创造一个孩子兄弟链表的树
void DFSearch(CSTree T,SqStack &S){
	if(T==NULL){
		return;
	}
	else{
		if(T->firstchild!=NULL){
			int i;
			Pop(S,i);
			i++;
			Push(S,i);
			DFSearch(T->firstchild,S);
		}
		if(T->nextsibling!=NULL){
			int i;
			Pop(S,i);
			Push(S,i);
			Push(S,i);
			DFSearch(T->nextsibling,S);
		}
	}
} 
