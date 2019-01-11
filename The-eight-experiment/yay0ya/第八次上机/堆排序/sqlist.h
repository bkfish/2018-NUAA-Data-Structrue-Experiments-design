#define LIST_INIT_SIZE 100
#define LISTNCREMENT 10
#define ERROR 0;
#define OK 1;
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef int Sqtype;
typedef struct{
	Sqtype *elem;
	int length;//当前长度
	int listsize;//当前分配存储容量 
} Sqlist;
bool InitList_Sq(Sqlist &L){
	//create a new empty list
	L.elem=(Sqtype *)malloc(LIST_INIT_SIZE*sizeof(char));
	if(!L.elem) 
	exit(0);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return 0;
} 
bool DestroyTriplet(Sqlist &L){
	free(L.elem);
	return 0;
}
bool ClearList(Sqlist &L){
	L.length=0;
	return 0;
}
bool ListEmpty(Sqlist L){
	if(!L.length) return 1;
	else return 0; 
}
int ListLength(Sqlist &L){
	return L.length;
}
bool GetElem(Sqlist L,int i,Sqtype &e){
	//find the location of the number i
	if(i<1||i>L.length+1) return 0;
	e=L.elem[i-1];
	return 1;
}
int LocateElem(Sqlist L,Sqtype e){
	//find one number is compare with e
	Sqtype *p=L.elem; int i=1;
	while(*p!=e){
		p++;
		i++;
	}
	if(*p){
		return i; 
	}
	else return 0;
}
bool PriorElem(Sqlist L,Sqtype cur_e,Sqtype& pre_e){
	Sqtype*p=L.elem,*q;
	if(cur_e==*p) return ERROR;
	q=p;p++;
	while(cur_e!=*p){
		q=p;p++;
	}
	pre_e=*q;
	return OK;
}
bool NextElem(Sqlist L,Sqtype cur_e,Sqtype &next_e){
	Sqtype *p=L.elem;
	if(cur_e==L.elem[L.length-1]) return ERROR;
	while(*p!=cur_e){
		p++;
	}
	p++;
	next_e=*p;
	return OK;
}
bool ListInsert(Sqlist &L,int i,Sqtype e){
	Sqtype *newbase,*q,*p;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length>=L.listsize){
		newbase=(Sqtype *)realloc(L.elem,(L.listsize+LISTNCREMENT)*sizeof(char));
		if(!newbase) exit(0);
		L.elem=newbase;
		L.listsize+=LISTNCREMENT;
	}
	q=&(L.elem[i-1]);
	for(p=&(L.elem[L.length-1]);p>=q;--p)
	*(p+1)=*p;
	*q=e;
	++L.length;
	return OK;
}
bool ListDelete(Sqlist &L,int i,Sqtype &e){
	Sqtype *p;
	int j;
	if(i<1||i>L.length+1) return ERROR;//i is illegal
	e=L.elem[i-1];
	p=L.elem;
	for(j=i-1;j<L.length;j++)
	*(p+j)=*(p+j+1);
	--L.length;
	return OK; 
}
int visit(char p){
	cout<<p;
	return 1;
}
bool ListTraverse(Sqlist L){
	Sqtype *p=L.elem;
	int j=0;
	while(j<L.length){
		visit(*p);
		p++;
		j++;
	}
	cout<<endl;
	if(j==L.length+1)
	 return OK;
}
