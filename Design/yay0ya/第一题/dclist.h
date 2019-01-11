//创建一个双向循环列表。完成数据的存储
#include"linklist.h"
typedef struct record{
	sNode store;//数据结点 
	int sales;//设置销量 
	struct record *pre;
	struct record *next;//pre指向前驱，next指向后继 
}record,*head;
bool createdclist(head &L){
//创造一个双向链表
	head=new record;
	if(head==NULL)
	exit(0);
	head->next=head;
	head->pre=head;
	return 1;
}
bool insertlist(head &L,int id,string name,int credit,int sales){
	//插入一个结点在尾部
	record *p,*s;
	s=new record;
	if(s==NULL)
	{
		cout<<"申请空间失败\n";
		return 0; 
	}
	p=L->pre;//p指向尾结点
	s->store.id=id;
	s->store.name=name;
	s->store.credit=credit;//暂时先将除商品信息的商铺信息存储到链表里面
	s->sales=sales;
	p->next=s;
	s->pre=p;
	s->next=L;//将 s 插到尾结点以后 
	return 1;//完成插入操作  
}
bool lineuplist(head &L,string name,Shop S){
	//进行排队插入操作
	 sNode *p;
	 p=S;
	 goods goodp;//设置商品指针 
	 while(p!=NULL){
	 	goodp=p->goods.data;
	 	for(int i=0;i<p->goods.numbers;i++){
	 		if(goodp.name==name){
	 			insertlist(L,p->id,p->name,p->credit,goodp.sold);
	 			//如果该商品中有此类需要排序的商品
				  //将商品插入创造的商品链表
			  
			 }
			 	p++; 
		 }
		 p=p->next;
	 }//将所有包含给商品的商铺插入链表中，完成了双向链表 
} 
