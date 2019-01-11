#include"ShellSort.h"
void BubbleSortLT(){
	int L[20001]={};
	char name[10]="3.txt";
	int i=0,j;
	readfile(L,name);
	for(i=1;i<=20000;i++){
		for(j=i+1;j<=20000;j++){
			if(LT(L[i],L[j])){
				int temp;
				temp=L[i];
				L[i]=L[j];
				L[j]=temp;
			}
		}
	} 
		fstream file;
	file.open("32.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}
void BubbleSortRT(){
	int i=0,j;
	int L[20001]={};
	char name[10]="3.txt";
	readfile(L,name);
	for(i=1;i<=20000;i++){
		for(j=i+1;j<=20000;j++){
			if(RT(L[i],L[j])){
				int temp;
				temp=L[i];
				L[i]=L[j];
				L[j]=temp;
			}
		}
	} 
		fstream file;
	file.open("33.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}

