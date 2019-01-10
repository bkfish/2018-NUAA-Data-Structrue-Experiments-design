/* 
编程实现书P121  ADT BinaryTree 基本操作20个，用二叉链表结构实现；
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
	
	bool isEmptyL = false, isEmptyR = false;		// 用来判断左右结点是否为空的标志位 
	if (inOrderL.empty()) {
		bTree->lchild = NULL;
		isEmptyL = true;
	}
	if (inOrderR.empty()) {
		bTree->rchild = NULL; 
		isEmptyR = true;
	}
	if (!isEmptyL) {
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
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
	cout<<"销毁树结束\n\n";
}


// 判断树是否为空 
bool BiTreeEmpty(BiTree bTree) {
	if (bTree) return false;
	else return true;
}


// 返回树的深度，递归 
int BiTreeDepth(BiTree bTree) {
	if (bTree) {
		int lchildDepth = 0;
		if (bTree->lchild) lchildDepth = BiTreeDepth(bTree->lchild);
		int rchildDepth = 0;
		if (bTree->rchild) rchildDepth = BiTreeDepth(bTree->rchild);
		return lchildDepth > rchildDepth ? lchildDepth+1 : rchildDepth+1;
	}
	return 0;
}


// 返回树的根 
char Root(BiTree bTree) {
	return bTree->data;
}


// 返回结点 bTNode 的值
char Value(BiTree bTree, const BTNode* bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			return temp->data;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return '\0';
}
 

// 给结点 bTNode 赋值为value
bool Assign(BiTree bTree, BTNode *bTNode, char value) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			temp->data = value;
			return true;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return false;
}


// 返回结点 bTNode 的双亲
BTNode* Parent(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL;
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp->lchild == bTNode) return temp;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp->rchild == bTNode) return temp;
			s.push(temp->rchild);
		}
	}
	return NULL;
}
 

// 返回结点 bTNode 的左孩子
BTNode* LeftChild(BiTree bTree, BTNode *bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp == bTNode) return temp->lchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			s.push(temp->rchild);
		}
	}
	return NULL;
} 


// 返回结点 bTNode 的左孩子
BTNode* RightChild(BiTree bTree, BTNode *bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp == bTNode) return temp->rchild;
			s.push(temp->rchild);
		}
	}
	return NULL;
} 


// 返回结点 bTNode 的左兄弟 
BTNode* LeftSibling(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL; 
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp->rchild == bTNode && temp->lchild) return temp->lchild;
			s.push(temp->rchild);
		}
	}
	return NULL;
}


// 返回结点 bTNode 的右兄弟
BTNode* RightSibling(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL; 
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp->lchild == bTNode && temp->rchild) return temp->rchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			s.push(temp->rchild);
		}
	}
	return NULL;
}


// 将树insertBTree插入到树BTree的bTNode结点的左或右(condition=0或1)子树中 
bool InsertChild(BiTree bTree, const BTNode *bTNode, int condition, BiTree insertBTree) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp, tempLChild = NULL, tempRChild = NULL;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			tempLChild = temp->lchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			tempRChild = temp->rchild;
			s.push(temp->rchild);
		}
		if (temp == bTNode) {
			if (temp->lchild && temp->rchild) return false;
			if (condition) {
				temp->rchild = insertBTree;
				insertBTree->rchild = tempRChild;
			}
			else {
				temp->lchild = insertBTree;
				insertBTree->rchild = tempLChild;
			}
			return true; 
		}
	}
	return false;
}


// 删除BTNode结点的左或右子树(condition=0或1)
bool DeleteChild(BiTree bTree, BTNode *bTNode, int condition) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp, tempChild;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			if (condition) {
				DestoryBiTree(temp->rchild);
			}
			else {
				DestoryBiTree(temp->lchild);
			}
			return true;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return false;
}


// 先序遍历，递归
void PreOrderTraverse(BiTree bTree, int tab) {
	if (bTree) {
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
		PreOrderTraverse(bTree->lchild, tab+1);
		PreOrderTraverse(bTree->rchild, tab+1);
	} 
}


// 中序遍历，递归 
void InOrderTraverse(BiTree bTree, int tab) {
	if (bTree) {
		InOrderTraverse(bTree->lchild, tab+1);
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
		InOrderTraverse(bTree->rchild, tab+1);
	} 
}


// 后序遍历，递归 
void PostOrderTraverse(BiTree bTree, int tab) {
	if(bTree) {
		PostOrderTraverse(bTree->lchild, tab+1);
		PostOrderTraverse(bTree->rchild, tab+1);
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
	} 
}


// 层次遍历，非递归 
void LevelOrderTraverse(BiTree bTree) {
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


int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n建树成功\n\n";
	
	// 递归实现 
	cout<<"先序遍历：\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"后序遍历：\n";
	PostOrderTraverse(bTree, 0);
	cout<<endl<<endl;
	
	// 返回树的深度 
	cout<<"树的深度："<<BiTreeDepth(bTree);
	cout<<endl<<endl;
	
	// 层次遍历
	LevelOrderTraverse(bTree);
	cout<<endl;
	
	// 测试获取值 
	BTNode *bTNode = bTree->lchild->rchild->rchild;
	cout<<"测试结点的值为："<<Value(bTree,  bTNode)<<endl;
	cout<<"修改测试结点的值为X\n";
	Assign(bTree, bTNode, 'X');
	cout<<"测试结点的值为："<<Value(bTree,  bTNode)<<endl;
	cout<<"测试结点的双亲值为："<<Value(bTree, Parent(bTree,  bTNode))<<endl;
	cout<<"测试结点的左孩子值为："<<Value(bTree, LeftChild(bTree,  bTNode))<<endl;
	cout<<"测试结点的右孩子值为："<<Value(bTree, RightChild(bTree,  bTNode))<<endl;
	cout<<"测试结点的左兄弟值为："<<Value(bTree, LeftSibling(bTree,  bTNode))<<endl;
	cout<<"测试结点的右兄弟值为："<<Value(bTree, RightSibling(bTree,  bTNode))<<endl<<endl;
	
	cout<<"中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// 测试插入和删除
	preOrder = "QYZ";
	inOrder = "ZYQ";
	BiTree insertBTree;
	CreateBiTree(insertBTree, preOrder, inOrder);
	cout<<"\n建插入树成功\n\n";
	
	cout<<"中序遍历插入树：\n";
	InOrderTraverse(insertBTree, 0);
	cout<<endl;
	
	bTNode = bTree->lchild->rchild->lchild;
	InsertChild(bTree, bTNode, 0, insertBTree);
	
	cout<<"插入树后中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	DeleteChild(bTree, bTNode, 0);
	cout<<"删除树后中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// 销毁树 
	DestoryBiTree(bTree);
}
