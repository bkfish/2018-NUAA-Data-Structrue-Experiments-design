#include<stdio.h>
#include"list.h"
bool reverseList(Sqlist &L){
	char p;
	int i=0;
	for(i=0;i<L.length/2;i++){
		p=L.elem[i];
		L.elem[i]=L.elem[L.length-i-1];
		L.elem[L.length-i-1]=p;
	}
	return OK;
}
int main(){
	Sqlist l;
	int n=0,i=0;
	char c,ch;
	printf("创建一个顺序表\n");
	InitList_Sq(l);
	printf("请输入你想输入的值的数量\n");
	scanf("%d",&n);
	printf("请输入你需要输入的值\n");
	getchar();
	while(i<n){
		scanf("%c",&l.elem[i]);
		i++;
		l.length++;
		getchar();
	}
	ListTraverse(l); 
	printf("该队列的长度是%d",ListLength(l));
	printf("请输入你想插入的值,以及它的位置\n");
	scanf("%c%d",&c,&i);
	ListInsert(l,i,c);
	ListTraverse(l);
	printf("请输入你想删除的值的位置\n");
	scanf("%d",&i);
	ListDelete(l,i,c);
	printf("删除的值是%c",c);
	printf("请输入位置\n");
	scanf("%d",&i);
	GetElem(l,i,c);
	printf("该位置上面的值是%c",c);
	PriorElem(l,c,ch);
	printf("该位置前面的值是%c",ch);
	NextElem(l,c,ch); 
	printf("该位置后面的值是%c",ch);
	printf("请输入你需要查找的值\n");
	getchar();
	scanf("%c",&c);
	i=LocateElem(l,c); 
	printf("该位置是%d，如果为0表示该值不存在",i);
	cout<<"输出逆向元\n";
	reverseList(l);
	ListTraverse(l); 
	
}
