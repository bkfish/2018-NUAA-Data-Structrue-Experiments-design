/*
随机数生成程序
*/ 
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>

using namespace std;


// 打开文件 
FILE* fileOpen(char *fileName, char *method) {
	FILE *fp;
	if((fp=fopen(fileName,method)) == NULL) {
        printf("file cannot be opened\n");
        return NULL;
    }
    else printf("file has been opened\n");
    return fp;
}

// 关闭文件 
void fileClose(FILE *fp) {
	if(fclose(fp) != 0) printf("file cannot be closed\n");
    else printf("file has been closed\n");
    return;
} 


// 遍历数组
void Traverse(int *num, int n) {
	cout<<"\n遍历数组：\n"; 
	for (int i=0; i<n; i++) {
		cout<<num[i]<<" ";
	}
	cout<<endl;
}


int main() {
	int count = 20000, limit = 0;
//	cout<<"请输入想排序的随机数的个数:\n";
//	cin>>count;
	cout<<"请输入这些数的上限(小于等于某个数):\n"; 
	cin>>limit;
	
	FILE *fp = fileOpen("data10.txt", "w");
	
	fprintf(fp, "%d  %d\n", count, limit);
	
	cout<<"生成的无序随机数数组如下：\n";
	int *num = (int*)malloc(sizeof(int) * count);
	srand(time(0));
	for (int i=0; i<count; i++) {
		num[i] = rand()%limit;
		cout<<num[i]<<" ";
		fprintf(fp, "%d  ", num[i]);
	}
	cout<<endl;
	fileClose(fp);
	
	free(num);
}
