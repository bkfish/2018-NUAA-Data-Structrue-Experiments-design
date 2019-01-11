#include"BiTree.h"
Status EQ(TElemType data,TElemType key){
	if(data==key) return 1;
	else return 0;
}
Status LT(TElemType data,TElemType key){
	if(data<key) return 1;
	else return 0;
}
Status SearchBST(BiTree T,TElemType key,BiTree f,BiTree &p){
	if(T==NULL) {
		p=f;
		return 0; 
	}
	else if(EQ(key,T->data))//如果key值比T->data的值小 
		{
			p=T;
			return 1;
	}		
	else if(LT(key,T->data)) return SearchBST(T->lchild,key,T,p);
	else return SearchBST(T->rchild,key,T,p); 
}//SearchBST
Status InsertBST(BiTree &T,TElemType e){
	BiTNode *s;
	BiTNode *p;//p指针，指向访问路径上的最后一个结点，f指向双亲 
	if(!SearchBST(T,e,NULL,p)){//树中不存在该值 
		s=new BiTNode;
		s->data=e;
		s->lchild=NULL;
		s->rchild=NULL;
		if(p==NULL) T=s;
		else if(LT(e,p->data))
		p->lchild=s;
		else p->rchild=s;
		return 1;
	}
	else return 0;
}
Status DeleteT(BiTree &p) {
	BiTNode *q,*s;
	if(p->rchild==NULL){//如果右孩子为空，则删除该结点时，前驱指向结点的左孩子 
		q=p;
		p=p->lchild;
		free(q);
	}
	else if(p->lchild==NULL){//左孩子为空，前驱指向右孩子 
		q=p;
		p=p->rchild;
		free(q);
	}
	else{//左右孩子皆不为空 
		q=p;s=p->lchild;//q指向该结点，s指向该结点的左孩子 
		while(s->rchild!=NULL){//如果s的右孩子不为空 
			q=s;//q指向前驱，s一直指向右孩子的末尾 
			s=s->rchild;
		}
		p->data=s->data;//将s的右孩子中最大的值赋给p 
		if(q!=p) q->rchild=s->lchild;//如果q所指的位置与p不相等，既左孩子是树叶，就将q的最后一个结点的值赋给p 
		else q->lchild=s->lchild;// 
		free(s);
	}
	return 1;
}//Delete
Status DeleteBST(BiTree &T,TElemType key){
	if(T==NULL) return 0;
	else{
		if(EQ(key,T->data)) {
			 DeleteT(T);
			 return 1;
		}
		else if(LT(key,T->data)) return DeleteBST(T->lchild,key);//如果key值比该结点的值小，向左寻找插入位置 
		else return DeleteBST(T->rchild,key);
	}
}//DeleteBST
