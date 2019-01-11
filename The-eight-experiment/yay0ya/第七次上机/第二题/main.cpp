#include"Graph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	ALGraph G;
	CreateGraph(G);
	TopologicalSort(G);
	return 0;
}
