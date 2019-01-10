#include<iostream>
#include<stdlib.h>
using namespace std;

//顺序表头结构体 
typedef struct {
	int *head;
	int length;
}Sqlist;


//遍历函数
void ListTraverse(Sqlist list) {
	for(int i = 0; i < list.length; i++) 
		printf("第%d位值为：%d\n", i+1, list.head[i]); 
}
		
//初始化线性表
bool InitList(Sqlist &list, int n) {
	if(list.head = (int*)malloc(n*sizeof(int))) {
		list.length = 0;
		for(int i = 0; i < n; i++) {
		list.head[i] = i+1;
			list.length++;
		}
		printf("================顺序表倒置前===============\n");
		ListTraverse(list);
		return true;
	}
	else return false;
}

//销毁线性表，即free头指针
bool DestroyList(Sqlist &list) {
	if(list.head) {
		free(list.head);
		list.head = NULL;
		return true;
	}
	else return false;
}


int main() {
	Sqlist list;//顺序表头 
	
	int num;
	printf("请输入顺序表元素的个数：");
	scanf("%d", &num);
	
	if(InitList(list, num)) printf("初始化顺序表成功\n");
	else printf("初始化顺序表失败\n");
	
	int temp = 0;
	for(int i = 0; i < list.length/2; i++) {
		temp = list.head[i];
		list.head[i] = list.head[list.length-i-1];
		list.head[list.length-i-1] = temp; 
	}
	printf("=====================顺表倒置后=================\n");
	ListTraverse(list);
	
	if(DestroyList(list)) printf("链表销毁成功\n");
	else printf("链表销毁失败\n"); 
}
