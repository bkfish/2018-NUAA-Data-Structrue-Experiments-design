#include<iostream>
#include<stdlib.h>
using namespace std;

// 链式结点 
typedef struct LNode{
	int data;
	LNode *next;
}LNode, *LinkList;

// 链式线性表类
class CLinkList {
	public:
		
		//初始化线性表，创建一个头结点，头结点的data数据表示链表长度 
		bool InitList(LinkList &list) {
			if(list = (LNode*)malloc(sizeof(LNode))) {
				list->data = 0;
				list->next = NULL;
				return true;
			}
			else return false;
		};

		//销毁线性表，即free头指针
		bool DestroyList(LinkList &list) {
			if(list) {
				if(ClearList(list)) {
					printf("清空链表成功\n");
					free(list);
					return true;
				}
				else {
					printf("清空链表失败\n");
					return false;
				}
			}
			else return false;
		};
		
		//清空线性表，将链表的结点都删除（除头结点之外） 
		bool ClearList(LinkList &list) {
			if(list) {
				LNode *temp, *p = list->next;
				while(p) {
					temp = p;
					p = p->next;
					free(temp);
				}
				list->data = 0;
				list->next = NULL;
				return true;
			}
			return false;
		};
		
		//判断是否为空表
		bool ListEmpty(LinkList list) {
			if(!list) return false;			//判断表是否为空 
			return list->data ? false:true;
		};	
		
		//返回线性表的长度
		int ListLength(LinkList list) {
			if(!list) return 0;				//判断表是否为空 
			return list->data;
		};
		
		//返回线性表中第i个位置的结点 
		bool GetElem(LinkList list, int i, LNode *e) {
			if(!list || !list->data) return false;			//判断表是否为空 
			if(i <= 0 || i > list->data) return false;
			else {
				int j = 1;
				LNode *p = list->next;
				while(p && j++!=i) p = p->next;
				e->data = p->data;
				e->next = p->next;
			}
			return true;
		};
		
		//返回线性表中值与e相等的位置 
		int LocateElem(LinkList list, LNode *e) {
			if(!list || !list->data) return 0;
			LNode *p = list->next;
			int i = 1;
			while(p) {
				if(p->data == e->data) return i;
				p = p->next;
			}
			return 0;
		};
		
		//返回值与cur_e相同的前一个值
		bool PriorElem(LinkList list, LNode *cur_e, LNode *pre_e) {
			if(!list || !list->data) return false;			//判断表是否为空 
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p) {
				if(j == 1 && p->data == cur_e->data) return false;
				if(p->data == cur_e->data) {
					pre_e->data = last->data;
					pre_e->next = last->next;
					return true;
				}
				last = p;
				p = last->next;
				j++;
			}
			return false;
		};
		
		//返回值与cur_e相同的下一个值 
		bool NextElem(LinkList list, LNode *cur_e, LNode *next_e) {
			if(!list || !list->data) return false;			//判断表是否为空 
			LNode *next, *p = list;
			int j = 1;
			while(p) {
				next = p->next;
				if(j == list->data && p->data == cur_e->data) return false;
				if(p->data == cur_e->data) {
					next_e->data = next->data;
					next_e->next = next->next;
					return true;
				}
				p = p->next;
				j++;
			}
			return false;
		};
		
		//在线性表的第i位插入e值
		bool ListInsert(LinkList &list, int i, LNode *e) {
			if(!list) return false;			//判断表是否为空  
			if(i <= 0 || i > list->data+1) return false;		//判断i是否有效
			
			//防止用户把传进的实参e多次使用
			LNode *temp = (LNode*)malloc(sizeof(LNode));	 
			temp->data = e->data;
			temp->next;
			
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p && j++!=i) {							
				last = p;
				p = last->next;
			}
			last->next = temp;
			temp->next = p;
			list->data++;
			return true;
		};
		
		//删除i位置的值，并用e返回其值 
		bool ListDelete(LinkList &list, int i, LNode *e) {
			if(!list || !list->data) return false;			//判断表是否为空 
			if(i <= 0 || i > list->data) return false;		//判断i是否有效
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p && j++!=i) {
				last = p;
				p = last->next;
			}
			e->data = p->data;
			e->next = NULL;
			last->next = p->next;
			free(p);
			list->data--;
			return true;
		};
		
		//遍历函数
		void ListTraverse(LinkList list) {
			printf("\n================遍历==============\n");
			LNode *p = list->next;
			int i = 1;
			while(p) {
				printf("第%d位值为：%d\n", i, p->data); 
				p = p->next;
				i++;
			}
		};		 
}; 


int main() {
	CLinkList List;//顺序表对象 
	LinkList list;//顺序表头 
	
	if(List.InitList(list)) printf("初始化顺序表成功\n");
	else printf("初始化顺序表失败\n");
	
	int i = 1;
	LNode *temp, *p=list;
	while(i <= 20) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i;
		temp->next = NULL;
		p->next = temp;
		p = p->next;
		list->data++;
		i++; 
	}
	
	LNode *test = (LNode*)malloc(sizeof(LNode));
	if(List.GetElem(list, 16, test)) printf("第16位元素的值是：%d\n", test->data);
	else printf("访问第16位元素失败\n");
	
	LNode *test1 = (LNode*)malloc(sizeof(LNode));
	if(List.PriorElem(list, test, test1)) printf("%d前一个元素的值为：%d\n", test->data, test1->data);
	else printf("访问前一位元素失败\n");
	
	if(List.NextElem(list, test, test1)) printf("%d后一个元素的值为：%d\n", test->data, test1->data);
	else printf("访问后一位元素失败\n");
	
	test->data = 9999;
	if(List.ListInsert(list, 13, test)) printf("在第13位插值成功，插入的值为：%d\n", test->data);
	else printf("在第13位插值失败\n");
	
	test->data = 8888;
	if(List.ListInsert(list, 21, test)) printf("在第21位插值成功，插入的值为：%d\n", test->data);
	else printf("在第21位插值失败\n");
	
	if(List.ListDelete(list, 6, test)) printf("第6位删值成功，值为：%d\n", test->data);
	else printf("第6位删值失败\n");
	
	List.ListTraverse(list);
	
	if(List.DestroyList(list)) printf("链表销毁成功\n");
	else printf("链表销毁失败\n"); 
}
