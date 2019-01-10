/*
实现二叉排序树的插入和删除。
10
100 24 3 45 12  53 37 78 61 90
*/
#include<iostream>
#include<cstdlib>
#include<queue>

using namespace std;

typedef struct BTNode {
	int data;
	BTNode *lchild, *rchild;
}BTNode, *BiTree;


// 插入结点
void InsertBTree(BiTree &bTree, int data) {
	cout<<"插入数值："<<data<<endl;
	BTNode *p = bTree, *temp;
	while (1) {
		if (data < p->data) {
			if (p->lchild) p = p->lchild;
			else {
				temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = data;
				temp->lchild = temp->rchild = NULL;
				p->lchild = temp;
				break; 
			}
		} 
		else if (data > p->data) {
			if (p->rchild) p = p->rchild;
			else {
				temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = data;
				temp->lchild = temp->rchild = NULL;
				p->rchild = temp;
				break;
			}
		} 
		else break;
	}
	cout<<"插入成功\n";
}


// 删除结点
int DeleteBTree(BiTree &bTree, int data) {
	BTNode *cur, *pre;
	cur = pre = bTree;
	while (1) {
		// 如果当前指针指向空结点，那么没找到这个值
		if (!cur) break;
		// 如果找到了这个值
		if (cur->data == data) {
			// 如果删去的结点没有孩子 
			if (!cur->lchild && !cur->rchild) {
				// 如果删的点是根 
				if (bTree->data == data) bTree = NULL;
				
				if (pre->lchild == cur) pre->lchild = NULL;
				else pre->rchild = NULL;
			}
			// 如果删去的结点有两个孩子 
			else if (cur->lchild && cur->rchild) {
				// 找到以该结点左孩子为根节点的子树中的最大值（即小于该值的数中的最大值） 
				BTNode *cur2, *pre2;
				pre2 = cur;		// per2此处一定要等于cur，不是cur->lchild。这个在Delete时很关键 
				cur2 = cur->lchild;
				while (cur2->rchild) {
					pre2 = cur2;
					cur2 = pre2->rchild;
				}
				// pre2不能等于cur2，不然如果出现要删的点为根节点的情况时，就不能将上一个结点的该孩子指针置为NULL 
				int tempData = DeleteBTree(pre2, cur2->data);	
				
				// 将找到的最大值结点取代要删除结点的位置 
				BTNode *temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = tempData;
				temp->lchild = cur->lchild;
				temp->rchild = cur->rchild;
				
				// 特殊情况，要删除的结点是根
				if (bTree->data == data) bTree = temp;
				if (pre->lchild == cur) pre->lchild = temp;
				else pre->rchild = temp;
			}
			// 最后一种情况，该结点只有一个孩子 
			else {
				// 找到不为空的孩子 
				BTNode *temp;
				if (cur->lchild) temp = cur->lchild;
				else if (cur->rchild) temp = cur->rchild;
				// 将该孩子取代这个结点的位置 
				// 要删除的结点为根时
				if (bTree->data == data) {
					bTree = temp;
				}
				if (pre->lchild == cur) pre->lchild = temp;
				else pre->rchild = temp;
			}
			break;
		}
		else if (cur->data > data) {
			pre = cur;
			cur = cur->lchild;
		} 
		else if (cur->data < data) {
			pre = cur;
			cur = cur->rchild;
		}
	}
	int temp = cur->data;
	free(cur);
	cout<<"删除成功，删除的值为："<<temp<<endl; 
	return temp;
}
 

// 建二叉排序树 
void CreateBTree(BiTree &bTree) {
	cout<<"请输入要新建的数的个数：\n";
	int n = 0;
	cin>>n;
	cout<<"请依次输入每个数：\n";
	bTree = (BTNode*)malloc(sizeof(BTNode));
	cin>>bTree->data;
	bTree->lchild = NULL;
	bTree->rchild = NULL;
	int data = 0;
	for (int i=0; i<n-1; i++) {
		cin>>data;
		InsertBTree(bTree, data);
	}
}


// 销毁二叉排序树 
void DestoryBTree(BiTree &bTree) {
	if (bTree) {
		DestoryBTree(bTree->lchild);
		DestoryBTree(bTree->rchild);
		free(bTree);
	}
}


// 中序遍历二叉排序树，即顺序输出数据
void InOrderBTree(BiTree bTree) {
	if (bTree) {
		InOrderBTree(bTree->lchild);
		cout<<bTree->data<<"  ";
		InOrderBTree(bTree->rchild);
	}
}


// 层次遍历，非递归 
void LevelOrderTraverse(BiTree bTree) {
	if (!bTree) {
		cout<<"该树为空！";
		return; 
	}
	
	cout<<"\n层次遍历：";
	queue<BiTree> q;
	q.push(bTree);
	BiTree temp;
	while (!q.empty()) {
		temp = q.front();
		cout<<temp->data<<" ";
		if (temp->lchild) q.push(temp->lchild);
		if (temp->rchild) q.push(temp->rchild);
		q.pop();
	}
	cout<<endl;
} 


int main() {
	BiTree bTree;
	CreateBTree(bTree);
	cout<<"\n中序遍历，顺序输出：\n";
	InOrderBTree(bTree);
	LevelOrderTraverse(bTree);
	cout<<"\n请输入要删除的数据：\n";
	int data;
	cin>>data;
	DeleteBTree(bTree, data);
	//if (bTree) cout<<"删根失败"<<bTree<<"\n";
	cout<<"\n中序遍历，顺序输出：\n";
	InOrderBTree(bTree);
	LevelOrderTraverse(bTree);
	DestoryBTree(bTree);
}



