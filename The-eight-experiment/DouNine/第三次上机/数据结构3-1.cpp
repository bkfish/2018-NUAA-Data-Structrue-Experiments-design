#include<iostream>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10 

using namespace std;

typedef struct sqStack {
	int stackSize;
	int *base;
	int *top;
}sqStack;

class SqStack {

public:
	bool InitStack(sqStack &sqStack) {
		sqStack.base = (int*)malloc(sizeof(int)*STACK_INIT_SIZE);
		if(!sqStack.base) return false;
		sqStack.top = sqStack.base;
		sqStack.stackSize = STACK_INIT_SIZE;
		return true;
	}
	
	void DestroyStack(sqStack &sqStack) {
		if(sqStack.base) free(sqStack.base);
	}
	
	void ClearStack(sqStack &sqStack) {
		if(sqStack.base) sqStack.top = sqStack.base;
	}
	
	bool StackEmpty(sqStack sqStack) {
		if(!sqStack.base) return true;
		if(sqStack.base == sqStack.top-1) return true;
		return false;
	}
	
	int StackLength(sqStack sqStack) {
		if(!sqStack.base) return 0;
		return sqStack.top - sqStack.base;
	}
	
	bool GetTop(sqStack sqStack, int &e) {
		if(!sqStack.base) return false;
		e = *(sqStack.top-1);
		return true;
	}
	
	bool Push(sqStack &sqStack, int e) {
		if(!sqStack.base) return false;
		if(StackLength(sqStack) == sqStack.stackSize-1) {
			sqStack.base = (int*)realloc(sqStack.base, sqStack.stackSize+STACKINCREMENT);
			sqStack.top = sqStack.base + sqStack.stackSize - 1;
			sqStack.stackSize += STACKINCREMENT;
		}
		*sqStack.top = e;
		sqStack.top++;
		return true;
	}
	
	bool Pop(sqStack &sqStack, int &e) {
		if(!sqStack.base || !StackLength(sqStack)) return false;
		sqStack.top--;
		e = *sqStack.top;
		return true;
		
	}
	
	void StackTraverse(sqStack sqStack) {
		printf("==================遍历栈===================\n");
		int *p = sqStack.base;
		while(p!=sqStack.top) {
			printf("%d ", *p);
			p++;
		}
		printf("\n===========================================\n");
	}
};


int main() {
	SqStack S;
	sqStack s;
	if(S.InitStack(s))
		printf("栈初始化成功\n");
	printf("请输入十个数：\n");
	int num = 0;
	for(int i=0; i<10; i++) {
		scanf("%d", &num);
		S.Push(s, num);
	}
	S.StackTraverse(s);
	
	int temp = 0;
	S.Pop(s, temp);
	printf("弹出栈顶元素：%d\n", temp);
	S.StackTraverse(s);
	
	S.GetTop(s, temp);
	printf("获取栈顶元素：%d\n", temp);
	S.StackTraverse(s);
	
	S.DestroyStack(s);
	printf("栈销毁成功\n");
}
