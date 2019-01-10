#include<iostream>
#include<stdlib.h>
using namespace std;

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

// 顺序表头 
typedef struct {
	int *head;
	int length;
	int listSize;
}Sqlist;

//顺序线性表类
class CSqList {
	public:
		
		//初始化线性表，即创建一个空表
		bool InitList(Sqlist &list) {
			if(list.head = (int*)malloc(LIST_INIT_SIZE*sizeof(int))) {
				list.length = 0;
				list.listSize = LIST_INIT_SIZE;
				return true;
			}
			else return false;
		};

		//销毁线性表，即free头指针
		bool DestroyList(Sqlist &list) {
			if(list.head) {
				free(list.head);
				list.head = NULL;
				return true;
			}
			else return false;
		};
		
		//清空线性表，即令长度为零
		void ClearList(Sqlist &list) {
			list.length = 0;
		};
		
		//判断是否为空表
		bool ListEmpty(Sqlist list) {
			return list.length ? false:true;
		};	
		
		//返回线性表的长度
		int ListLength(Sqlist list) {
			return list.length;
		};
		
		//返回线性表中第i个位置的值
		bool GetElem(Sqlist list, int i, int &e) {
			if(!list.length) return false;
			if(i <= 0 || i > list.length) return false;
			else e = list.head[i-1];
			return true;
		};
		
		//返回线性表中值与e相等的位置 
		int LocateElem(Sqlist list, int e) {
			if(!list.length) return 0;
			for(int i = 0; i < list.length; i++) {
				if(list.head[i] == e) return i+1;
			}
			return 0;
		};
		
		//返回值与cur_e相同的前一个值
		bool PriorElem(Sqlist list, int cur_e, int &pre_e) {
			if(!list.length) return false;
			if(list.head[0] == cur_e) return false;
			for(int i = 1; i < list.length; i++) {
				if(list.head[i]  == cur_e) {
					pre_e = list.head[i-1];
					return true;
				}
			}
			return false;
		};
		
		//返回值与cur_e相同的下一个值 
		bool NextElem(Sqlist list, int cur_e, int &next_e) {
			if(!list.length) return false;
			if(list.head[list.length - 1] == cur_e) return false;
			for(int i = 0; i < list.length-1; i++) {
				if(list.head[i]  == cur_e) {
					next_e = list.head[i+1];
					return true;
				}
			}
			return false;
		};
		
		//在线性表的第i位之前插入e值
		bool ListInsert(Sqlist &list, int i, int e) {
			if(!list.length) return false;					//判断表是否为空 
			if(i <= 0 || i > list.length) return false;		//判断i是否有效
			if(list.length == list.listSize) {				//判断表存储空间是否已满 
				int *newBase;
				if(newBase = (int*)realloc(list.head, 
				(list.listSize+LIST_INCREMENT) * sizeof(int))) {
					list.head = newBase;
					list.listSize += LIST_INCREMENT;
				}
				else {
					printf("error from ListInsert(): realloc defeat!\n");
					return false;
				}
			}
			for(int j = list.length-1; j >= i-1; j--) {		//将head[i-2]之后的数都向后移一位 
				list.head[j+1] = list.head[j];
			}
			list.head[i-1] = e;								//把e赋给head[i-1] 
			list.length++;
			return true;
		};
		
		//删除i位置的值，并用e返回其值 
		bool ListDelete(Sqlist &list, int i, int &e) {
			if(!list.length) return false;					//判断表是否为空 
			if(i <= 0 || i > list.length) return false;		//判断i是否有效
			e = list.head[i-1];								//把head[i-1]赋给e 
			for(int j = i; j < list.length; j++) {			//将head[i]之后的数都向前移一位 
				list.head[j-1] = list.head[j];
			}
			list.length--;
			return true;
		};
		
		//遍历函数
		void ListTraverse(Sqlist list) {
			printf("\n================遍历==============\n");
			for(int i = 0; i < list.length; i++) 
				printf("第%d位值为：%d\n", i+1, list.head[i]); 
		};		 
}; 


int main() {
	CSqList List;//顺序表对象 
	Sqlist list;//顺序表头 
	
	if(List.InitList(list)) printf("初始化顺序表成功\n");
	else printf("初始化顺序表失败\n");
	for(int i = 0; i < 20; i++) {
		list.head[i] = i+1;
		list.length++;
	}
	
	int test = 0;
	if(List.GetElem(list, 16, test)) printf("第16位元素的值是：%d\n", test);
	else printf("访问第16位元素失败\n");
	
	int test1 = 0;
	if(List.PriorElem(list, test, test1)) printf("%d前一个元素的值为：%d\n", test, test1);
	else printf("访问前一位元素失败\n");
	
	if(List.NextElem(list, test, test1)) printf("%d后一个元素的值为：%d\n", test, test1);
	else printf("访问后一位元素失败\n");
	
	if(List.ListInsert(list, 13, 1392985954)) printf("在第13位插值成功，插入的值为：1392985954\n");
	else printf("在第13位插值失败\n");
	
	if(List.ListDelete(list, 6, test)) printf("第6位删值成功，值为：%d\n", test);
	else printf("第6位删值失败\n");
	
	List.ListTraverse(list);
	
	if(List.DestroyList(list)) printf("链表销毁成功\n");
	else printf("\n链表销毁失败\n"); 
}
