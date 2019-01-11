#include"Delete.h"
int main(){
	BiTree T1,T2;
	InitBiTree(T1);
	cout<<"请输入二叉树的各个结点分支，以-1表示结束\n"; 
	createBiTree(T1);
	cout<<"先序遍历结果\n"; 
	PreOrderTraverse(T1);
	cout<<endl;
	cout<<"后序遍历结果\n"; 
	PostOrderTraverse(T1);
	cout<<endl;
	cout<<"中序遍历结果\n";
	InOrderTraverse(T1);
	/*cout<<"再创造一个树";
	InitBiTree(T2);
	cout<<"请输入二叉树的各个结点分支，以-1表示结束\n";
	createBiTree(T2);*/
	BiTNode temp,*p;
	cout<<"输入你要在T1查找的值\n"; 
	cin>>temp.data;
	p=RightSibling(T1,temp);
	if(p!=NULL){
		cout<<"它的右兄弟是";
		cout<<p->data;
	}
	if(p==NULL){
		cout<<"它不存在右兄弟或者不存在该值\n";
	}
	cout<<"请再输入一个值\n";
	cin>>temp.data;
	p=LeftSibling(T1,temp);
	if(p!=NULL){
		cout<<"它的左兄弟是";
		cout<<p->data;
	}
	if(p==NULL){
		cout<<"它不存在左兄弟或者不存在该值\n";
	}
	cout<<"输入一个节点值\n";
	BiTNode node;
	cin>>node.data;
	node.lchild=NULL;
	node.rchild=NULL;
	cout<<"现在p指向的值为\n"; 
	cout<<p->data;
	cout<<"现在将结点插入到p所指位置的右孩子上面"; 
	InsertChild(T1,p,1,&node);
	cout<<"中序遍历结果是\n";
	InOrderTraverse(T1);
	cout<<"现在p指向的值为\n";
	cout<<p->data;
	cout<<"删除p所指向的右结点\n";
	DeleteChile(T1,p,1);
	cout<<"中序遍历结果是\n";
	InOrderTraverse(T1);
	cout<<"输入一个存在于树中的一个节点值\n"<<endl;
	cout<<"p指向输入结点的左兄弟，以下删除p所在的结点的左右子树\n" ; 
	cin>>temp.data;
	p=LeftSibling(T1,temp);
	cout<<"p是"<<p->data<<"\n"; 
	cout<<"删除先在这p所在结点的左右子树\n"; 
	Deletechild(T1,p);
	InOrderTraverse(T1);
	return 0;
}

