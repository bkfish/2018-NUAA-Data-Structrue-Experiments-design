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


// 中序遍历，非递归，曾经算法 
void inOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	} 
	
	cout<<"非递归中序遍历：";
	stack<BTNode> s;
	s.push(*bTree);
	BTNode temp, dataBTree;
	dataBTree.lchild = dataBTree.rchild = NULL;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
			
		if (!temp.lchild && !temp.rchild) cout<<temp.data;
		else {
			dataBTree.data = temp.data;
			
			if (temp.rchild) s.push(*temp.rchild);
			s.push(dataBTree);
			if (temp.lchild) s.push(*temp.lchild);
		}
	}
	cout<<endl;
}


//// 中序遍历，非递归，用后序非递归的方法失败 
//void inOrderTraverseOther(BiTree bTree) {
//	if (!bTree) {
//		cout<<"该树为空！";
//		return; 
//	} 
//	
//	cout<<"非递归中序遍历：";
//	stack<BiTree> s;
//	s.push(bTree);
//	BiTree temp = NULL, top = NULL;
//	while (!s.empty()) {
//		stack<BiTree> t(s);
//		cout<<"\nstack:";
//		while (!t.empty()) {
//			cout<<t.top()->data;
//			t.pop();
//		}
//		cout<<endl;
//		
//		top = s.top();
//		s.pop();		
//			
//		if ((!top->lchild && !top->rchild) || top->lchild == temp) {
//			cout<<top->data;
//			temp = top;
//		}
//		else {			
//			if (top->rchild) s.push(top->rchild);
//			s.push(top);
//			if (top->lchild) s.push(top->lchild);
//		}
//	}
//	cout<<endl;
//}


// 后序遍历，递归 
void postOrderTraverse(BiTree bTree) {
	if(bTree) {
		postOrderTraverse(bTree->lchild);
		postOrderTraverse(bTree->rchild);
		cout<<bTree->data;
	} 
}


//// 后序遍历，非递归，曾经算法 
//void postOrderTraverseOther(BiTree bTree) {
//	if (!bTree) {
//		cout<<"该树为空！";
//		return; 
//	}
//	
//	cout<<"非递归后序遍历：";
//	stack<BTNode> s;
//	s.push(*bTree);
//	BTNode temp, dataBTree;
//	dataBTree.lchild = dataBTree.rchild = NULL;
//	while (!s.empty()) {
//		temp = s.top();
//		s.pop();
//			
//		if (!temp.lchild && !temp.rchild) cout<<temp.data;
//		else {
//			dataBTree.data = temp.data;
//			
//			s.push(dataBTree);
//			if (temp.rchild) s.push(*temp.rchild);
//			if (temp.lchild) s.push(*temp.lchild);
//		}
//	}
//	cout<<endl;
//}


// 后序遍历，非递归
void postOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"非递归后序遍历：";
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp = NULL, top = NULL;	// 定义指向栈顶的top指针，和指向上一个输出节点的temp指针 
	while (!s.empty()) {
		top = s.top();		//  获取栈顶的BiTree指针 
		
		// 若 该指针指向的是一个叶子节点 或者 该节点的左或右孩子已经输出
		if ((!top->lchild && !top->rchild) || top->rchild == temp || top->lchild == temp) {
			cout<<top->data;		// 输出该节点中的值 
			temp = top;				// 将输出节点指针指向该节点 
			s.pop();				// 弹出该元素 
		}
		else {
			if (top->rchild) s.push(top->rchild);
			if (top->lchild) s.push(top->lchild);
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
