//*********************
//*朋友圈*/
//******************
#include<iostream>
using namespace std;
#include<fstream>
typedef struct group{
	int id;
	int *data;
	int length;
}group,*G;
bool ifind(int M[],int n,int N){
	for(int i=0;i<N;i++){
		if(M[i]==n){
			return 1;
		}
	}
	return 0;
}
int calculatefriend(int N,G g,int id[],int M){//N是学生数，G是学生形成的社团，id是需要哪个学生相关的社团的进行一些搜索查找，m是社团数 
	int i,j,k,l;
	int record=0;
	int member[N]={};//用来存储学生 
	i=0;
	while(id[i]!=0){
		i++;
	}
	int count=i;
	for(i=0;i<count;i++){//对学生后面的社团数进行计数，count代表社团数 
		for(j=0;j<M;j++){//M是社团数 
			if(g[j].id==id[i]){//查找社团，找到这个社团 
				for(k=0;k<g[j].length;k++){//对社团中的人进行记录和比较 
					if(g[j].data[k]&&!ifind(member,g[j].data[k],N)){//如果id是i的这个已经拥有这个朋友，就不再将其放入朋友去 
						for(l=0;member[l]!=0;l++)
						;
						member[l]=g[j].data[k];
					}
				} 
			}
		}
	}
	for(i=0;i<N;i++){
		if(member[i]!=0)
			record++;
	}
	return record;
}
int main(){
	int N,M;
	fstream file;
	file.open("data.txt",ios::in);
	file>>N;
	file>>M;
	int i,j,k;
	G g;
	g=new group[M];
	for(int i=0;i<M;i++){
		g[i].id=i+1;
		file>>g[i].length;
		g[i].data=new int[g[i].length];
		for(int j=0;j<g[i].length;j++){
			file>>g[i].data[j];
		} 
	}
/*	for(int i=0;i<M;i++){
		cout<<g[i].length<<" ";
		for(int j=0;j<g[i].length;j++){
			cout<<g[i].data[j]<<" ";
		}
		cout<<endl;
	}
	输入检测函数*/
	int relation[N+1][M]={};//建立关系的数组
	for( i=0;i<M;i++){
		for( j=0;j<g[i].length;j++){
			for( k=0;relation[g[i].data[j]][k]!=0;k++)
					;
			relation[g[i].data[j]][k]=g[i].id;		
		
		}
}
	int friendgroup[N+1]={};//设计一个数组存储
	for(i=1;i<N+1;i++){
		friendgroup[i]=calculatefriend(N,g,relation[i],M);
	}
	int max;
	max=0;
	for(i=0;i<N+1;i++){
		if(friendgroup[i]>max){
			max=friendgroup[i];
		}
	}
	cout<<max; 
	
} 

