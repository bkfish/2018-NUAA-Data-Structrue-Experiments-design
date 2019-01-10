/*
计算孩子兄弟树的叶子数 
*/
/*
编程实现，对一棵以孩子-兄弟链表表示的树，求树的高度。
*/
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>

using namespace std;

typedef struct CSTNode {
	char data;
	CSTNode *firstChild;
	CSTNode *nextSibling; 
}CSTNode, *CSTree;


// 先序+中序 建树法
void CreateCSTree(CSTree &csTree, string preOrder, string inOrder) {
	csTree = (CSTNode*)malloc(sizeof(CSTNode));
	csTree->data = preOrder[0];
	
	int pos = inOrder.find(preOrder[0]);
	string inOrderL = inOrder.substr(0, pos);
	string inOrderR = inOrder.substr(pos + 1, inOrder.length() - 1);
	string preOrderL = preOrder.substr(1, inOrderL.length());
	string preOrderR = preOrder.substr(inOrderL.length() + 1, preOrder.length() - 1);
	
	int isEmptyL = 0, isEmptyR = 0;		// 用来判断左右结点是否为空的标志位 
	if (inOrderL.empty()) {
		csTree->firstChild = NULL;
		isEmptyL = 1;
	}
	if (inOrderR.empty()) {
		csTree->nextSibling = NULL; 
		isEmptyR = 1;
	}
	if (!isEmptyL) {
		cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateCSTree(csTree->firstChild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateCSTree(csTree->nextSibling, preOrderR, inOrderR);
	}	
}


// 先序遍历，递归
void PreOrderTraverse(CSTree csTree) {
	if (csTree) {
		cout<<csTree->data;
		PreOrderTraverse(csTree->firstChild);
		PreOrderTraverse(csTree->nextSibling);
	} 
}


// 销毁树
void DestroyCSTree(CSTree &csTree) {
	if (!csTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"开始销毁树：\n";
	// 销毁树，只能将树结点指针传进去，因为free要传入的是指针 
	stack<CSTree> s;
	s.push(csTree);
	csTree = NULL; 
	CSTree temp;
	
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<"销毁："<<temp->data<<endl;
		if (temp->nextSibling) s.push(temp->nextSibling);
		if (temp->firstChild) s.push(temp->firstChild);
		free(temp);
	}
	cout<<"销毁树结束";
}


// 求树的叶子数 
int GetTreeLeaves(CSTree csTree) {
	if (!csTree) {
		cout<<"该树为空！";
		return 0;
	}
	
	//cout<<"ok\n"; 
	stack<CSTree> s;
	s.push(csTree);
	CSTree top;
	int leaves = 0;
	while (!s.empty()) {
		//cout<<leaves<<endl;
		top = s.top();
		s.pop();
		if (!top->firstChild && !top->nextSibling) leaves++;
		else {
			if (top->firstChild) s.push(top->firstChild);
			if (top->nextSibling) s.push(top->nextSibling);
		}
	}
	
	return leaves;
} 


int main() {
	string preOrder = "ABFCGJHIKDE";
	string inOrder = "FBJGHKICDEA";
		
	CSTree csTree;
	CreateCSTree(csTree, preOrder, inOrder);
	cout<<"\n建树成功\n\n";
	
	cout<<"先序递归遍历树：\n";
	PreOrderTraverse(csTree);
	cout<<endl<<endl;
	
	int leaves = GetTreeLeaves(csTree);
	cout<<"树的叶子数为："<<leaves<<endl<<endl;
	
	cout<<"销毁树\n";
	DestroyCSTree(csTree);
}
