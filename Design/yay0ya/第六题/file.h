#include<iostream>
using namespace std;
#include<fstream>
void readfile(int number[],char name[]){
	//从文件中读取数据至数组中
	fstream file;
	file.open(name,ios::in);
	for(int i=1;i<=20000;i++){
		file>>number[i];
	}
	file.close();
}
bool LT(int n,int m){
	if(n>m){
		return 1;
	}
	else{
		return 0;
	}
}
bool RT(int n,int m){
	if(n<m){
		return 1;
	}
	else return 0;
}
