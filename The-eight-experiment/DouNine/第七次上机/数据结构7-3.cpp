/*
4 4
1 2 1
2 3 4
2 4 2
3 4 3
*/
#include<cstdio>
#include<algorithm>

using namespace std;

typedef struct {
	int from, to;
	int weight;
}Arc;

Arc arcs[100005];
int points[1005];		// 并查集 

bool isConnect(int i, int j) {
	int n = i;
	while (points[n] != -1 && points[n] != i) {
		if (points[n] == j) return true;
		n = points[n];
	}
	return false;
}

void connect(int i, int j) {
	int x = i;
	while (points[x] != -1 && points[x] != i) x = points[x];
	int y = j;
	while (points[y] != -1 && points[y] != j) y = points[y];

	points[x] = j;
	points[y] = i;
} 

bool cmp(Arc a, Arc b) {
	return a.weight < b.weight;
}

int main() {
	long long n=0, m=0;
	scanf("%d%d", &n, &m);
	
	for (int i=0; i<n; i++) points[i] = -1;
	
	for (int i=0; i<m; i++) {
		scanf("%d%d%d", &arcs[i].from, &arcs[i].to, &arcs[i].weight);	// 用cin比scanf慢 
		arcs[i].from--;
		arcs[i].to--;
	}
	
	// 对m条边排序
	sort(arcs, arcs+m, cmp);	// 不用快排，就会超时 
//	for (int i=1; i<m; i++) {
//		int j=i;
//		Arc temp;
//		while (j>0 && arcs[j].weight<arcs[j-1].weight) {
//			temp = arcs[j-1];
//			arcs[j-1] = arcs[j];
//			arcs[j] = temp;
//			j--;
//		}
//	}
	
	// check 
//	for (int i=0; i<m; i++) {
//		cout<<arcs[i].from<<" "<<arcs[i].to<<" "<<arcs[i].weight<<endl;
//	}
	
	int sum = 0;
	for (int i=0; i<m; i++) {
		if (!isConnect(arcs[i].from, arcs[i].to)) {
			connect(arcs[i].from, arcs[i].to);
			sum += arcs[i].weight;
		}
	}
	
	printf("%d", sum);
	return 0;
}
