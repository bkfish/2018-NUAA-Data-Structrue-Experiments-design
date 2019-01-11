#include<iostream>
using namespace std;
#include<fstream>
#define m 3
typedef int KeyType;
typedef struct BTNode{
	int keynum;
	struct BTNode *parent;//指向双亲结点
	KeyType key[m+1];//关键字向量，不用0号单元
	struct BTNode *ptr[m+1];//子树指针向量 	
}BTNode,*BTree;
typedef struct {
	BTNode *pt;//指向找到的结点 
	int i;//1...,m在结点中的关键字序号 
	int tag;//1.查找成功。0.查找失败 
}Result;
int BTreeSearch(BTree T,KeyType K,BTNode *curNode,int count){
	//在B树中查找k值
	BTNode *p;
	if(T==NULL) return 0;//不存在这棵树 
	p=T;
	int flag=0,i=0;
	while(p!=NULL){
		flag=0;
		for(i=1;i<=p->keynum;i++){
			if(K==p->key[i]){
				curNode=p;
				count=i;
				return 1;//表示存在这个值找到 
			}
			
			if(K<p->key[i]){
				//如果该值比p,key[i]小，则前往其该子树之前下的子树中去
				p=p->ptr[i-1];
				flag=1;
				break;
			 
			}
		}
		if(K>p->key[i]&&flag==0){
			p=p->ptr[i-1];
		}
		
	}
	return 0; 
}//仅用来表示是否找到该结点 
void Insert(BTree &T,KeyType K,BTree q,int i){
	//k是要插入的值，T是B树，bTree 
	int j=0;
	for(j=T->keynum;j>=i+1;--j){
		T->key[j+1]=T->key[j];
		T->ptr[j+1]=T->ptr[j];//关键字后移，插入新的关键字	 
	}
	T->key[i+1]=K;
	T->ptr[i+1]=q;
	++T->keynum;//完成插入 
}
bool BTreeSplit(BTree &T,int s,BTNode *rhs,KeyType &k){
	rhs=new BTNode;
	//rhs为新建的结点，用于保存右半部份的
	if(rhs==NULL){
		exit(0);
	} 
	//对t进行分裂，所以rhs是t的兄弟结点，有相同的父母
	rhs->parent=T->parent;
	//其中关键字序列的中间值为
	k=T->key[s];
	T->key[s]=0;
	rhs->ptr[0]=T->ptr[s];
	//如果原来的T是s号孩子指针，现在0号指针不为空，需要改变孩子的父亲节点
	if(rhs->ptr[0]!=NULL){
		rhs->ptr[0]->parent=rhs; 
	}//endif;
	T->ptr[s]=NULL;
	for(int i=1;i<=m-s;++i){
		//把右半部分全部复制到rhs中
		rhs->key[i]=T->key[s+i];
		T->key[s+i]=0;
		rhs->ptr[i]=T->ptr[s+i];
		T->ptr[s+i]=NULL;
		//现在改变rhs的父亲结点
		if(rhs->ptr[i]){
			rhs->ptr[i]->parent=rhs;
		}//endif 
	}//endfor
	rhs->keynum=m-s;
	T->keynum=s-1;
	return true; 
}
bool BTreeNewroot(BTree &T,BTree &lhs,KeyType midk,BTree &rhs){
	//建立一个新的结点
	BTNode *temp=new BTNode;
	if(temp==NULL){
		exit(0);
	}
	temp->keynum=1;
	temp->key[1]=midk;
	
	temp->ptr[0]=lhs;
	//左孩子不为空的时候
	if(temp->ptr[0]){
		temp->ptr[0]->parent=temp;
	}
	temp->ptr[1]=rhs;
	//右孩子不为空的时候
	if(temp->ptr[1]){
		temp->ptr[1]->parent=temp;
	} 
	T=temp;
	return true;
} 
//插入一个k值 
bool BTreeInsert(KeyType k,BTree &T){
	BTNode *curNode=NULL;
	int preldx=0;
	if(BTreeSearch(T,k,curNode,preldx)){
		cout<<"关键字已经存在"<<endl;
		return false;
	}
	else{
		KeyType curkey=k;
		BTNode *rhs=NULL;
		bool finished=false;
		while(!finished&&curNode){
			Insert(curNode,curkey,rhs,preldx);
			if(curNode->keynum<m)
				finished=true;
			else{
				int s=(m+1)/2;
				if(BTreeSplit(curNode,preldx,rhs,curkey)){
					return false;
				}
				if(curNode->parent==NULL){
					//curNode 成为根结点
					break; 
				}
				else{
					//如果有父亲结点，此时curkey指向原来这个结点的中间值
					//所以需要和父亲结点融合
					curNode=curNode->parent;
					BTreeSearch(T,curkey,curNode,preldx); 
				}
			}
				
		}
	} 
}

void BTreeTraverse(BTree T){
	if(T){
		for(int i=0;i<T->keynum;i++){
			cout<<T->key[i]<<" ";
		}
		for(int i=0;i<T->keynum;i++)
			BTreeTraverse(T->ptr[i]);
	}
}
