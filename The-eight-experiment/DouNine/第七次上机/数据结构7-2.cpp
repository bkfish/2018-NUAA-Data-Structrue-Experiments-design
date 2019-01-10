/*
编写拓扑排序算法
6 8

0 1
0 2
0 3
2 1
2 4
3 4
5 3
5 4
*/
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

typedef struct VNode {
	int data;
	VNode* next;
}VNode, *VList;

// 有向图的领接表表示法 
typedef struct {
	int vexnum, arcnum;
	VList* vexList;
}ALGraph;

void CreateALGraph(ALGraph &G) {
	cout<<"请输入顶点数和边数:\n";
	cin>>G.vexnum>>G.arcnum;
	
	// 初始化领接表 
	G.vexList = (VList*)malloc(sizeof(VList) * G.vexnum);
	for (int i=0; i<G.vexnum; i++) {
		VNode* temp = (VNode*)malloc(sizeof(VNode));
		temp->data = i;
		temp->next = NULL;
		G.vexList[i] = temp;
	}
	
	cout<<"请每条边的始点、终点(0~n-1):\n";
	for (int i=0; i<G.arcnum; i++) {
		int x = 0, y = 0;
		VNode* temp = (VNode*)malloc(sizeof(VNode));
		cin>>x>>y;
		temp->data = y;
		temp->next = NULL;
		temp->next = G.vexList[x]->next;
		G.vexList[x]->next = temp;
	}
}

void DestroyALGraph(ALGraph &G) {
	for (int i=0; i<G.vexnum; i++) {
		VNode *p = G.vexList[i], *temp;
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
	}
	cout<<"\nDestroy Success!\n";
}

void TraverseALGraph(ALGraph G) {
	cout<<"领接表的遍历如下：\n";
	for (int i=0; i<G.vexnum; i++) {
		VNode * p = G.vexList[i];
		while (p) {
			cout<<p->data<<" ";
			p = p->next;
		}
		cout<<endl;
	}
}

int main() {
	ALGraph G;
	CreateALGraph(G);
	TraverseALGraph(G);
	
	int inCount[G.vexnum];
	for (int i=0; i<G.vexnum; i++) {
		inCount[i] = 0;
	}
	for (int i=0; i<G.vexnum; i++) {
		VNode * p = G.vexList[i]->next;
		while (p) {
			inCount[p->data]++;
			p = p->next;
		}
	} 
	
//	for (int i=0; i<G.vexnum; i++) {
//		cout<<inCount[i]<<"--";
//	}
//	cout<<endl;
	
	vector<int> res;
	while (1) {
		bool noZero = true;
		for (int i=0; i<G.vexnum; i++) {
			if (inCount[i] == 0) {
				//cout<<"===="<<i<<endl;
				inCount[i]--;
				noZero = false;
				res.push_back(i);
				VNode * p = G.vexList[i]->next;
				while (p) {
					inCount[p->data]--;
					p = p->next;
				}
			}
		}
		if (noZero) break;
	}
	if (res.size() < G.vexnum) {
		cout<<"有环！\n";
		getchar();
		return 0;
	}
	
	cout<<"拓扑排序结果如下：\n";
	for (int i=0; i<G.vexnum; i++) {
		cout<<res[i]<<"--";
	}
	
	DestroyALGraph(G);
	return 0;
} 
