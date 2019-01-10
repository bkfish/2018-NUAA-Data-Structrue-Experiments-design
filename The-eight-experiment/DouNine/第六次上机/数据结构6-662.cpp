/*
编程实现，对一棵以孩子-兄弟链表表示的树，求树的深度。
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


// 求树的深度
int GetTreeDepth(CSTree csTree) {
	if (!csTree) {
		cout<<"该树为空！";
		return 0;
	}
	
	queue<CSTree> qA, qB;
	qA.push(csTree);
	
	int depth = 0;
	while (!qA.empty() || !qB.empty()) {
		CSTree temp;
		// 如果队列A不为空 
		if (!qA.empty()) {
			while (!qA.empty()) {
				temp = qA.front();
				qA.pop();
				cout<<temp->data;
				// 如果孩子不为空，则把孩子丢进另一个队列 
				if (temp->firstChild) qB.push(temp->firstChild);
				// 如果兄弟不为空，则把兄弟继续丢进该队列中 
				if (temp->nextSibling) qA.push(temp->nextSibling);
			}
		}
		// 反之，如果队列B不为空 
		else {
			while (!qB.empty()) {
				temp = qB.front();
				qB.pop();
				cout<<temp->data;
				// 同上 
				if (temp->firstChild) qA.push(temp->firstChild);
				if (temp->nextSibling) qB.push(temp->nextSibling);
			}
		}
		depth++;
		cout<<endl;
	}
	return depth;
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
	
	int depth = GetTreeDepth(csTree);
	cout<<"树的深度为："<<depth<<endl<<endl;
	
	cout<<"销毁树\n";
	DestroyCSTree(csTree);
}
