/*
关键路径
6 8

1 2 3
1 3 2
2 4 2
2 5 3
3 4 4
3 6 3
4 6 2
5 6 1
*/
#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;


// 有向图 
typedef struct {
	char *vexs;				// 顶点值的向量 
	int vexNum, arcNum;  	// 图的顶点数和边数
	int **arcs;				// 边的矩阵 
}MGraph;


// 路径
typedef struct {
	int from, to;
	int weight;
}Arc; 

 
// 创建图 
void CreateMGraph(MGraph &G) {
	cout<<"请输入顶点数和边数:\n";
	cin>>G.vexNum>>G.arcNum;
	
	// 动态初始化图，将每一条边的值设为0
	G.arcs = (int**)malloc(sizeof(int*) * (G.vexNum+1));
	for (int i=0; i<=G.vexNum; i++) {
		G.arcs[i] = (int*)malloc(sizeof(int) * (G.vexNum+1));
		for (int j=0; j<=G.vexNum; j++) {
			G.arcs[i][j] = 0;		// 用0表示这两条边不相邻 
		}
	}

	cout<<"请依次输入该有向网中各边(1-n)的始点、终点和权值：\n";
	
	int x, y, weight;
	for (int i=1; i<=G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"不能出现环！\n";
			i--;
			continue;
		} 
		if (x > G.vexNum) {
			cout<<"不存在该点！\n";
			i--;
			continue;
		} 
		if (y > G.vexNum) {
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


// 销毁图
void DestroyGraph(MGraph &G) {
	cout<<"\n销毁图\n";
	for (int i=0; i<=G.vexNum; i++) {
		free(G.arcs[i]);
	}
	free(G.arcs);
	G.vexNum = G.arcNum = 0;
} 


// 遍历图 
void Traverse(MGraph G) {
	cout<<"\n图的矩阵遍历如下：\n";
	for (int i=1; i<=G.vexNum; i++) {
		for (int j=1; j<=G.vexNum; j++) {
			cout<<G.arcs[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
} 


// 拓扑排序 
vector<int> TopoSort(MGraph &G) {
	int *inCount = (int*)malloc(sizeof(int) * (G.vexNum+1));	// 定义一个记录每个点入度值的数组 
	// 初始化入度值数组 
	for (int i=0; i<=G.vexNum; i++) {
		inCount[i] = 0;
	}	
	// 求每个点的入度 
	for (int i=1; i<=G.vexNum; i++) {
		for (int j=1; j<=G.vexNum; j++) {
			// 如果i，j位置不为零，则说明i->j，j点的入度加一 
			if (G.arcs[i][j]) inCount[j]++; 
		}
	}
	
	vector<int> topoRes;		// 拓扑排序后的路径
	bool hasZero = true; 
	while (hasZero) {
		hasZero = false;
		for (int i=1; i<=G.vexNum; i++) {
			// 如果存在入度为0的顶点 
			if (!inCount[i]) {
				hasZero = true;
				inCount[i]--;
				topoRes.push_back(i);
				// 将以该点为始点的点的入度都减一 
				for (int j=1; j<=G.vexNum; j++) {
					if (G.arcs[i][j]) inCount[j]--;
				}
			}
		}
	}
	
	free(inCount);
	
	if (topoRes.size() < G.vexNum) {
		cout<<"有环！\n";
		getchar();
		exit(0);
	}
	
	return topoRes;
}


int main() {
	MGraph G;
	CreateMGraph(G);
	Traverse(G);
	
	
	vector<int> topoRes = TopoSort(G);
	cout<<"拓扑排序结果如下：\n";
	for (int i=0; i<topoRes.size(); i++) {
		cout<<topoRes[i]<<"---";
	}
	cout<<endl<<endl;


	int *ve = (int*)malloc(sizeof(int) * (G.vexNum+1));		// 每个点最早时间 
	int *vl = (int*)malloc(sizeof(int) * (G.vexNum+1));		// 每个点最晚时间 
	
	// 各点的最早开工时间 
	for (int n=0; n<topoRes.size(); n++) {
		int j = topoRes[n];
		// 取所将所有以j为终点的点i中，i点的最早时间加上i->j的时间中，的最大值
		int max = 0;  
		for (int i=1; i<=G.vexNum; i++) {
			if (G.arcs[i][j]) {
				if (ve[i] + G.arcs[i][j] > max) max = ve[i] + G.arcs[i][j];
			}
		}
		ve[j] = max;
	}
	cout<<"每个点的最早开工时间如下：\n";
	for (int i=1; i<=G.vexNum; i++) {
		cout<<i<<"---"<<ve[i]<<"  ";
	} 
	cout<<endl<<endl;
	
	// 各点的最晚开工时间 
	int last = topoRes[G.vexNum-1];	// 最后一个工程点，即终点 
	vl[last] = ve[last];	// 将终点的最晚开工时间设为最早开工时间 
	for (int n=G.vexNum-2; n>=0; n--) {
		int i = topoRes[n];
		// 取所将所有以i为始点的点j中，j点的最晚时间减去i->j的时间中，的最小值 
		int min = INT_MAX;  
		for (int j=1; j<=G.vexNum; j++) { 
			if (G.arcs[i][j] && (vl[j] - G.arcs[i][j] < min)) {
				min = vl[j] - G.arcs[i][j];
			}
		}
		vl[i] = min;
	}
	cout<<"每个点的最晚开工时间如下：\n";
	for (int i=1; i<=G.vexNum; i++) {
		cout<<i<<"---"<<vl[i]<<"  ";
	} 
	cout<<endl<<endl;
	
	
	// 求关键路径 
	vector<Arc> importPath;
	for (int n=0; n<topoRes.size(); n++) {
		int i = topoRes[n];
		for (int j=1; j<=G.vexNum; j++) {
			if (G.arcs[i][j] && (vl[j]-G.arcs[i][j] == ve[i])) {
				Arc arc;
				arc.from = i;
				arc.to = j;
				arc.weight = G.arcs[i][j];
				importPath.push_back(arc);
			}
		}
	}
	cout<<"关键路径如下：\n";
	for (int i=0; i<importPath.size(); i++) {
		cout<<importPath[i].from<<"-->"<<importPath[i].to<<"  "<<importPath[i].weight<<endl;
	}
	
	free(ve);
	free(vl);
	
	DestroyGraph(G);
	return 0; 
}







