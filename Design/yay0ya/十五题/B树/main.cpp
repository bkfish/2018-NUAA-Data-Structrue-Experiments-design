#include"BTree.h"
int main() {
	BTree T;
	T=NULL;
	Result s;
	fstream file;
	file.open("test.txt",ios::in);
	if(!file.is_open()){
		cout<<"文件打开失败\n";
		return 0;
	} 
	int n;
	file>>n;
	int number[n]={};
	for(int i=0;i<n;i++){
		file>>number[i];
		s=SearchBTree(T,number[i]);
		if(s.tag==0){
			InsertBTree(T,number[i],s.pt,s.i);
		}
	}//完成插入
	BTreeTraverse(T);
	cout<<"输入需要删除的值\n";
	cin>>n; 
	BTNodeDelete(T,n);
	BTreeTraverse(T);
}
