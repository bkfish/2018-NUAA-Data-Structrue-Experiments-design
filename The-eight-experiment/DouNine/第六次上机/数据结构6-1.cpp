/*
编程实现书P156  ADT Graph 基本操作13个，用邻接矩阵存储结构实现；
1.有向图
2.有向网
3.无向图
4.无向网
请确定图的类型：
3
请输入图的顶点数和边数：5 7
请依次输入各顶点的值(字符型)：a b c d e
请依次输入该无向图中各边的两个相邻点：
0 1
0 3
0 4
1 2
1 3
2 4
3 4

请输入图的顶点数和边数：8 9
0 1
0 2
1 3
1 4
3 7
4 7
2 5
2 6
5 6

不连通图 
请输入图的顶点数和边数：8 8
0 1
1 3
1 4
3 7
4 7
2 5
2 6
5 6
*/
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;


// 图的类型{有向图，有向网(带权图)，无向图， 无向网}
typedef enum {DG, DN, UDG, UDN} GraphKind;	


// 边(不使用) 
typedef struct ArcCell {
	int adj;	// 对于无权图，用1或0表示相邻与否；对于带权图，则为权值。 
	int *info;	// 该边对应的信息 
}ArcCell, AdjMatrix[20][20];


// 图 
typedef struct {
	char *vexs;			// 顶点值的向量 
	int vexNum, arcNum;  		// 图的顶点数和边数
	int **arcs;	// 边的矩阵 
	GraphKind kind;				// 图的类型 
}MGraph;


// 构建有向图 
void CreateDG(MGraph &G) {
	cout<<"请依次输入该有向图中各边的始点、终点：\n";
	
	int x, y;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y;
		if (x == y) {
			cout<<"不能出现环！\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = 1;
	}
}


// 构建有向网
void CreateDN(MGraph &G) {
	cout<<"请依次输入该有向网中各边的始点、终点和权值：\n";
	
	int x, y, weight;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"不能出现环！\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		}
		if (weight == 0) {
			cout<<"权重不能为0！\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = weight;
	}
}
 

// 构建无向图 
void CreateUDG(MGraph &G) {
	cout<<"请依次输入该无向图中各边的两个相邻点：\n";
	
	int x, y;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y;
		if (x == y) {
			cout<<"不能出现环！\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = 1;
		G.arcs[y][x] = 1;
	}
}


// 构建无向网
void CreateUDN(MGraph &G) {
	cout<<"请依次输入该无向网中各边的两个相邻点和权值：\n";
	
	int x, y, weight;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"不能出现环！\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		}
		if (weight == 0) {
			cout<<"权重不能为0！\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = weight;
		G.arcs[y][x] = weight;
	}
}


// 构建图G
void CreateGraph(MGraph &G) {
	int choose;
	cout<<"1.有向图\n2.有向网\n3.无向图\n4.无向网\n请确定图的类型：\n";
	cin>>choose;
	
	cout<<"请输入图的顶点数和边数：";
	cin>>G.vexNum>>G.arcNum;
	
	// 动态初始化图，将每一条边的值设为0
	G.arcs = (int**)malloc(sizeof(int*) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) {
		G.arcs[i] = (int*)malloc(sizeof(int) * G.vexNum);
		for (int j=0; j<G.vexNum; j++) {
			G.arcs[i][j] = 0;		// 用0表示这两条边不相邻 
		}
	}
	
	// 初始化顶点值 
	G.vexs = (char*)malloc(sizeof(char) * G.vexNum);
	cout<<"请依次输入各顶点的值(字符型)："; 
	for (int i=0; i<G.vexNum; i++) {
		cin>>G.vexs[i];
	}
	
	switch(choose) {
		case 1: {
			G.kind = DG;
			CreateDG(G);
			break;
		}
		case 2: {
			G.kind = DN;
			CreateDN(G);
			break;
		}
		case 3: {
			G.kind = UDG;
			CreateUDG(G);
			break;
		}
		case 4: {
			G.kind = UDN;
			CreateUDN(G);
			break;
		}
	}
}


// 销毁图
void DestroyGraph(MGraph &G) {
	cout<<"\n销毁图\n";
	free(G.vexs);
	for (int i=0; i<G.vexNum; i++) {
		free(G.arcs[i]);
	}
	free(G.arcs);
	G.vexNum = G.arcNum = 0;
} 


// 返回顶点位置
int LocateVex(MGraph &G, char value) {
	for (int i=0; i<G.vexNum; i++) {
		if (G.vexs[i] == value) {
			return i;
		}
	}
	return -1; 
}


// 返回顶点的值
char GetVex(MGraph &G, int v) {
	return G.vexs[v];
} 
 

// 设置顶点的值
void PutVex(MGraph &G, int v, char value) {
	G.vexs[v] = value;
}
 

