#include<iostream>
using namespace std;
typedef struct sqlist{
	int *data;
	int length;
}sqlist;
void lineup(sqlist &list){
	int n;
	cout<<"输入你需要表的长度\n";
	cin>>n;
	list.data=new int[n];
	cout<<"输入你需要录入的值\n"; 
	for(int i=0;i<n;i++){
		cin>>list.data[i];
	}
	list.length=n;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(list.data[i]>list.data[j]){//如果前一个比后一个大。交换位置 
				int temp;
				temp=list.data[i];
				list.data[i]=list.data[j];
				list.data[j]=temp;
			}
		//跳出循环对下一个数进行查找 
		}
	}
	cout<<"排序后输出的值\n"; 
	for(int i=0;i<n;i++){
		cout<<list.data[i]<<"\n";
	} 
} 
