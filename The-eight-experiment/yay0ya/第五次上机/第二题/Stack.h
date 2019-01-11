#include<iostream>
using namespace std;
#include<stdlib.h> 

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef int TElemType;
typedef struct BiTNode{
	//结点结构
	 TElemType data;
	 struct BiTNode *lchild,*rchild;//左右孩子指针 
}BiTNode,*BiTree;
typedef BiTNode* SElemType;
typedef int Status;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//-----基本操作的函数原型说明----

Status InitStack(SqStack &S){
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) exit(0);//存储分配失败
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return 1; 
}//InitStack

Status DestroyStack(SqStack &S){
	//摧毁一个栈
	SElemType *p;
	p=S.base;//指针指向栈底；
	while(p!=S.top){//当指针没有指向栈顶时 
		free(p);
		p++;
	} 
	free(p);//释放p指向的地址的空间 
	S.stacksize=0;//栈空间置为0 
	return 1;
} 
Status ClearStack(SqStack &S){
	//清空一个栈 
	S.top=S.base;//栈顶和栈底指向同一个空间栈底 
	return 1; 
} 
Status StackEmpty(SqStack S){
	//判断栈是否为空
	if(S.top==S.base)//栈底和栈顶在同一空间上，则判断其栈为空 
	return 1;
	else return 0; 
}
Status StackLength(SqStack S){
	//判断栈的大小
	SElemType *p=S.base;
	int count=0;
	while(p!=S.top){//指正不指向栈顶的时候 count+1 
		p++;
		count++;
	} 
	return count;
} 
Status GetTop(SqStack S,SElemType &e){
	//返回栈顶元素
	if(S.top==S.base) return 0;
	e=*(S.top-1);
	return 1; 
} //GetTop
Status Push(SqStack &S,SElemType &e){
	//插入元素e为新的栈顶元素
	if(S.top-S.base>=S.stacksize){
	//栈满追加空间
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit(0);//分配存储空间失败
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT; 
	} 
	*S.top++=e;
	return 1;
}//Push
Status Pop(SqStack &S,SElemType &e){
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回1，否则返回0
	if(S.top==S.base) return 0;
	e=*--S.top;
	return 1; 
}//Pop 
