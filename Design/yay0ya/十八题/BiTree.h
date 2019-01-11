#include<iostream>
using namespace std;
#include<stdlib.h>
#define LH 1 //左高 
#define EH 0 //等高
#define RH -1 //右高 
typedef  int  ElemType;
#define FALSE 0
#define TRUE 1
typedef struct BSTNode{
	ElemType data;
	int bf;//结点的平衡因子
	struct BSTNode *lchild,*rchild; 
}BSTNode,*BSTree;

void R_Rotate(BSTree &p){
	//对以*p为根的二叉排序树进行右旋处理，处理之后p指向新的树根结点，既
	//旋转助理之前的左子树的根节点 
	BSTNode *lc;
	lc=p->lchild;//lc指向*p的左子树的根结点 
	p->lchild=lc->rchild;//lc的右子树挂接为*p的左子树
	lc->rchild=p;
	p=lc; //p指向新的结点 
	
}//R_Rotate

void L_Rotate(BSTree &p){
	//对以*p为根的二叉排序树作左旋处理，处理之后的p指向新的树根结点，既
	//旋转处理之前的右子树的根结点
	BSTNode *rc;
	rc=p->rchild;//rc指向的*p的右子树的根结点
	p->rchild=rc->lchild;//rc的左子树挂接为*p的右子树
	rc->rchild=p;p=rc;//p指向新的根节点 
} //L_Rotate

int EQ(ElemType e1,ElemType e2){
	if(e1==e2)
		return 1;
	else
		return 0;	
}

int LT(ElemType e1,ElemType e2){
	if(e1<e2)
		return 1;
	else 
		return 0;
}

void LeftBalance (BSTree &T){
	//对以指针T所指结点为根的二叉树做做左平衡旋转处理，本算法结束时候，指针T指向
	//新的根结点
	BSTNode *lc,*rd;
	lc=T->lchild;   //lc指向*T的左子树根结点 
	switch(lc->bf){		//检查*T的左子树的平衡度，并作相应平衡处理 
		case LH:			//新结点插入在*T的左孩子的左子树上，要作单右旋处理 
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH:	//新结点插入在*T的左孩子的右子树上，要作双旋处理 
			rd=lc->rchild;//rd指向*T的左孩子的右子树根
			switch(rd->bf){
				case LH:
					T->bf=RH;
					lc->bf=EH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=EH;
					lc->bf=LH;
					break;		
			}//switch(rd->bf)
			rd->bf=EH;
			L_Rotate(T->lchild);  //对*T的左子树作左旋平衡处理
			R_Rotate(T);		  //对*T作右旋平衡处理 
	}//switch(lc->bf) 
}//LeftBalance

void RightBalance(BSTree &T){
	//对以指针T所指结点为根的刹儿出，做右平衡旋转处理，本算法结束的时候，指针T指向
	//新的根节点
	BSTNode *rc,*ld;
	rc=T->rchild;		//rc指向*T的右子树根节点
	switch(rc->bf){     //检查*T的右子树的平衡度，并作相应的平衡处理 
		case LH:		//新结点插入在*T的右孩子的左子树上，要作双旋处理
			ld=rc->lchild;	// ld指向*T的右孩子的左子树根
			switch(ld->bf){
				case LH:
					T->bf=EH;
					rc->bf=RH;
					break;
				case EH:
					T->bf=rc->bf=EH;
					break;
				case RH:
					T->bf=LH;
					rc->bf=EH;
					break;//	
			}//switch(ld->bf)
			ld->bf=EH;
			R_Rotate(T->rchild);	//对*T的右子树进行右旋平衡处理 
			L_Rotate(T);		 //对T进行左旋平衡处理 
	} 
}

