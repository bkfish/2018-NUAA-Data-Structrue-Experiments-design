#include"InsertSort.h"
void ShellInsertLT(int L[],int dk){
	int i=0,j;
	for(i=dk+1;i<=20000;i++){
		if(LT(L[i],L[i-dk])){
			L[0]=L[i];
		
		for(j=i-dk;j>0&&LT(L[0],L[j]);j-=dk){
			L[j+dk]=L[j];
		}
		L[j+dk]=L[0];
	}
	}
}
void ShellSortLT(){
	int L[20001]={};
	char name[10]="2.txt";
	readfile(L,name);
	int dlta[]={50,42,35,29,24,20,17,15,12,10,8,9,4,3,2,1};
	int k,i;
	for(k=0;k<16;k++){
		ShellInsertLT(L,dlta[k]);
	}
		fstream file;
	file.open("22.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}
void ShellInsertRT(int L[],int dk){
	int i=0,j;
	for(i=dk+1;i<=20000;i++){
		if(RT(L[i],L[i-dk])){
			L[0]=L[i];
		
		for(j=i-dk;j>0&&RT(L[0],L[j]);j-=dk){
			L[j+dk]=L[j];
		}
		L[j+dk]=L[0];
	
}
}
}
void ShellSortRT(){
	int L[20001]={};
	char name[10]="2.txt";
	readfile(L,name);
	int dlta[]={50,42,35,29,24,20,17,15,12,10,8,9,4,3,2,1};
	int k,i;
	for(k=0;k<16;k++){
		ShellInsertRT(L,dlta[k]);
	}
		fstream file;
	file.open("23.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}
