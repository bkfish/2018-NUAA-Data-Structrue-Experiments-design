#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#define m 3
typedef int KeyType;
typedef int Record;
typedef struct BTNode{
	int   keynum;//结点中关键字个数，即结点的大小
	struct BTNode  *parent;		//指向双亲结点
	KeyType  key[m+1];			//关键字向量，0号单元未用
	struct BTNode *ptr[m+1];    //子树指针向量
	Record   *recptr[m+1];		//记录指针向量，0号单元未用 
}BTNode,*BTree;					//B-树结点和B-树类型
typedef struct {
	BTNode *pt;					//指向找到的结点
	int      i;					//1...m在结点中的关键字序号
	int    tag;					//1:查找成功，0：查找失败 
}Result;						//B-树的查找结果类型
 
int Search(BTNode *p,KeyType K){
	for(int i=0;i<p->keynum-1;i++){
		if(p->key[i]==K){
			return i;//如果找到与K值相同的关键，返回它的索引 
		}
		if(p->key[i]<K&&K<p->key[i+1])
			return i;//找到一个结点，它的前值比K小，后值比K大；
		if(i+1==p->keynum&&K>p->key[i+1])//如果K比最后一个值还要大
				return i+1; 
	}
}

Result SearchBTree(BTree T,KeyType K){
	//在m阶B-树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值
	//tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0；等于K的关键字应
	//插入在指针pt所指的节点中第i和第i+1个关键字之间
	BTNode *p,*q;
	Result re;
	bool found=false;
	int i=0;
	p=T;q=NULL;				//初始化，p指向待查找结点，q指向p的双亲
	while(p!=NULL&&!found){
		i=Search(p,K);		//在p->key[1...keynum]中查找，
							//使得：p->key[i]<=K<p->key[i+1]
		if(i>0&&p->key[i]==K) found=true;//找到待查找关键字
		else {
			q=p;  p=p->ptr[i];
		}					 
	}//while
	if(found) {				//查找成功 
		re.pt=p;
		re.i=i;
		re.tag=1;
		return re;
	}
	else {				//查找不成功，返回K的插入位置信息 
		re.pt=q;
		re.i=i;
		re.tag=0;
		return re;
	}
}

void Insert(BTree &q,int i,KeyType x,BTNode *ap){
	int j;
	for(j=q->keynum;j>i;j--){
		q->key[j+1]=q->key[j];//整体后移，给插入值空出一个位置 
		q->ptr[j+1]=q->ptr[j]; 
	}
	q->ptr[i+1]=ap;//将ptr[i+1]这个结点的指针指向ap 
	q->key[i+1]=x;//将x这个值赋给key[i+1] 
	if(ap!=NULL){
		ap->parent=q;//将ap 的双亲指针，指向q 
	}
	q->keynum++;//插入一个值，该结点上的值数量增加
}

void split(BTree &q,int s,BTree &ap){
	//将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap
	int i;
	ap=new BTNode;//给结点ap分配空间
	ap->ptr[1]=q->ptr[s];//将q指针指向的后一般空间内容移入结点q 
	for(i=1;s+i<=m;i++){
		ap->key[i]=q->key[s+i];//将q->key[s+1...m]移入到 ap->key[1..m-s]中
		ap->recptr[i]=q->recptr[s+i];//将q->recptr[s+1..m]移入到ap->[1..m-s]中 
		ap->ptr[i-1]=q->ptr[s+i];
	}
	ap->keynum=q->keynum-s;
	ap->parent=q->parent;;//则q中间的keynum值成为s个 
	for(i=0;i<=q->keynum-s;i++){
		//修改剩余指针的双亲结点
		if(ap->ptr[i]!=NULL)
			ap->ptr[i]->parent=ap;
		q->keynum=s-1;			//结点q内的keynum值发生改变	 
	}
}

void NewRoot(BTree &T,BTNode *q,KeyType K,BTNode *ap){
	//	T是空树(参数q初值为NULL)或者根结点已分裂为结点*q和*ap 
	// 生成含信息(T,x,ap)的新的根结点*T，原T和ap为子树指针 
	T=new BTNode;
	T->keynum=1;
	T->ptr[0]=q;
	T->ptr[1]=ap;
	T->key[1]=K;
	if(q!=NULL){
		q->parent=T;
	}
	if(ap!=NULL)
		ap->parent=T;
	T->parent=NULL;
			
}//NewRoot

