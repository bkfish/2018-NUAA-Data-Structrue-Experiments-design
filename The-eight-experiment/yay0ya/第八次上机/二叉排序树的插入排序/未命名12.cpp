#include<iostream>
using namespace std;
typedef int BStype;
typedef struct BSNode{
	BStype data;
	struct BSNode *lchild;
	struct BSNode *rchild;//左右孩子 
}BSNode,*BiSTree;//构造二叉排序树的结点和树
int BFSearch(BiSTree T,BStype ch,BSNode *q,BSNode *temp)//进行搜索，找到适合的结点位置 ,返回结点指针 
{
	BSNode *p;
	p=T;
	if(p->data==ch)	{
		temp=p;//找到该值，将指针指向该值所在的位置
		return 1; 
	}
	if(p->data>ch){
		if(p->lchild==NULL){
			q=p;
			return 0;
		}
		BFSearch(p->lchild,ch,q,temp);
	}
	if(p->data<ch){
		if(p->rchild==NULL){
			q=p;//表示已经找到适合的结点位置可以进行插入 
			return 0;
		}
		BFSearch(p->rchild,ch,q,temp);
	}
}
bool InsertBiSTree(BiSTree &T){
	//创造一个二叉排序树
	BStype ch;
	BSNode *p,*temp,*q;
	cin>>ch;
	p=new BSNode;
	p->data=ch;
	p->lchild=NULL;
	p->rchild=NULL; 
	if(ch!=-1){
		if(!BFSearch(T,ch,q,temp)){
			
		if(ch>p->data){
			q->rchild=p;
		}
		if(ch<p->data){
			q->lchild=p;
		}
	}
	else{
		cout<<"该值已经存在\n"<<" "; 
		return 1;
	}
	}
	else
		return 0; 
} 
void InitBiStree(BiSTree &T){
	//创建头结点
	T=new BSNode;
	BStype ch;
	cin>>ch;
	T->data=ch;
	T->lchild=NULL;
	T->rchild=NULL; 
}
void DeleteBSNode(BiSTree &T){
	 
}
