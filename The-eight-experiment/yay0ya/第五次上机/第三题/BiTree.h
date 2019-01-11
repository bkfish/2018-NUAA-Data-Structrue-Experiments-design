#include<iostream>
using namespace std;
#include<stdlib.h>
#include"Stack.h"
Status Depth(BiTree T,int n,int depth){
		if(!T->lchild)//进行一个遍历。 
		Depth(T->lchild,n+1,depth);//如果左孩子不为空，进入，层数加一 
		if(!T->rchild)
		Depth(T->rchild,n+1,depth);
		if(depth<n)//如果其depth比当前n（代表此时的深度）小，则将此时深度赋给depth 
		depth=n;
	}
Status InitBiTree(BiTree &T){//创造一个空的二叉树 
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;
	T->rchild=NULL;
	if(!T) exit(0);
	return 1;
}
Status DestroyBiTree(BiTree &T){
	//销毁一个树
	free(T);
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
Status ClearBiTree(BiTree &T){
	//将二叉树清为空树
	if(T){
		T->lchild=NULL;
		T->rchild=NULL;
	}
	return 1;
} 
Status BiTreeEmpty(BiTree T){
	//若空返回1，不空返回0
	if(T->lchild||T->rchild) return 0;
	else return 1; 
}
Status BiTreeDepth(BiTree T){
	int depth=0;
	BiTree p;
	if(!T) return 0;
	p=T;
	Depth(p,0,depth);
	return depth;
}
BiTree Root(BiTree T){
	//如果二叉树T存在，返回T的根 
	BiTree p;
	if(!T) return p;
	else return T;
} 
Status Value(BiTree T,BiTNode e){	//是否需要判断e是否存在于T中？
	/*遍历，查找比对e*/
	BiTree p;
	if(!T) return 0;
	p=T;
	return e.data; 
}
	void find1(BiTree&T,BiTNode e,TElemType value){
		BiTNode*p;
		p=T;
		if(p->data==e.data) T->data=value;
		else{
		find1(p->lchild, e,value);
		find1(p->rchild, e,value);
	}
	}
Status Assign(BiTree T,BiTNode e,TElemType value){
	//二叉树T存在，e是T中的某个结点，结点e赋值为value
	if(!T) return 0;
	find1(T,e,value);
	return OK;
	
}
	Status find(BiTree T,BiTNode e,BiTNode**p){
		if(T->data==e.data){//经行查找操作，如果该结点与e相同，则返回这个e值 
			*p=T;
			return 1;   
		}
		else{
			find(T->lchild,e,p);
			find(T->rchild,e,p);
		}
	}
BiTNode* Parent(BiTree T,BiTNode e){
	//e如果是树中的非根结点，返回其的双亲。否则返回空
	BiTNode *p;
	if(!T){
	
	find(T,e,&p);
	return p;}
	else return 0;
	
} 
BiTNode LeftChild(BiTree T,BiTNode e){
	//非叶子结点，则返回左孩子，否额返回空
	BiTNode* p;
	find(T,e,&p);
	if(!p->lchild&&!p->rchild){
		p=NULL;
		return *p;
	}
	else
		return *p->lchild;
	
}
BiTNode Rightchild(BiTree T,BiTNode e){
	//非叶子结点，则返回右孩子，否则返回空
	BiTNode* p;
	find(T,e,&p);
	if(!p->lchild&&!p->rchild)	{
		p=NULL;
		return *p;
	}
	else
		return *p->rchild;
} 
void find(BiTree T,BiTNode e,BiTree &p){
		if(T==NULL){
			return;
		}
		else{
			if(T!=NULL){
				if(T->data==e.data){
					p=T;
				}
				find(T->lchild,e,p);
				find(T->rchild,e,p);	
			}
		}
	}
void findq(BiTree T,BiTNode e,BiTree &q){
	if(T==NULL){
		return;
	}
	else{
		if(T->lchild!=NULL&&T->lchild->data==e.data){
			q=T;
		}
		if(T->rchild!=NULL&&T->rchild->data==e.data){
			q=T;
		}
		findq(T->lchild,e,q);
		findq(T->rchild,e,q);
	}
}
BiTNode *LeftSibling(BiTree T,BiTNode e){
	//返回e的左兄弟。若e是T的左孩子，或者无左兄弟，则返回空
	BiTNode* p,*q;
	BiTNode* t=NULL;
	find(T,e,p);//q现在为该e结点的双亲结点。接下来判断e的位置
	findq(T,e,q);//找前驱 
	if(q->rchild==p){//e值为右结点，返回其左兄弟	 
			return q->lchild;//返回其的右兄弟； 
	}
	else{//结点是左孩子孩子，返回Error；
		return t; 
	}
	}
BiTNode *RightSibling(BiTree T,BiTNode e){
	//返回e的右兄弟。若e是T的右孩子，或者无右兄弟，则返回空
		BiTNode* p,*q;
	BiTNode* t=NULL;
	find(T,e,p);//q现在为该e结点的双亲结点。接下来判断e的位置
	findq(T,e,q);//找前驱 
	if(q->lchild==p){//e值为右结点，返回其左兄弟	 
			return q->rchild;//返回其的右兄弟； 
	}
	else{//结点是左孩子孩子，返回Error；
		return t; 
	}
}
Status InsertChild(BiTree&T,BiTNode *p,int LR,BiTree c){
	//二叉树存在，p指向t中的某个结点，LR为0或1，非空二叉树c与T不想交且右子树为空
	//根据LR为0或1插入c为T中所知的结点的左或右子树，p所指结点的原有的左子树和右子树
	//则成为c的子树
	BiTNode *temp; 
	if(LR==0){//插入T中所知的结点的左子树
		 if(p->lchild) temp=p->lchild;
		 p->lchild=c;
		 c->rchild=temp; 
		return OK;
	} 
	if(LR==1){//插入T中所知的结点的右子树
		temp=p->rchild;//用指针temp指向其将被代替的右子树（如果存在右子树） 
		p->rchild=c;//c插入到右子树
		c->rchild=temp;
		return OK; 
	}
}
Status DeleteChile(BiTree T,BiTree &p,int LR){
	//二叉树存在，p指向T中的某个结点，LR为0或1；
	//根据LR为0或1，删除T中p所指的左子树或右子树。
	
	if(LR==0){
		p->lchild=NULL;
	} 
	if(LR==1){
		p->rchild=NULL;
	}
	return OK; 
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
