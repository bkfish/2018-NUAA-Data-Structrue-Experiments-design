#include"HeapSort.h"
#define RADIX 10//¹Ø¼ü×Ö»ùÊý
#define MAX_SPACE  20000

int findmax(int L1[],int n){
	int max=L1[1];
	for(int i=2;i<n;i++){
		if(L1[i]>max)
			max=L1[i];
	}
	return max;
} 
int getlooptimes(int max){
	int count=1;
	max=max/10;
	while(max!=0){
		count++;
		max=max/10;
	}
	return count;
}
void sort(int L[],int n,int i){
	int bucket[10][MAX_SPACE]={};
	int j=0,temp=1;
	while(j<i){
		temp*=10;
		j++; 
	}
	int record=0;
	for(j=1;j<n;j++){
		record=(L[j]/temp)%10;
		for(int k=0;k<MAX_SPACE;k++){
			if(bucket[record][k]==0){
				bucket[record][k]=L[j];
				break;
			}
		}
	}
	int m=1;
	for(j=0;j<10;j++){
		for(int k=0;k<MAX_SPACE;k++){
			if(bucket[j][k]!=0){
				L[m]=bucket[j][k];
				bucket[j][k]=0;
				m++;
			}
		}
	}
}
void RadixSort(){
	int n=20001;
  	int L1[20001]={};
	char name[10]="8.txt";
	int i=0,j;
	int max,timeloop;
	readfile(L1,name);
	max=findmax(L1,n); 
	timeloop=getlooptimes(max);
	for(i=0;i<timeloop;i++){
		sort(L1,n,i);
	}
		fstream file;
	file.open("82.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L1[i]<<" ";
	}
	file.close();
}