int InsertBTree(BTree &T,KeyType K,BTree q,int i){
	//在m阶B-树T上结点*q的key[i]与key[i+1]之间插入关键字K。
	//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B-树。
	KeyType x=K;
	BTNode *ap=NULL;
	int s;
	bool finished=false;
	if(T==NULL){
		NewRoot(T,NULL,K,NULL);
	}
	while(q!=NULL&&!finished){
		Insert(q,i,x,ap);   //将x和ap分别插入到q->key[i+1]和q->ptr[i+1]x是key[i]的一个值，q是BTree 一个指针，ap代表这个指针
		if(q->keynum<m) finished=true;//插入完成 
		else {			//分裂结点*q
		 	s=(m+1)/2;//s对m/2向上取整，如果该值m是奇数，进行除以二加一操作
			 					//m是偶数，仅仅除以二
			split(q,s,ap);
			x=q->key[s];		//将q->key[s+1,..m],q->ptr[s...m]和q->recptr[s+1..m]移入新结点*ap
			q=q->parent;
			if(q!=NULL) i=Search(q,x);		//在双亲结点*q中查找x的插入位置	 
	
		}//else
	}//while
	if(!finished)			//	T是空树(参数q初值为NULL)或者根结点已分裂为结点*q和*ap 
		NewRoot(T,q,x,ap); 	// 生成含信息(T,x,ap)的新的根结点*T，原T和ap为子树指针 
	return 1; 
}//InsertBTree
void  deletechild(BTNode *p,int i){
	int j;
	for(j=i+1;j<=p->keynum;j++){
		p->key[j-1]=p->key[j];
		p->ptr[j-1]=p->ptr[j];
	}
	p->keynum--;//删除一个结点key[i],同时删除与之相关的ptr[i]结点 
}
void findsub(BTNode *p,int i){
	//寻找能够放入上一层结点的值
	BTNode *q;
	for(q=p->ptr[i];q->ptr[0]!=NULL;q=q->ptr[1]);
	p->key[i]=q->key[1];//复制关键字 
}

void Restore(BTree &T,BTree &p){
	BTNode *parent,*leftBrother,*rightBrother;//被删除的结点的父亲结点和左右兄弟
	parent=p->parent;
	if(parent!=NULL){
		//父结点不为空 
	} 
}

void MoveRight(BTNode *p,int i){
/*将双亲结点p中的最后一个关键字移入右结点q中
将左结点aq中的最后一个关键字移入双亲结点p中*/ 
    int j;
    BTNode *q=p->ptr[i];
    BTNode *aq=p->ptr[i-1];

    for(j=q->keynum;j>0;j--){                       //将右兄弟q中所有关键字向后移动一位
        q->key[j+1]=q->key[j];
        q->ptr[j+1]=q->ptr[j];
    }

    q->ptr[1]=q->ptr[0];                            //从双亲结点p移动关键字到右兄弟q中
    q->key[1]=p->key[i];
    q->keynum++;

    p->key[i]=aq->key[aq->keynum];                  //将左兄弟aq中最后一个关键字移动到双亲结点p中
    p->ptr[i]->ptr[0]=aq->ptr[aq->keynum];
    aq->keynum--;
}


void MoveLeft(BTNode *p,int i){
/*将双亲结点p中的第一个关键字移入左结点aq中，
将右结点q中的第一个关键字移入双亲结点p中*/ 
    int j;
    BTNode *aq=p->ptr[i-1];
    BTNode *q=p->ptr[i];

    aq->keynum++;                                   //把双亲结点p中的关键字移动到左兄弟aq中
    aq->key[aq->keynum]=p->key[i]; 
    aq->ptr[aq->keynum]=p->ptr[i]->ptr[0];

    p->key[i]=q->key[1];                            //把右兄弟q中的关键字移动到双亲节点p中
    q->ptr[0]=q->ptr[1];
    q->keynum--;

    for(j=1;j<=aq->keynum;j++){                     //将右兄弟q中所有关键字向前移动一位
        aq->key[j]=aq->key[j+1];
        aq->ptr[j]=aq->ptr[j+1];
    }
}


