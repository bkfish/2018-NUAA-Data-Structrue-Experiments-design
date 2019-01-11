#include"BiTree.h"
Status Deletechild(BiTree T,BiTree &p){
	//二叉树存在，并删除p所指向结点的左右子树，并释放他们的空间
	SqStack S;
	InitStack(S);
	BiTNode *q;
	q=p->lchild;
	Push(S,q);
	while(!StackEmpty(S)){
		while(GetTop(S,q)&&q!=NULL){Push(S,q->lchild);}//向左走到尽头
		Pop(S,q);//空指针出栈 
		if(!StackEmpty(S)){
			Pop(S,q);
			free(q);
			Push(S,q->rchild);
		}
	}//while
	q=p->rchild;
	Push(S,q);
	while(!StackEmpty(S)){
		while(GetTop(S,q)&&q!=NULL){Push(S,q->lchild);}//向左走到尽头
		Pop(S,q);//空指针出栈 
		if(!StackEmpty(S)){
			Pop(S,q);
			free(q);
			Push(S,q->rchild);
		}
	}//while
	p->lchild=NULL;
	p->rchild=NULL;
	return OK; 
}
