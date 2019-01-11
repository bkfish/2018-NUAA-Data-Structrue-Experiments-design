
#include"file.h"
void insertsortLT(){
	char name[10]="1.txt";
	int i,j;
	int L[20001]={};
	readfile(L,name);
	for(i=2;i<=20000;i++){
		if(LT(L[i],L[i-1])){
			L[0]=L[i];
			L[i]=L[i-1];
		for(j=i-2;LT(L[0],L[j]);--j){
			L[j+1]=L[j];
		}
		L[j+1]=L[0];
	}
	}
	fstream file;
	file.open("12.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close(); 
}
void insertsortRT(){
	char name[10]="1.txt";
	int i,j;
	int L[20001]={};
	readfile(L,name);
	for(i=2;i<=20000;i++){
		if(RT(L[i],L[i-1])){
			L[0]=L[i];
			L[i]=L[i-1];
		for(j=i-2;RT(L[0],L[j]);--j){
			L[j+1]=L[j];
		}
		L[j+1]=L[0];
	}
	}
	fstream file;
	file.open("13.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close(); 
}