void Combine(BTNode *p,int i){
/*将双亲结点p、右结点q合并入左结点aq，
并调整双亲结点p中的剩余关键字的位置*/ 
    int j;
    BTNode *q=p->ptr[i];                            
    BTNode *aq=p->ptr[i-1];

    aq->keynum++;                                  //将双亲结点的关键字p->key[i]插入到左结点aq     
    aq->key[aq->keynum]=p->key[i];
    aq->ptr[aq->keynum]=q->ptr[0];

    for(j=1;j<=q->keynum;j++){                      //将右结点q中的所有关键字插入到左结点aq 
        aq->keynum++;
        aq->key[aq->keynum]=q->key[j];
        aq->ptr[aq->keynum]=q->ptr[j];
    }

    for(j=i;j<p->keynum;j++){                       //将双亲结点p中的p->key[i]后的所有关键字向前移动一位 
        p->key[j]=p->key[j+1];
        p->ptr[j]=p->ptr[j+1];
    }
    p->keynum--;                                    //修改双亲结点p的keynum值 
    free(q);                                        //释放空右结点q的空间
}


void AdjustBTree(BTNode *p,int i){
//删除结点p中的第i个关键字后,调整B树
    int Min=(m-1)/2;
	if(i==0)                                        //删除的是最左边关键字
        if(p->ptr[1]->keynum>Min)                   //右结点可以借
            MoveLeft(p,1);
        else                                        //右兄弟不够借 
            Combine(p,1);
    else if(i==p->keynum)                           //删除的是最右边关键字
        if(p->ptr[i-1]->keynum>Min)                 //左结点可以借 
            MoveRight(p,i);
        else                                        //左结点不够借 
            Combine(p,i);
    else if(p->ptr[i-1]->keynum>Min)                //删除关键字在中部且左结点够借 
        MoveRight(p,i);
    else if(p->ptr[i+1]->keynum>Min)                //删除关键字在中部且右结点够借 
        MoveLeft(p,i+1);
    else                                            //删除关键字在中部且左右结点都不够借
        Combine(p,i);
}


int FindBTNode(BTNode *p,KeyType k,int &i){
//反映是否在结点p中是否查找到关键字k 
    if(k<p->key[1]){                                //结点p中查找关键字k失败 
        i=0;
        return 0;
    }
    else{                                           //在p结点中查找
        i=p->keynum;
        while(k<p->key[i]&&i>1)
            i--;
        if(k==p->key[i])                            //结点p中查找关键字k成功 
            return 1;
    }
}


int BTNodeDelete(BTNode *p,KeyType k){
//在结点p中查找并删除关键字k
	int Min=(m-1)/2;
    int i;
    int found_tag;                                  //查找标志 
    if(p==NULL)                                     
        return 0;
    else{
        found_tag=FindBTNode(p,k,i);                //返回查找结果 
        if(found_tag==1){                           //查找成功 
            if(p->ptr[i-1]!=NULL){                  //删除的是非叶子结点
                findsub(p,i);                  //寻找相邻关键字(右子树中最小的关键字) 
                BTNodeDelete(p->ptr[i],p->key[i]);  //执行删除操作 
            }
            else
                deletechild(p,i);                        //从结点p中位置i处删除关键字
        }
        else
            found_tag=BTNodeDelete(p->ptr[i],k);    //沿孩子结点递归查找并删除关键字k
        if(p->ptr[i]!=NULL)
            if(p->ptr[i]->keynum<Min)               //删除后关键字个数小于MIN
                AdjustBTree(p,i);                   //调整B树 
        return found_tag;
    }
}

void BTreeDelete(BTree &t,KeyType k){
//构建删除框架，执行删除操作  
    BTNode *p;
    int a=BTNodeDelete(t,k);                        //删除关键字k 
    if(a==0)                                        //查找失败 
        cout<<"不存在该词\n"<<endl; 
    else if(t->keynum==0){                          //调整 
        p=t;
        t=t->ptr[0];
        free(p);
    }
}

void DestroyBTree(BTree &t){
    int i;  
    BTNode* p=t;  
    if(p!=NULL){                                    //B树不为空  
        for(i=0;i<=p->keynum;i++){                  //递归释放每一个结点 
            DestroyBTree(*&p->ptr[i]);  
        }  
        free(p);  
    }  
    t=NULL;  
}  
void BTreeTraverse(BTree T){
	if(T){
		for(int i=1;i<=T->keynum;i++){
			cout<<T->key[i]<<" ";
		}
		for(int i=0;i<=T->keynum;i++)
			BTreeTraverse(T->ptr[i]);
	}
}
