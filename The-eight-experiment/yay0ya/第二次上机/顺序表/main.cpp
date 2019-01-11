#include"list.h"
#include<stdlib.h>
#include<stdio.h>
int main(){
	int i,j,t,temp;//进行计数 
	sqlist a,b,c;
	int *q,*p,*r;
	lineup(a);
	lineup(b);
	if(a.length>b.length)
		temp=a.length;
	else
		temp=b.length;
	c.data=new int [temp];
	c.length=0;
	r=c.data;
	q=a.data;
	p=b.data;
	t=0;
	if(*q>*(p+b.length-1)||*(q+a.length-1)<*p)//如果a列表的第一个值大于b的第最后一个值，则两个没有交集 
	//如果b列表的第一个值大于a 的最后一个，无交集
	{
		c.length=0;
	}
	else{
	for(i=0;i<a.length;i++){
		p=b.data;
		p+=t;
		for(j=t;j<b.length;j++){
			
			if(*q<*p){
				break;
			}
			if(*q==*p){
				*r=*p;	
				c.length++;	
				r++;
				t=j;
				break;
		}
		p++;
		}
		q++;		 
	}
}
	r=c.data;
	if(c.length==0)
	{
		printf("无交集\n");
	}
	else{
	printf("交集为\n"); 
	for(i=0;i<c.length;i++)
	{
		printf("%d ",*r);
		r++;
	}
}
}
