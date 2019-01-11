#include"Graph.h"
int main(){
	int n,m;
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open()) 
		{
			cout<<"无法打开该文件\n";
			exit(0);
		}
	MGraph G;
	file>>n;
	file>>m;//n为路口数量，m为道路数量
	G.vexnum=n;
	G.arcnum=m;
	int road[n]={};
	int t,a,b,c;
	Initarray(G,n);//初始化矩阵 
	for(int i=1;i<=m;i++){
		file>>t;
		file>>a;
		file>>b;
		file>>c;
		G.arcs[a][b].type=t;
		G.arcs[a][b].adj=c;
	}//所有与道路有关的矩阵接收到赋值
	road[0]=1;
	findroad(G,road,0);
	miniout(G);

		
 }
