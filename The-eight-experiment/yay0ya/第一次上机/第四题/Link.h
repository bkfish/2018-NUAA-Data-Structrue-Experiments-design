#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
typedef struct LNode{
	int id;//表示学生的序号
	int lenghts;//队列的长度
	struct LNode *next; //指向下一个结点 
}LNode,*LinkList;
int InitLink(LinkList &l,int i){
	LNode *p; int j=0;
	l=NULL;
	if(i>MAXSIZE) return ERROR;
	for(j=0;j<i+1;j++){
		p=(LNode*)malloc(sizeof(LNode));
		p->next=l;
		l=p;
	}
	p=l;
	for(j=0;j<i+1;j++){
		p->id=j;
		p->lenghts=i;
		p=p->next;
	}
	return OK;
}
int Moveafter(LinkList &l,int i,int temp)//i表示学生的序号，temp表示学生的向后移动的步数
{
	LNode *p,*q,*r;
	int j=0,count=0; 
	p=l;
	for(j=0;j<l->lenghts;j++){
		if(p->id==i){
			break;//既已经找到该学生 
		}
		q=p;//用q来记录p指针的前一个指针 
		p=p->next;//如果id值不匹配，则该指针向后移动，直到找到该学生 
	}
	r=p;//用指针r来表示学生 
	count=j;//用count来记录现在这个学生排在哪个位置
	if(count>=l->lenghts){
		return ERROR;//如果学生的位置长度大于等于队列的长度，说明不存在这个学生，报错 
	}
	q->next=r->next;//q指针指向移动同学的前面一个同学，r指针指向该学生
		 //前面的同学越过r指针，指向r后面的一个同学 
	if(l->lenghts-(count+temp)<=0)//如果移动步长加上学生现在的位置已经超过或到达队伍末尾时
	{
		p=l->next;
		//则将学生移动到队伍最末尾
		 for(j=0;j<(l->lenghts-2);j++){
		 	p=p->next;
		 }//p指针移动到最末尾；
		 p->next=r;//p是末尾的同学，将r排在p后面 
	 	 r->next=NULL;
	 }
	 else{//如果移动的步长不到达最后一个位置的时候 
		p=l->next;	 	
		for(j=0;j<count+temp-1;j++){
	 		q=p;
	 		p=p->next;
		 }
		 q->next=r;
		 r->next=p;//在这个指针后面位置插入同学r 
	 }
	 return OK;
 } 
 int Movebefore(LinkList &l,int i,int temp)//用i表示学生现在的序号，temp表示向前移动的步数
 {
 	LNode *p,*q,*r;
	int j=0,count=0; 
	p=l->next;
	for(j=0;j<l->lenghts;j++){
		if(p->id==i){
			break;//既已经找到该学生 
		}
		q=p;//用q来记录p指针的前一个指针 
		p=p->next;//如果id值不匹配，则该指针向后移动，直到找到该学生 
	}
	r=p;//用指针r来表示学生 
	count=j;//用count来记录现在这个学生排在哪个位置
	if(count>=l->lenghts){
		return ERROR;//如果学生的位置长度大于等于队列的长度，说明不存在这个学生，报错 
	}
	q->next=r->next;//q指针指向移动同学的前面一个同学，r指针指向该学生
		 //前面的同学越过r指针，指向r后面的一个同学 
	if(count+temp<=0){
		//如果移动temp时，使学生达到头部，或者超过头部
		r->next=l->next;
		l->next=r;//将这个同学设为队伍的头部 
	}
	else {
		p=l->next;
		//如果没有到达队伍的头部
		for(j=0;j<count+temp;j++){
			q=p;
			p=p->next;
		}
		q->next=r;
		r->next=p;//将这个人插到前面 
	}
	return OK;
  } 
