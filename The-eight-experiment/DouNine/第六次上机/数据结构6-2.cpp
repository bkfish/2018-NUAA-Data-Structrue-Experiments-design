/*
输入N个权值（1-100正整数），建立哈夫曼树。
8
5 29 7 8 14 23 3 11
*/
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<stack>
using namespace std;

typedef struct {
	int weight;
	int parent;
	int lchild, rchild;
}HuffmanTree;

// 建哈夫曼树表
void CreateHuffmanTree(HuffmanTree * &hTree, int n, int m) {
	// 经过n-1次找两个最小值 
	for (int i=1; i<=n-1; i++) {
		int fMin = INT_MAX, sMin = INT_MAX-1;	// 初始化第一小和第二小的权值 
		int fMinP = 0, sMinP = 0;            	// 权值第一小和第二小的位置 
		int j = 1;
		// 遍历所有已经有权值的结点 
		while (j<m && hTree[j].weight) {
			// 如果该结点没有双亲，且权值小于第二小的权值 
			if ((!hTree[j].parent) && (hTree[j].weight < sMin)) {
				// 如果该权值小于第一个小的权值 
				if (hTree[j].weight < fMin) {
					sMin = fMin;
					sMinP = fMinP; 
					fMin = hTree[j].weight;
					fMinP = j;
				}
				// 如果在第一和第二小权值中间 
				else {
					sMin = hTree[j].weight;
					sMinP = j;
				}
			}
			j++;
		}
		// j最后停在没有权值的新结点的那一行，将上述两个结点变为新结点的孩子 
		if (j < m) {

			hTree[fMinP].parent = j;
			hTree[sMinP].parent = j;
			
			hTree[j].lchild = fMinP;
			hTree[j].rchild = sMinP;
			hTree[j].weight = fMin + sMin;
		}
	}
	
	cout<<"建哈夫曼树成功:\n";
	for (int i=1; i<m; i++) {
		cout<<hTree[i].weight<<" "<<hTree[i].parent<<" "<<hTree[i].lchild<<" "<<hTree[i].rchild<<endl;
	}
}


// 显示哈夫曼编码 
void ShowHuffmanCoding(HuffmanTree *hTree, int n, int m) {
	vector< stack<char> > hCode;
	stack<char> temp;
	// 从结点开始找双亲 
	for (int i=1; i<=n; i++) {
		cout<<i<<endl;
		int j = i;
		int parent = hTree[i].parent;	// 找到双亲
		// 当双亲不为空，即没有到头 
		while (parent) {
			// 如果该结点是双亲的左孩子 
			if (hTree[parent].lchild == j) temp.push('0');
			// 如果是右孩子 
			else temp.push('1');
			j = parent;
			parent = hTree[j].parent;
		}
		hCode.push_back(temp);
		while (!temp.empty()) temp.pop();
	}
	
	for (int i=0; i<n; i++) {
		cout<<"第"<<i+1<<"个数的权值为："<<hTree[i+1].weight<<"，编码为：";
		while (!hCode[i].empty()) {
			cout<<hCode[i].top();
			hCode[i].pop();
		}
		cout<<endl;
	}
}


int main() {
	printf("请输入要输入的权值的个数:");
	int n = 0;
	scanf("%d", &n);
	
	// 初始化哈夫曼树线性表 
	int m = 2 * n;
	HuffmanTree *hTree = (HuffmanTree*)malloc(sizeof(HuffmanTree) * m);
	for (int i=1; i<m; i++) {
		hTree[i].weight = hTree[i].parent = hTree[i].lchild = hTree[i].rchild = 0;
	}
	
	printf("请依次输入权值：\n");
	for (int i=1; i<=n; i++) {
		scanf("%d", &hTree[i].weight);
	}
	
	CreateHuffmanTree(hTree, n, m);
	ShowHuffmanCoding(hTree, n, m);
	
	free(hTree);
}
