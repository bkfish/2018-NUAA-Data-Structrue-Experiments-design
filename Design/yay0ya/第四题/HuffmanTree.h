#include<iostream>
using namespace std;
#include<stdlib.h>
#include<string.h>
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;//动态分配数组存储赫夫曼编码表
typedef int Status;
Status Max(int a,int b){
	if(a>b) return a;
	else return b;
}
void Select(HuffmanTree HT,int n,int &s1,int &s2){
	int min1=-1,min2=-1;
	int flag1=0,flag2=0;
	int comp,a,b;
	int m=2*n-1;
	for(int i=0;i<m;i++){
		if(HT[i].parent==0&&flag1==0){
			min1=i;
			flag1=1;
			continue;
		}
		if(HT[i].parent==0&&flag2==0)
		{
			min2=i;
			flag2=1;
		}
	}
	for(int i=0;i<n;i++){
		comp=Max(HT[min1].weight,HT[min2].weight);
			a=HT[min1].weight;
			b=HT[min2].weight;
			if(comp==a&&HT[i].parent==0&&min1!=i&&min2!=i){
				if(HT[i].weight<comp){
					min1=i;
				}
			}
			if(comp==b&&HT[i].parent==0&&min1!=i&&min2!=i){
				if(HT[i].weight<comp){
					min2=i;
				}
			}
	}
	s1=min1;
	s2=min2;
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
	//w存放n个字符的权值（均>0),构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	HTNode *p;
	int i,m;
	int s1=-1,s2=-1;
	char* cd;
	if(n<=1) return;
	m=2*n-1;
	HT=new HTNode[m+1];
	for(p=HT,i=1;i<=n;++i,++p,++w) {
		p->weight=*w;
		p->rchild=0;
		p->lchild=0;
		p->parent=0;
	}
	for(;i<=m;++i,++p){
		p->weight=0;
		p->parent=0;
		p->rchild=0;
		p->lchild=0;
	}
	for(i=n;i<m;++i){
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	HC=new char*[n+1];
	cd=new char[n];
	cd[n-1]='\0';
	int temp=0,c;
	unsigned int f; 
	for(i=1;i<=n;++i){
		temp=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild==c){
				temp--;
				cd[temp]='0';
			}
			else {
				temp--;
				cd[temp]='1';
			}
		HC[i]=new char[n-temp];
		strcpy(HC[i],&cd[temp]);
	}
	free(cd);
} 

