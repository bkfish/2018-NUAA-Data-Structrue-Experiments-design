#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int *list;
	int length;
}SqList ;

void ListTraverse(SqList L) {
	printf("\n==========遍历=============\n");
	for(int i=0; i<L.length; i++) {
		printf("%d ", L.list[i]);
	}
	printf("\n===========================\n\n");
}

int main() {
	
	// 初始化 
	SqList La, Lb, Lc;
	printf("请输入A、B线性表中元素个数：");
	scanf("%d%d", &La.length, &Lb.length);
	La.list = (int*)malloc(sizeof(int) * La.length);
	Lb.list = (int*)malloc(sizeof(int) * Lb.length);
	
	printf("\n请递增有序输入A线性表中的数据：");
	for(int i=0; i<La.length; i++) {
		scanf("%d", &La.list[i]);
	}
	ListTraverse(La);
	
	printf("请递增有序输入B线性表中的数据：");
	for(int i=0; i<Lb.length; i++) {
		scanf("%d", &Lb.list[i]);
	}
	ListTraverse(Lb);
	
	
	// 将A、B取交 
	int i=0, j=0;
	while(i<La.length && j<Lb.length) {
		if(La.list[i] == Lb.list[j]) {
			i++;
			j++; 
		} 
		else if(La.list[i] < Lb.list[j]) {
			for(int k=i; k<La.length-1; k++) {
				La.list[k] = La.list[k+1];
			}
			La.length--;
		}
		else {
			j++;
		}
	}
	if(i < La.length) {
		La.length = i;
	}
	printf("取交集结束:\n");
	Lc.list = La.list;
	Lc.length = La.length;
	ListTraverse(Lc);
	
	
	// 销毁线性表 
	free(La.list);
	free(Lb.list);
} 






