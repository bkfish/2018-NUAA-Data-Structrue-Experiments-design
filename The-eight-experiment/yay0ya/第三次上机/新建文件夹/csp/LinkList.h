#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct point{
	int x;
	int y;
}point;
typedef struct window{
	point locate1;
	point locate2;
	int data;
	struct window *next;
}window,*W;
void Createwindows(W &w,int n){
	window *p;
	w=(window*)malloc(sizeof(window));//建立一个
	w->next=NULL;
	int i=0;
	while(i<n){
		p=(window*)malloc(sizeof(window));
		p->data=i+1;
		cin>>p->locate1.x;
		cin>>p->locate1.y;
		cin>>p->locate2.x;
		while(p->locate1.x>p->locate2.x)
		{
			cout<<"input x2 again"<<endl;
			cin>>p->locate2.x;
		 }
		 cin>>p->locate2.y;
		 while(p->locate1.y>p->locate2.y){
		 	cout<<"input y2 again"<<endl;
		 	cin>>p->locate2.y;
		 }
		p->next=w;
		w=p;
		i++;
	}
	
		//输入N个窗口的坐标及值 
}
void CreateClick(point *click,int m){
	int i=0; 
	for(i=0;i<m;i++){
		cin>>click[i].x;
		cin>>click[i].y;
		while(click[i].x<0||click[i].x>2559)
		{
			cout<<"input click x again"<<endl;
			cin>>click[i].x;
		}
		while(click[i].y<0||click[i].y>1439){
			cout<<"input click y again"<<endl;
			cin>>click[i].y ;
		}		
	}
	
}
void idenfy(W&w,int n,point *click,int m){
	window *p,*pre;
	int flag=0;
	window *head;
	head=(window*)malloc(sizeof(window));
	p=w;
	head->next=p;
	pre=head;
	//尾结点为空 
	printf("点击窗口顺序是\n"); 
		for(int j=0;j<m;j++){
			while(p->next!=NULL){

			if(click[j].x>=p->locate1.x&&click[j].x<=p->locate2.x&&click[j].y>=p->locate1.y&&click[j].y<=p->locate2.y){
				//说明这个点击在这个窗口内 
				//需要输出这个窗口的编号，然后将其放在最前面
				printf("%d\n",p->data);
				pre->next=p->next;
				p->next=head->next;
				head->next=p;
				flag=1;
				break;
			}
			pre=p;
			p=p->next;
		}
		if(flag==0)
		printf("ignore"); 
		pre=head;
		p=pre->next;
		flag=0;
		}
}