// 返回v的第一个邻接顶点
int FisrtAdjVex(MGraph G, int v) {
	for (int j=0; j<G.vexNum; j++) {
		if (!G.arcs[v][j]) return j;
	}
	return -1;
}


// 返回v相对领接顶点w外的下一个顶点
int NextAdjVex(MGraph G, int v, int w) {
	// 从第v行第w列位置开始向右找下一个顶点 
	for (int j=w; j<G.vexNum; j++) {
		if (!G.arcs[v][j]) return j;
	}
	return -1;
}


// 新增顶点
void InsertVex(MGraph &G, char value) {
	
	G.vexNum++;
	
	// 重新申请点向量空间，并加入新顶点值 
	G.vexs = (char*)realloc(G.vexs, sizeof(char) * G.vexNum);
	G.vexs[G.vexNum-1] = value;
	
	// 重新申请图空间，将新边的值设为0 
	G.arcs = (int**)realloc(G.arcs, sizeof(int*) * G.vexNum);
	//cout<<"ok\n";
	for (int i=0; i<G.vexNum-1; i++) {
		//cout<<i<<endl;
		G.arcs[i] = (int*)realloc(G.arcs[i], sizeof(int) * G.vexNum);
		//cout<<"ok   "<<G.vexNum-1<<"\n";
		G.arcs[i][G.vexNum-1] = 0;
		//cout<<"ok\n";
	}
	//cout<<"ok\n";
	G.arcs[G.vexNum-1] = (int*)malloc(sizeof(int) * G.vexNum);
	for (int j=0; j<G.vexNum; j++) {
		//cout<<"  "<<j<<endl;
		G.arcs[G.vexNum-1][j] = 0;
	}
	
	cout<<"\n新增顶点成功!\n";
}
 
 
// 删除顶点
void DeleteVex(MGraph &G, char value) {
	
	int v = LocateVex(G, value);
	if (v == -1) {
		cout<<"不存在";
		return;
	}
	// 在顶点数组中删去该值，并在边图中删去该行 
	for (int i=v+1; i<G.vexNum; i++) {
		G.vexs[i-1] = G.vexs[i];
		G.arcs[i-1] = G.arcs[i];
	}
	
	// 在边图中删去该列 
	for (int i=0; i<G.vexNum-1; i++) {
		for (int j=v+1; j<G.vexNum; j++) {
			G.arcs[i][j-1] = G.arcs[i][j];
		}
	}
	
	G.vexNum--;
	
	// 重新申请顶点向量空间，并加入新顶点值 
	G.vexs = (char*)realloc(G.vexs, sizeof(char) * G.vexNum);
	
	// 重新申请图空间，将新边的值设为0 
	G.arcs = (int**)realloc(G.arcs, sizeof(int*) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) {
		G.arcs[i] = (int*)realloc(G.arcs[i], sizeof(int) * G.vexNum);
	}
	
	cout<<"\n删除顶点成功!\n";
}


// 新增边 
void InsertArc(MGraph &G, char valueV, char valueW) {
	int v = LocateVex(G, valueV), w = LocateVex(G, valueW);
	if (G.kind == DG) {
		G.arcs[v][w] = 1;
	} 
	else if (G.kind == DN) {
		cout<<"请输入新增边的权重：";
		int weight = 0;
		cin>>weight;
		G.arcs[v][w] = weight;
	}
	else if (G.kind == UDG) {
		G.arcs[v][w] = 1;
		G.arcs[w][v] = 1;
	}
	else if (G.kind == UDN) {
		cout<<"请输入新增边的权重：";
		int weight = 0;
		cin>>weight;
		G.arcs[v][w] = weight;
		G.arcs[w][v] = weight;
	}
	cout<<"\n新增边成功!\n";
}


// 删除边
void DeleteArc(MGraph &G, char valueV, char valueW) {
	int v = LocateVex(G, valueV), w = LocateVex(G, valueW);
	if (G.kind == DG || G.kind == DN) {
		G.arcs[v][w] = 0;
	}
	else if (G.kind == UDG || G.kind == UDN) {
		G.arcs[v][w] = 0;
		G.arcs[w][v] = 0;
	}
	cout<<"\n删除边成功!\n";
}


