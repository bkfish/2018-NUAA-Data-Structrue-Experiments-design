#ifndef _BTREE_H
#define _BTREE_H
#define MAXM 10                     //定义B树的最大的阶数

const int m=4;                      //设定B树的阶数 
const int Max=m-1;                  //结点的最大关键字数量 
const int Min=(m-1)/2;              //结点的最小关键字数量 
typedef int KeyType;                //KeyType为关键字类型

typedef struct node{                //B树和B树结点类型 
    int keynum;                     //结点关键字个数
    KeyType key[MAXM];              //关键字数组，key[0]不使用 
    struct node *parent;            //双亲结点指针
    struct node *ptr[MAXM];         //孩子结点指针数组 
}BTNode,*BTree;

typedef struct{                     //B树查找结果类型 
    BTNode *pt;                     //指向找到的结点
    int i;                          //在结点中的关键字位置; 
    int tag;                        //查找成功与否标志
}Result;

typedef struct LNode{               //链表和链表结点类型 
    BTree data;                     //数据域
    struct LNode *next;             //指针域
}LNode, *LinkList;

typedef enum status{               //枚举类型（依次递增） 
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

Status InitBTree(BTree &t);                                     //初始化B树 
int SearchBTNode(BTNode *p,KeyType k);                          //在结点p中查找关键字k的插入位置i 
Result SearchBTree(BTree t,KeyType k);                          /*在树t上查找关键字k,返回结果(pt,i,tag)。若查找成功,则特征值
                                                                tag=1,关键字k是指针pt所指结点中第i个关键字；否则特征值tag=0,
                                                                关键字k的插入位置为pt结点的第i个*/
void InsertBTNode(BTNode *&p,int i,KeyType k,BTNode *q);        //将关键字k和结点q分别插入到p->key[i+1]和p->ptr[i+1]中
void SplitBTNode(BTNode *&p,BTNode *&q);                        //将结点p分裂成两个结点,前一半保留,后一半移入结点q
void NewRoot(BTNode *&t,KeyType k,BTNode *p,BTNode *q);         //生成新的根结点t,原结点p和结点q为子树指针
void InsertBTree(BTree &t,int i,KeyType k,BTNode *p);           /*在树t上结点q的key[i]与key[i+1]之间插入关键字k。若引起
                                                                 结点过大,则沿双亲链进行必要的结点分裂调整,使t仍是B树*/
void Remove(BTNode *p,int i);                                   //从p结点删除key[i]和它的孩子指针ptr[i]
void Substitution(BTNode *p,int i);                             //查找被删关键字p->key[i](在非叶子结点中)的替代叶子结点(右子树中值最小的关键字) 
void MoveRight(BTNode *p,int i);                                /*将双亲结点p中的最后一个关键字移入右结点q中
                                                                将左结点aq中的最后一个关键字移入双亲结点p中*/ 
void MoveLeft(BTNode *p,int i);                                 /*将双亲结点p中的第一个关键字移入结点aq中，
                                                                 将结点q中的第一个关键字移入双亲结点p中*/
void Combine(BTNode *p,int i);                                  /*将双亲结点p、右结点q合并入左结点aq，
                                                                并调整双亲结点p中的剩余关键字的位置*/                                                                 
void AdjustBTree(BTNode *p,int i);                              //删除结点p中的第i个关键字后,调整B树                                                                
int FindBTNode(BTNode *p,KeyType k,int &i);                     //反映是否在结点p中是否查找到关键字k 
int BTNodeDelete(BTNode *p,KeyType k);                          //在结点p中查找并删除关键字k
void BTreeDelete(BTree &t,KeyType k);                           //构建删除框架，执行删除操作 
void DestroyBTree(BTree &t);                                    //递归释放B树
Status InitQueue(LinkList &L);                                  //初始化队列 
LNode* CreateNode(BTree t);                                     //新建一个结点 
Status Enqueue(LNode *p,BTree t);                               //元素q入队列
Status Dequeue(LNode *p,BTNode *&q);                            //出队列，并以q返回值
Status IfEmpty(LinkList L);                                     //队列判空 
void DestroyQueue(LinkList L);                                  //销毁队列 
Status Traverse(BTree t,LinkList L,int newline,int sum);        //用队列遍历输出B树 
Status PrintBTree(BTree t);                                     //输出B树 
void Test();                                                    //测试B树功能函数 
#endif 
