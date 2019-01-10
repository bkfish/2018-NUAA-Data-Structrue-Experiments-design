/*
编写算法判定二叉树是否为完全二叉树
图：
	   A
	 B  C
   D  E   F
	G  H    J
   I  K L 
*/
#include<iostream>
#include<stdlib.h>
#include<math.h>
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
		// cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		// cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
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
	cout<<"销毁树结束\n";
}


// 判断是否为完全二叉树
void IsCompleteBiTree(BiTree bTree, string preOrder) {
	int depth = BiTreeDepth(bTree);
	int count = preOrder.length();
	cout<<"树的深度为："<<depth<<endl;
	cout<<"树的结点数为："<<count<<endl;
	
	// 数学判断 
	if (count < pow((double)2, (double)depth-1)) {
		cout<<"树的结点数 n < 2^(depth-1)，不是完全二叉树\n"; 
		return;
	}
	else {
		queue<BiTree> q;
		q.push(bTree);
		
		// 定义界符 
		BiTree limit = (BTNode*)malloc(sizeof(BTNode) * 1);
		limit->data = ' ';
		limit->lchild = limit->rchild = NULL;
		q.push(limit);
		
		int d = 0, node = 0;  // 树的深度和结点数 
		BiTree top, next;
		while (1) {
			top = q.front();
			q.pop();
			node++;
			
			// 如果q.pop()弹出一个元素后队列为空，说明弹出的是最后一行的最后一个界符 
			if (q.empty()) break;
			else next = q.front();
			
			// 如果得到的是界符 
			if (top->data == ' ') {
				q.push(top);// 将界符放回队列中 
				d++;		// 深度加一 
				node--;		// 结点减一，因为界符不是结点
				// 如果在d行结束时（d不可能到最后一行），不满足结点数  n = 2^d - 1 ，则不是完全二叉树 
				if (pow((double)2, (double)d) - 1 != node) {
					cout<<"由第"<<d<<"行可以看出，该树不是完全二叉树"<<endl;
					return; 
				}
			}
			// 用来判断最后一行：如果 左孩子为空但右孩子不空 或 右孩子空但下一个结点左孩子不空 
			else if ((top->lchild == NULL && top->rchild != NULL) 
					|| (top->rchild == NULL && next->lchild != NULL)) { 
				cout<<"该树不是完全二叉树"<<endl;
				return;
			}
			else {
				if (top->lchild) q.push(top->lchild);
				if (top->rchild) q.push(top->rchild);
			}
		}
	}
	cout<<"该树是完全二叉树\n";
}


int main() {

	// 第一颗树 
	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n先序+中序建树成功\n\n";
	
	// 递归实现 
	cout<<"先序遍历：\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// 检测是否为二叉树 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
	
	
	// 第二颗树 
	preOrder = "ABDHEJCFG";
	inOrder = "HDBJEAFCG";
		
	bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n先序+中序建树成功\n\n";
	
	// 递归实现 
	cout<<"先序遍历：\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// 检测是否为二叉树 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
	
	// 第三颗树 
	preOrder = "ABDHIEJCF";
	inOrder = "HDIBJEAFC";
		
	bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n先序+中序建树成功\n\n";
	
	// 递归实现 
	cout<<"先序遍历：\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"中序遍历：\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// 检测是否为二叉树 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
}
