/* 
实现二叉树的先序、中序、后序遍历，用递归和非递归方法；实现层次遍历。
图：
	   A
	 B  C
   D  E   F
	G  H    J
   I  K L 
*/
#include<iostream>
#include<stdlib.h>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef struct BTNode {
	char data;
	BTNode *lchild, *rchild;
}*BiTree;


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


// 先序遍历，递归
void preOrderTraverse(BiTree bTree) {
	if (bTree) {
		cout<<bTree->data;
		preOrderTraverse(bTree->lchild);
		preOrderTraverse(bTree->rchild);
	} 
}


// 先序遍历，非递归
void preOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return;
	}
	
	cout<<"非递归先序遍历：";
	stack<BiTree> s;
	s.push(bTree); 
	BiTree temp; 
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<temp->data;
		if (temp->rchild) s.push(temp->rchild);
		if (temp->lchild) s.push(temp->lchild);
	}
	cout<<endl;
}


// 中序遍历，递归 
void inOrderTraverse(BiTree bTree) {
	if (bTree) {
		inOrderTraverse(bTree->lchild);
		cout<<bTree->data;
		inOrderTraverse(bTree->rchild);
	} 
}


// 中序遍历，非递归 
void inOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	} 
	
	cout<<"非递归中序遍历：";
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
			
		if (!temp->lchild && !temp->rchild) cout<<temp->data;
		else {
			// 定义一个没有孩子，专门用来存数据的树，此处每次都要申请空间。 
			// dataBTree->data = temp->data;  
			// 上面是错误范例。因为每次将该指针值压入栈中，如果在此处修改该指针指向的内存区域的值，
			// 那么，栈中指针指向的内存区域中的值也会被修改。 
			BiTree dataBTree = (BTNode*)malloc(sizeof(BTNode));
			dataBTree->data = temp->data;
			dataBTree->lchild = NULL;
			dataBTree->rchild = NULL;
			
			/*sTemp = s;
			cout<<"\n4-------"; 
			while (!sTemp.empty()) {
				cout<<sTemp.top()->data;
				sTemp.pop();
			}
			cout<<endl;*/
			
			if (temp->rchild) s.push(temp->rchild);
			s.push(dataBTree);
			if (temp->lchild) s.push(temp->lchild);
		}
	}
	cout<<endl;
}


// 后序遍历，递归 
void postOrderTraverse(BiTree bTree) {
	if(bTree) {
		postOrderTraverse(bTree->lchild);
		postOrderTraverse(bTree->rchild);
		cout<<bTree->data;
	} 
}


// 后序遍历，非递归
void postOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"非递归后序遍历：";
	stack<BiTree> s;
	s.push(bTree);	
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		
		if (temp->lchild == NULL && temp->rchild == NULL) {
			cout<<temp->data;
		}
		else {
			BiTree dataBTree = (BTNode*)malloc(sizeof(BTNode));	// 定义一个没有孩子，专门用来存数据的树 
			dataBTree->data = temp->data;
			dataBTree->lchild = NULL;
			dataBTree->rchild = NULL;
			
			s.push(dataBTree);
			if (temp->rchild) s.push(temp->rchild);
			if (temp->lchild) s.push(temp->lchild);
		}
	} 
	cout<<endl;
}


// 层次遍历
void levelOrderTraverse(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"层次遍历：";
	queue<BiTree> q;
	q.push(bTree);
	BiTree temp;
	while (!q.empty()) {
		temp = q.front();
		cout<<temp->data;
		if (temp->lchild) q.push(temp->lchild);
		if (temp->rchild) q.push(temp->rchild);
		q.pop();
	}
	cout<<endl;
} 


// 销毁树
void DestoryBiTree(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"开始销毁树：\n";
	BiTree temp = bTree;
	cout<<"销毁："<<temp->data<<endl;
	stack<BiTree> s;
	if (bTree->rchild) s.push(bTree->rchild);
	if (bTree->lchild) s.push(bTree->lchild);
	free(temp);
	
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<"销毁："<<temp->data<<endl;
		if (temp->rchild) s.push(temp->rchild);
		if (temp->lchild) s.push(temp->lchild);
		free(temp);
	}
	cout<<"销毁树结束";
}


int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n建树成功\n\n";
	
	// 递归实现 
	cout<<"先序遍历：";
	preOrderTraverse(bTree);
	cout<<endl;
	
	cout<<"中序遍历：";
	inOrderTraverse(bTree);
	cout<<endl;
	
	cout<<"后序遍历：";
	postOrderTraverse(bTree);
	cout<<endl<<endl;
	
	// 非递归实现 
	preOrderTraverseOther(bTree);
	inOrderTraverseOther(bTree);
	postOrderTraverseOther(bTree);
	cout<<endl;
	
	// 层次遍历
	levelOrderTraverse(bTree);
	cout<<endl;
	
	// 销毁树 
	DestoryBiTree(bTree);
} 
