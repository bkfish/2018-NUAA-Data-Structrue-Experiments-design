#include"Queue.h"
#define MAX_NODE 100
#define OK 1
#define ERROR 0
Status InitBiTree(BiTree &T){//创造一个空的二叉树 
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;
	T->rchild=NULL;
	if(!T) exit(0);
	return 1;
}
void createBiTree(BiTree&T){	
	TElemType c;
	cin>>c;
	if(c==-1){
		T=NULL;
	}
	else{
		T= new BiTNode;
		T->data=c;
		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}
}
bool Visit(TElemType e){
	cout<<e<<" ";
	return 1;
}
Status PreOrderTraverse(BiTree T){
	if(T){
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild))
				if(PreOrderTraverse(T->rchild)) return OK;
		return ERROR;		
	}
	else return OK;
}
Status InOrderTraverse(BiTree T){
	//中序遍历T
	if(T){
		if(InOrderTraverse(T->lchild))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild)) return OK;
		return ERROR;		 
	
	}
	else
		return OK;
}
Status PostOrderTraverse(BiTree T){
	//后序遍历T
	if(T){
		if(PostOrderTraverse(T->lchild))
			if(PostOrderTraverse(T->rchild))
				if(Visit(T->data)) return OK;
		return ERROR;		
	} 
	else return OK;
}
Status LevelOrderTraverse(BiTree T){
	//层序遍历T
	LinkQueue Q;
	BiTNode *p;
	InitQueue(Q);
	EnQueue(Q,T);
	while(!QueueEmpty(Q)){
		DeQueue(Q,p);
		cout<<p->data<<" ";
		if(p->lchild!=NULL){
			EnQueue(Q,p->lchild);
		}
		if(p->rchild!=NULL){
			EnQueue(Q,p->rchild);
		}
	}
}
void visitfunc(TElemType i){
	cout<<i<<" ";
}
Status InOrderTraverse2(BiTree T){
	SqStack S;
	InitStack(S);
	BiTNode *p;
	Push(S,T);
	while(!StackEmpty(S)){
		while(GetTop(S,p)&&p!=NULL){Push(S,p->lchild);}//向左走到尽头
		Pop(S,p);//空指针出栈 
		if(!StackEmpty(S)){
			Pop(S,p);
			visitfunc(p->data);
			Push(S,p->rchild);
			}

		 
	}//while
	return OK;
}
Status PreOrderTraverse2(BiTree T){
	SqStack S;
	InitStack(S);
	BiTNode *p;
	Push(S,T);
	while(!StackEmpty(S)){
		while(GetTop(S,p)&&p!=NULL){visitfunc(p->data);Push(S,p->lchild); }//向左走到尽头
		Pop(S,p);//空指针出栈 
		if(!StackEmpty(S)){
			Pop(S,p);
			Push(S,p->rchild);
			}

		 
	}//while
	return OK;
}
Status PostOrderTraverse2(BiTree T){
	SqStack S;
	InitStack(S);
	BiTNode *p,*q;//p设置为当前访问结点，q设置为该结点的前驱 
	if(T==NULL){
		return 0;
	}
	p=T;
	q=NULL;
	while(p!=NULL){
		Push(S,p);
		p=p->lchild;//一直进入最左边的结点 
	}
	while(!StackEmpty(S))//栈不空 
	{
		Pop(S,p);
		if(p->rchild==NULL||p->rchild==q){
			cout<<p->data<<" ";
			q=p;
		}
		else{
			Push(S,p);
			p=p->rchild;
			while(p!=NULL){
				Push(S,p);
				p=p->lchild;
			}
		}
		
	 }
	 return OK; 
}
bool countleaf(BiTree T,int &count){
	if(T){
		if(T->lchild==NULL&&T->rchild==NULL)
			count++;
		

		if(countleaf(T->lchild,count))
			if(countleaf(T->rchild,count)) return 1;
		else 0;
	}
	return 1;
}
int Depth(BiTree T){
	int depthright=0,depthleft=0,depthval=1;
	if(T==NULL) depthval=0;
	else{
		depthleft=Depth(T->lchild);
		depthright=Depth(T->rchild);
		depthval=1+((depthleft>depthright)?depthleft:depthright);
	}
	return depthval;
}
int counthight(BiTree T,TElemType data){
	if(T==NULL) return 0;
	SqStack S;
	InitStack(S);
	BiTNode *p;
	p=T;
	Push()
}
