#include<iostream>
using namespace std;
#define LIST_INIT_SIZE  100
typedef int Sqtype;
typedef struct {
	Sqtype *elem;
	int length;//当前长度
	int listsize;//当前分配存储容量 
} Sqlist;
void selectsort(Sqlist &l){
	int SelectMinKey(Sqlist l,int i);
	for(int i=0;i<l.length;i++){
		int j=SelectMinKey(l,i);//从i开始对该排序中的所有数值中选择一个最小值的下标
		if(i!=j){
			int temp;
			temp=l.elem[i];
			l.elem[i]=l.elem[j];
			l.elem[j]=temp;//如果i！=j  进行交换表示现在的i不是排序中的最小值 
		} 
	}
}//selectsort
int SelectMinKey(Sqlist l,int i){
	int flag=i;
	for(int j=i+1;j<l.length;j++){
		if(l.elem[j]<l.elem[flag])
			flag=j;		
	}
	return flag;
} 
int main(){
	int n;
	cin>>n;
	Sqlist l;
	l.length=n;
	l.elem=new int[n];
	Sqtype *q;
	q=l.elem;
	for(int i=0;i<n;i++){
		cin>>*q;
		q++;
	}
	selectsort(l);
	q=l.elem;
	for(int i=0;i<n;i++){
		cout<<*q<<" ";
		q++; 
	}
	return 0;
}
