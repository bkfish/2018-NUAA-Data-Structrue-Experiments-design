#include"BTree.h"
int main() {
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open())
	{
		cout<<"文件打开失败\n";
		return 0; 
	}
	BTree T;
	int n;
	file>>n;//输入关键词的个数
	int character[n];
	for(int i=0;i<n;i++){
		file>>character[i];
		BTreeInsert(character[i],T);
	}
	BTreeTraverse(T);
	return 0;
	 
}
