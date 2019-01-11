//随机函数，以用来产生十个样本
#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#include<time.h>
int main(){
	srand(time(NULL));
	int i;
	char filename[10][10]={"1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt","9.txt","10.txt"};
		fstream file;
	for(int j=0;j<10;j++){
		file.open(filename[j],ios::out);
		if(!file.is_open())
		cout<<"文件打开失败\n";	
			for(i=0;i<20000;i++)
			file<<rand()<<" ";
		file.close();	
	}
	return 0;
} 

