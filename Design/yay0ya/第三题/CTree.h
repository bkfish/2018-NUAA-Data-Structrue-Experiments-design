#include<iostream>
using namespace std;
#include<string> 
#define MAX_TREE_SIZE 20
typedef char ElemType[50]; 
typedef int Status;
typedef struct CSNode{
	ElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;
void CreateTree(CSTree&T){
	T=new CSNode;
	T->data[1]=0;
	T->firstchild=NULL;
	T->nextsibling=NULL; 
}//创造一个孩子兄弟链表的树
void insertobject(CSTree &T){
	CSNode *p;
	p=new CSNode;
	p->firstchild=NULL;
	p->nextsibling=NULL;
	T->firstchild=p;
}
void insertonestring(CSTree &T){
	CSNode *p;
	p=new CSNode;
	p->firstchild=NULL;
	p->nextsibling=NULL;
	T->nextsibling=p; 
} 
