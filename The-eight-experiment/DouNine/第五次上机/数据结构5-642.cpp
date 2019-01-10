#include<iostream>
#include<stdlib.h>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef struct BTNode {
	char data;
	BTNode *lchild, *rchild;
}BTNode, *BiTree;


// 先序+中序 建树法
void CreateBiTree(BiTree &bTree, string preOrder, string inOrder) {
	bTree = (BTNode*)malloc(sizeof(BTNode));
	bTree->data = preOrder[0];
	
	int pos = inOrder.find(preOrder[0]);
	string inOrderL = inOrder.substr(0, pos);
	string inOrderR = inOrder.substr(pos + 1, inOrder.length() - 1);
	string preOrderL = preOrder.substr(1, inOrderL.length());
	string preOrderR = preOrder.substr(inOrderL.length() + 1, preOrder.length() - 1);
	
	int isEmptyL = 0, isEmptyR = 0;		// 用来判断左右结点是否为空的标志位 
	if (inOrderL.empty()) {
		bTree->lchild = NULL;
		isEmptyL = 1;
	}
	if (inOrderR.empty()) {
		bTree->rchild = NULL; 
		isEmptyR = 1;
	}
	if (!isEmptyL) {
		cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
}


// 先序遍历，非递归
void preOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return;
	}
	
	cout<<"非递归先序遍历：";
	stack<BTNode> s;
	s.push(*bTree); 
	BTNode temp; 
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<temp.data;
		if (temp.rchild) s.push(*temp.rchild);
		if (temp.lchild) s.push(*temp.lchild);
	}
	cout<<endl;
}


// 销毁树
void DestoryBiTree(BiTree &bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"开始销毁树：\n";
	// 销毁树，只能将树结点指针传进去，因为free要传入的是指针 
	stack<BiTree> s;
	s.push(bTree);
	bTree = NULL;
	BiTree temp;
	
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<"销毁："<<temp->data<<endl;
		if (temp->rchild) s.push(temp->rchild);
		if (temp->lchild) s.push(temp->lchild);
		free(temp);
	}
	cout<<"销毁树结束"<<endl;
}


// 计算树中叶子数
int leafSum(BiTree bTree) {
	int sum = 0;
	if (!bTree->lchild && !bTree->rchild) {
		return 1;
	}
	else {
		if (bTree->lchild) sum += leafSum(bTree->lchild);
		if (bTree->rchild) sum += leafSum(bTree->rchild);
	}
	return sum;
} 

 
int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n建树成功\n\n";
	
	preOrderTraverseOther(bTree);
	cout<<endl;
	
	cout<<"叶子个数为："<<leafSum(bTree)<<endl<<endl; 
	
	// 销毁树 
	DestoryBiTree(bTree);
} 
