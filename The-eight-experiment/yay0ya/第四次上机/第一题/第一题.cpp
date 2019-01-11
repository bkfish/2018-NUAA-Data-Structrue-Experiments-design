#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
typedef int ElemType;
typedef int Status;
typedef struct{
	int i,j;
	ElemType e;
}Triple; 
typedef struct{
	Triple data[MAXSIZE+1];
	int mu,tu,nu;//矩阵的行数、列数，非零元个数 
	}TSMatrix;
Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T){
	//采用三元组顺序表存储表示，求稀疏矩阵M的转置矩阵T
	int col,t,p,q,num[M.nu+1]={},cpot[M.nu+1]={};
	T.mu=M.nu; T.nu=M.mu; T.tu=M.tu;
	if(T.tu){
		for(col=1;col<=M.nu;++col) num[col]=0;//初始化
		for(t=1;t<=M.tu;++t) ++num[M.data[t].j];//求M种每一列非零元素的个数
		cpot[1]=1;
		//求第col列中第一个非零元在b.data中的序号
		for(col=2;col<=M.nu;++col) cpot[col]=cpot[col-1]+num[col-1];
		for(p=1;p<=M.tu;++p){
			col=M.data[p].j; q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		} 
	} 
	return 1;
}
int main(){
	TSMatrix M,T;
	int i,j,k;
	printf("请输入M数组的行数，列数，非零个数\n");
	scanf("%d %d %d",&M.mu,&M.nu,&M.tu);
	for(i=1;i<=M.tu;i++){
		printf("请输入数组中第%d数据的行、列、其值\n",i); 
		scanf("%d %d %d",&M.data[i].i,&M.data[i].j,&M.data[i].e);
		while(M.data[i].i>M.mu||M.data[i].i<1||M.data[i].i<M.data[i-1].i&&i>1){
			printf("该数据行值不符合规定，请重新输入\n"); 
			scanf("%d",&M.data[i].i);
		}
		while(M.data[i].j>M.nu||M.data[i].j<1||M.data[i].i==M.data[i-1].i&&M.data[i].j<=M.data[i-1].j){
			printf("该数据的列值不符合规定，请重新输入\n");
			scanf("%d",&M.data[i].j);
		}
	} 
	if(!FastTransposeSMatrix(M,T)) exit(0);
	for(i=1;i<=M.tu;i++){
		printf("%d %d %d\n",T.data[i].i,T.data[i].j,T.data[i].e);
	}
	return 0; 
}
