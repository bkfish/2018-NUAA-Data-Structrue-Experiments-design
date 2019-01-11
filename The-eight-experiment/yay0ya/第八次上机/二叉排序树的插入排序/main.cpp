#include<iostream>
using namespace std;
//完成二叉排序树的插入与删除
#include"InsertDelete.h"
int main(){
	BiTree T;
	int n;
	createBiTree(T);
	cout<<"输入要插入的值"<<endl; 
	cin>>n;
	InsertBST(T,n);
	cout<<"中序遍历结果"<<endl;
	InOrderTraverse(T);
	cout<<"输入要删除的值"<<endl;
	cin>>n;
	DeleteBST(T,n);
	cout<<"中序遍历结果"<<endl; 
	InOrderTraverse(T);
	return 0;
} 
