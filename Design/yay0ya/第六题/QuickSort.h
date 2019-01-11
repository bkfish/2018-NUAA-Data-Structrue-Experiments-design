#include"BubbleSort.h" 
using namespace std;
int QuickSortLT(){
	int PartitionLT(int *p,int low,int high);
	void QsortLT(int *p,int low,int high);
	int *p,low,high;
	int L[20001]={};
	char name[10]="4.txt";
	int i=0,j;
	readfile(L,name);
	QsortLT(L,1,20000);
	
	fstream file;
	file.open("42.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
} 
int QuickSortRT(){
	int PartitionRT(int *p,int low,int high);
	void QsortRT(int *p,int low,int high);
	int *p,low,high;
	int L[20001]={};
	char name[10]="4.txt";
	int i=0,j;
	readfile(L,name);
	QsortRT(L,1,20000);
	
	fstream file;
	file.open("43.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
} 
int PartitionLT(int *p,int low,int high){
	int record=low;
	int flag=p[low];
	while(low<high){
		while(low<high&&p[high]>=flag) 
			high--;
		p[low]=p[high];
		while(low<high&&p[low]<=flag) 
			low++;
		p[high]=p[low];
	}
	p[low]=flag;
	return low;
}
int PartitionRT(int *p,int low,int high){
	int record=low;
	int flag=p[low];
	while(low<high){
		while(low<high&&p[high]<=flag) 
			high--;
		p[low]=p[high];
		while(low<high&&p[low]>=flag) 
			low++;
		p[high]=p[low];
	}
	p[low]=flag;
	return low;
}
void QsortRT(int *p,int low,int high){
	int record;
	if(low<high){
		record=PartitionRT(p,low,high);
		QsortRT(p,low,record-1);
		QsortRT(p,record+1,high);
	}
}
void QsortLT(int *p,int low,int high){
	int record;
	if(low<high){
		record=PartitionLT(p,low,high);
		QsortLT(p,low,record-1);
		QsortLT(p,record+1,high);
	}
}