int InsertAVL(BSTree &T,ElemType e,bool &taller){
	//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素
	//为e的新节点，并返回1，否则返回0.若因插入而使二叉排序树失去平衡，则作平衡
	//旋转处理，布尔变量taller反映T长高与否
	if(T==NULL){
		//插入新节点，树“长高”，置taller为TRUE
		T=new BSTNode;
		T->data=e;
		T->lchild=T->rchild=NULL; 
		T->bf=EH; 
		taller=TRUE;
	} 
	else{
		if(EQ(e,T->data)){    //树中已经存在和e有相同关键字的结点 
			taller=FALSE;	  //不再进行插入 
			return 0;		 
		}
		if(LT(e,T->data)){	//则继续在*T的左子树中进行搜索 
			if(!InsertAVL(T->lchild,e,taller)) return 0;//未插入
			if(taller){					//已插入到*T的左子树中且左子树长高 
				switch(T->bf){		//检查*T的平衡度 
					case LH:		//原本左子树比右子树高，需要做左平衡处理 
						LeftBalance(T);
						taller=FALSE;
						break;
					case EH:		//原本左右子树等高，现因左子树增高而使树增高 
						T->bf=LH;
						taller=TRUE;
						break;
					case RH:		//原本右子树比左子树高，现，左右子树等高 
						T->bf=EH;
						taller=FALSE;
						break;		
				}//switch(T->bf) 
			}	
		}//if
		else { //应继续在*T的右子树中进行搜索 
			if(!InsertAVL(T->rchild,e,taller)) return 0;//未插入 
			if(taller)
				switch(T->bf){
					case LH:
						T->bf=EH;
						taller=FALSE;
						break;
					case EH:
						T->bf=RH;
						taller=TRUE;
						break;
					case RH:
						RightBalance(T);
						taller=FALSE;
						break;	
				}//swich(T->bf)
		}//else 
	}//else
	return 1;
} //InsertAVL

int DeleteAVL(BSTree &T,ElemType e,bool &shorter){
	//若在平衡的二叉排序树T中存在和e有相同关键字的结点，则删除这个元素
	//并返回1，否则返回0；若因删除而使二叉排序树失去平衡，则作平衡
	//旋转处理，布尔变量，shorter反映树变短与否 
	if(T==NULL){
		return 0;//不存在这个平衡树 
	}
	else{
		if(EQ(e,T->data))  //找到这个元素，开始进行删除操作
		{
			BSTNode *p=NULL;
			if(T->lchild==NULL){
				//如果左子树为空
				p=T;//则将p指向要删除的结点 
				T=T->rchild;//该结点指向自己的右子树，将右子树与他的父节点相联 
				free(p); 
				shorter=TRUE;
			}
			else if(T->rchild==NULL){
				//如果它的右子树为空
				p=T;
				T=T->lchild;
				free(p);
				shorter=TRUE; 
			}
			else{
				//如果左右子树都存在
				p=T->lchild;
				while(p->rchild!=NULL){
					p=p->rchild;
				} 
				T->data=p->data;
				DeleteAVL(T->lchild,p->data,shorter);//在左子树中递归删除前驱结点 
			}
			}//如果找到这个结点的 
			else if(e<T->data)//这个结点值比现在所指的值要小，进入左子树查找
			{
				if(!DeleteAVL(T->lchild,e,shorter)){
					return FALSE;
				}
				if(shorter){
					switch(T->bf){
						case LH:
							T->bf=EH;
							shorter=TRUE;
							break;
						case EH:
							T->bf=RH;
							shorter=FALSE;
							break;
						case RH:
							RightBalance(T);
							if(T->rchild->bf==EH){
								shorter=FALSE;
							}
							else 
								shorter=TRUE;
								break;	
					}
				}
			 }
			 else{
			 	//进入右子树查找
				 if(!DeleteAVL(T->rchild,e,shorter))
				 	return FALSE;
					 if(shorter){
					 	switch(T->bf){
					 		case LH:
					 			LeftBalance(T);//进行左平衡处理
								 if(T->lchild->bf==EH){
								 	shorter=FALSE;
								 } 
								 else shorter=TRUE;
								 break ;
							case EH:
								T->bf=LH;
								shorter=FALSE;
								break;
							case RH:
								T->bf=EH;
								shorter=TRUE;
								break;
						 }//switch(T->bf)
					 }//if 
			 } 
		 } 
		 	return 1;
	}
 

void InOrderTraverse(BSTree T){
	if(T){
		InOrderTraverse(T->lchild);
		cout<<T->data<<" ";
		InOrderTraverse(T->rchild);
	}
}
