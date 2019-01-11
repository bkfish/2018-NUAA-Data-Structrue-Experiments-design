#include <iostream>
using namespace std;
#include"traverse.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	BiTree T;
	int count=0;
	InitBiTree(T);
	createBiTree(T);
	cout<<"后序遍历树\n";
	PostOrderTraverse(T);
	cout<<endl;
	PostOrderTraverse2(T); 
	cout<<"中序遍历树\n";
	InOrderTraverse(T);
	cout<<"\n";
	InOrderTraverse2(T);
	cout<<"\n";
	cout<<"先序遍历树\n";
	PreOrderTraverse(T);
	cout<<"\n";
	PreOrderTraverse2(T);
	cout<<"\n";
	cout<<"层次遍历树\n";
	LevelOrderTraverse(T);
	countleaf(T,count);
	cout<<endl;
	cout<<count<<endl; 
	count=Depth(T);
	cout<<count;
}
