#include"Queue.h"
typedef struct newtype{
	int w;
	int s;
	int c;
	int count;
}newtype;
Status changethenumber(newtype &q,newtype &p){
	int temp;
	temp=q.w;
	q.w=p.w;
	p.w=temp;
	temp=q.s;
	q.s=p.s;
	p.s=temp;
	temp=q.c;
	q.c=p.c;
	p.c=temp;
	temp=q.count;
	q.count=p.count;
	p.count=temp;
}
