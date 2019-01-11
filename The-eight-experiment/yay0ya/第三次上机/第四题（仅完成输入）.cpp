//*********************
//时间：十一月二十四号
//题目：第三章第四题
//作者：姜丹妮
//*******************
#include<stdio.h>
#include<stdlib.h> 
typedef struct{
	int x;
	int y;
}point,*P;
typedef struct{
	point locate1;
	point locate2;
}windows,*W;
typedef struct click{
	windows data;
	click *next;
}*Clicklist;

int main(){
	int N,M;
	int x,y;
	int i=0;
	Clicklist list;
	P check,l;
	printf("请输入窗口个数\n");
	scanf("%d",&N);
	printf("请输入点击次数\n");
	scanf("%d",&M);
	list=(Clicklist)malloc(N*sizeof(click));
	while(i<N){
		printf("请输入窗口的左上坐标\n");
		scanf("%d %d",&x,&y);
		list->data.locate1.x=x;
		list->data.locate1.y=y;
		printf("请输入窗口的右下坐标\n");
		scanf("%d %d",&x,&y);
		list->data.locate2.x=x;
		list->data.locate2.y=y; 
		i++;
	}
	i=0;
	check=(P)malloc(M*sizeof(point));
	l=check;
	while(i<M){
		printf("请输入点击的位置\n");
		scanf("%d %d",&x,&y);
		l->x=x;
		l->y=y;
		l++;
		i++; 
	}
	
	 
} 