// 深度优先遍历
void DFSTraverse(MGraph G) {
	bool *vexsCheck = (bool*)malloc(sizeof(bool) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) vexsCheck[i] = false;
	
	cout<<"\n深度优先遍历：";
	stack<int> s;
	for (int i=0; i<G.vexNum; i++) {
		if (!vexsCheck[i]) {
			cout<<"  "<<GetVex(G, i);
			s.push(i);
			vexsCheck[i] = true;
			int top;
			while (!s.empty()) {
				top = s.top();
				// 如果该点未走过则输出 
				if (!vexsCheck[top]) cout<<"--"<<GetVex(G, top);	
				vexsCheck[top] = true;
				int j;		
				// 遍历该结点所有邻接节点 
				for (j=0; j<G.vexNum; j++) {
					if (j != top && G.arcs[top][j] && !vexsCheck[j]) {
						s.push(j);
						break;
					}
				}
				// 如果该点所有邻接点都走过，则弹出该点 
				if (j == G.vexNum) s.pop();
			}
		}
	}
	free(vexsCheck);
}


//// 点位置和已走过到的列位置(列位置从0到最大) 
//typedef struct {
//	int v;
//	int col;
//}vexNode;

//// 深度优先遍历所有路径 
//void DFSTraverse(MGraph G) {
//	int *vexsCheck = (int*)malloc(sizeof(int) * (G.vexNum+1));
//	for (int i=0; i<G.vexNum+1; i++) vexsCheck[i] = 0;
//	
//	vexNode start;
//	stack<vexNode> s;
//	for (int i=0; i<G.vexNum; i++) {
//		cout<<"ok\n"; 
//		if (!vexsCheck[i]) {
//			start.col = 0;
//			start.v = i;
//			s.push(start);
//			vexsCheck[start.v] = 1;
//			vexsCheck[G.vexNum]++;
//			vexNode top, temp;
//			while (!s.empty()) {
//				top = s.top();
//				vexsCheck[top.v] = 0;
//				// 若所有元素已经走过 
//				if (vexsCheck[G.vexNum] == G.vexNum) {
//					// 输出栈 
//					stack<vexNode> tempS(s);
//					cout<<"stack: ";
//					while (!tempS.empty()) {
//						temp = tempS.top();
//						tempS.pop();
//						cout<<GetVex(G, temp.v)<<"<--";
//					}
//					cout<<endl;
//					
//					s.pop();
//					vexsCheck[G.vexNum]--; 
//					continue;
//				}
//				
//				s.pop();
//				vexsCheck[G.vexNum]--;
//				for (top.col+=1; top.col<G.vexNum; top.col++) {
//					if (top.col != top.v && G.arcs[top.v][top.col] && !vexsCheck[top.col]) {
//						// cout<<G.arcs[top.v][top.col]<<" "<<top.col<<endl;
//						temp.v = top.col;
//						temp.col = 0;
//						s.push(top);
//						vexsCheck[top.v] = 1;
//						s.push(temp);
//						vexsCheck[temp.v] = 1;
//						vexsCheck[G.vexNum] += 2; 
//						
//						break;
//					}
//				}
//			}
//		}
//	}
//	free(vexsCheck);
//}


// 广度优先遍历
void BFSTraverse(MGraph G) {
	bool *vexsCheck = (bool*)malloc(sizeof(bool) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) vexsCheck[i] = false;
	
	cout<<"\n广度优先遍历：";
	queue<int> q;
	// for循环找所有未遍历的点，是为了有多个连通分支的情况 
	for (int i=0; i<G.vexNum; i++) {
		if (!vexsCheck[i]) {
			q.push(i);
			vexsCheck[i] = true;
			int front;
			while (!q.empty()) {
				front = q.front();
				cout<<GetVex(G, front)<<"--";
				q.pop();
				for (int j=0; j<G.vexNum; j++) {
					if (front != j && !vexsCheck[j]) {
						q.push(j);
						vexsCheck[j] = true;
					}
				}
			}
		}
	}
}


// 普通遍历 
void Traverse(MGraph G) {
	cout<<"\n顶点向量的遍历如下：\n";
	for (int i=0; i<G.vexNum; i++) {
		cout<<G.vexs[i]<<" ";
	}
	cout<<"\n图的矩阵遍历如下：\n";
	for (int i=0; i<G.vexNum; i++) {
		for (int j=0; j<G.vexNum; j++) {
			cout<<G.arcs[i][j]<<" ";
		}
		cout<<endl;
	}
} 


int main() {
	MGraph G;
	CreateGraph(G);
	Traverse(G);
	
	cout<<"请输入要新增的顶点的值：";
	char ch;
	cin>>ch;
	InsertVex(G, ch);
	Traverse(G);
	cout<<"请输入要删除的顶点：";
	cin>>ch;
	DeleteVex(G, ch);
	Traverse(G);
	
	cout<<"请输入要插入的边的两个顶点值：";
	char chV, chW;
	cin>>chV>>chW;
	InsertArc(G, chV, chW);
	cout<<"请输入要删除的边的两个顶点值：";
	cin>>chV>>chW;
	DeleteArc(G, chV, chW);
	Traverse(G);
	
	DFSTraverse(G);
	BFSTraverse(G);
	DestroyGraph(G); 
}





