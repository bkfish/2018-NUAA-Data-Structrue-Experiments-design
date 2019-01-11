#include"BiTree.h" 
#include<fstream>
int main() {
	fstream file;
	file.open("test.txt",ios::in);
	if(!file.is_open()){
		cout<<"文件打开失败\n";
		return 0; 
	}
	int n,data;//用于记录输入多少个字符数
	file>>n;
	int number[n]={};
	int i;
	for(i=0;i<n;i++){
		file>>number[i];//向i中输入 
	} 
	BSTree T;
	T=NULL;
	bool taller;
	bool shorter;
	for(i=0;i<n;i++){
		InsertAVL(T,number[i],taller);
	}
	cout<<"中序遍历二叉平衡树\n";
	InOrderTraverse(T);
	cout<<endl;
	cout<<"请输入你想删除的结点\n";
	cin>>data;
	DeleteAVL(T,data,shorter);
	cout<<"删除该节点后中序遍历\n";
	InOrderTraverse(T);
	return 0; 
}
