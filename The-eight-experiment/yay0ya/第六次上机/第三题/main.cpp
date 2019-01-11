#include"CTree.h"
//生成的是孩子兄弟树 
int main() {
	CSTree T;
	CreateTree(T);
	cout<<"输出树的深度"<<endl;
	SqStack S;
	InitStack(S);
	Push(S,0);
	DFSearch(T,S);
	SElemType *p;
	int max;
	p=S.base;
	max=*p;
	while(p!=S.top){
		if(max<*p)
			max=*p;
		p++;	
	}
	cout<<"树的深度"<<max<<endl;
	return 0;
}
