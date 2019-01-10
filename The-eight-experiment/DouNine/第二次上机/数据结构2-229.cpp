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
	printf("请输入A、B、C线性表中元素个数：");
	scanf("%d%d%d", &La.length, &Lb.length, &Lc.length);
	La.list = (int*)malloc(sizeof(int) * La.length);
	Lb.list = (int*)malloc(sizeof(int) * Lb.length);
	Lc.list = (int*)malloc(sizeof(int) * Lc.length);
	
	printf("\n请递增有序输入A线性表中的数据：");
	for(int i=0; i<La.length; i++) {
		scanf("%d", &La.list[i]);
	}
	//ListTraverse(La);
	
	printf("请递增有序输入B线性表中的数据：");
	for(int i=0; i<Lb.length; i++) {
		scanf("%d", &Lb.list[i]);
	}
	//ListTraverse(Lb);
	
	printf("请递增有序输入C线性表中的数据：");
	for(int i=0; i<Lc.length; i++) {
		scanf("%d", &Lc.list[i]);
	}
	//ListTraverse(Lc);
	
	
	// 将B、C取交，并将交集放在B中 
	int i=0, j=0;
	while(i<Lb.length && j<Lc.length) {
		if(Lb.list[i] == Lc.list[j]) {
			i++;
			j++; 
		} 
		else if(Lb.list[i] < Lc.list[j]) {
			for(int k=i; k<Lb.length-1; k++) {
				Lb.list[k] = Lb.list[k+1];
			}
			Lb.length--;
		}
		else {
			j++;
		}
	}
	if(i < Lb.length) {
		Lb.length = i;
	}
	printf("B、C取交集结束:\n");
	ListTraverse(Lb);
	
	
	// 在A中，将A、B的交集删去 
	i=0, j=0;
	while(i<La.length && j<Lb.length) {
		if(La.list[i] == Lb.list[j]) {
			for(int k=i; k<La.length-1; k++) {
				La.list[k] = La.list[k+1];
			}
			La.length--;
		} 
		else if(La.list[i] < Lb.list[j]) {
			i++;
		}
		else {
			j++;
		}
	}
	printf("在A表中删去A、B交集结束:\n");
	ListTraverse(La);
	
	
	// 销毁线性表 
	free(La.list);
	free(Lb.list);
	free(Lc.list);
} 






