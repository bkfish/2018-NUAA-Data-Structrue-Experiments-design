#include <iostream>
#include"newtype.h"
#include<fstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open())
	exit(0);
	int N,K,w,s,c;
	file>>N;
	file>>K;
	QNode *p;
	newtype *times;
	times=new newtype[N];
	LinkQueue Q;
	InitQueue(Q);//构造一个队列 
	 
	for(int i=0;i<N;i++){
		EnQueue(Q,i+1);
	}
	int maxtime=0;
	p=Q.front;
	for(int i=0;i<K;i++){
		file>>times[i].w;//w表示使用钥匙编号 
		file>>times[i].s;//s表示使用钥匙的起始时间 
		file>>times[i].c;//c表示使用钥匙的时间长度 
		times[i].count=times[i].c+times[i].s;
		if(maxtime<times[i].count)
			maxtime=times[i].count;//用来记录最大的时长 
	}
	for(int i=0;i<K;i++){
		for(int j=i+1;j<K;j++){
			if(times[i].s>times[j].s){
				changethenumber(times[i],times[j]);
			}
		}
	}
	bool flag1=0,flag2=0;
	int timerecord=times[0].s;//将时间记录为现在的q的时间 
	while(timerecord<=maxtime){
		flag1=0;
		flag2=0;
	for(int i=0;i<K;i++){
		if(times[i].s==timerecord)
			if(outQueue(Q,times[i].w))
				flag1=1;//将该值为w的钥匙取出 
	
	}
		for(int j=0;j<K;j++){
			if(times[j].count==timerecord)//如果放入钥匙的时间与timerecord 的时间相符合，将钥匙放入
				if(putQueue(Q,times[j].w))
					flag2=1; 
		}
		if(flag1||flag2){
		cout<<"现在时间是"<<timerecord<<"钥匙状况为：";
		QueueTraverse(Q);
		cout<<"\n";
		}
	
	timerecord++;
}
	file.close();
	return 0;
}
