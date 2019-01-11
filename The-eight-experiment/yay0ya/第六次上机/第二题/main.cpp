#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef int ELEMTYPE;

//哈弗曼树节点结构体
typedef struct HuffmanTree
{
	ELEMTYPE weight;
	ELEMTYPE id;//区分权值相同的节点
	struct HuffmanTree* lchild;
	struct HuffmanTree* rchild;
}HuffmanNode;

//构建哈弗曼树
HuffmanNode* createHuffmanTree(int* T,int n)
{
	int i,j;
	HuffmanNode **temp,*huffmanTree;
	temp =(HuffmanNode**)malloc(n*sizeof(HuffmanNode));

	//将数组T中的权值赋值给节点中的weight
	for(i=0;i<n;i++)
	{
		temp[i]=(HuffmanNode*)malloc(sizeof(HuffmanNode));
		temp[i]->weight =T[i];
		temp[i]->id =i;
		temp[i]->lchild =temp[i]->rchild =NULL;
	}

	//构建哈弗曼树需要N-1合并
	for(i=0;i<n-1;i++)
	{
		int small1=-1,small2;//将small1和small2分别作为最小值和次小值的下标

		//先将最小的两个下标赋值给small1和small2，对应权值未必最小
		for(j=0;j<n;j++)
		{
			if(temp[j]!=NULL&&small1==-1)
			{
				small1=j;
				continue;
			}
			else if(temp[j]!=NULL)
			{
				small2=j;
				break;
			}
		}
		for(j=small2;j<n;j++)//比较权值，挪动small1和small2使之分别成为最小权值和次小权值的下标
		{
			if(temp[j]!=NULL)
			{
				if(temp[j]->weight<temp[small1]->weight )
				{
					small2=small1;
					small1=j;
				}
				else if(temp[j]->weight<temp[small2]->weight)
				{
					small2=j;
				}
			}
		}
		huffmanTree=(HuffmanNode*)malloc(sizeof(HuffmanNode));
		huffmanTree->weight =temp[small1]->weight +temp[small2]->weight;
		huffmanTree->lchild =temp[small1];
		huffmanTree->rchild =temp[small2];

		temp[small1]=huffmanTree;
		temp[small2]=NULL;
	}
	free(temp);
	return huffmanTree;
}



//递归哈夫曼编码
void Huffman_code(HuffmanNode* huffmanTree,int depth)
{
	static int code[10];
	if(huffmanTree)
	{
		if(huffmanTree->lchild ==NULL&&huffmanTree->rchild ==NULL)
		{
			printf("权值为%d的叶子节点的哈夫曼编码为",huffmanTree->weight );
			int i;
			for(i=0;i<depth;i++)
			{
				printf("%d",code[i]);
			}
			printf("\n");
		}
		else
		{
			code[depth]=0;
			Huffman_code(huffmanTree->lchild,depth+1);
			code[depth]=1;
			Huffman_code(huffmanTree->rchild,depth+1);
		}
			
	}
}
int main()
{
	int i,n,*arr,WPL,len=0;
	printf("请输入叶节点的个数：\n");
	while(1)
	{
		scanf("%d",&n);
		if(n>1)break;
		else printf("输入错误，请重新输入：");
	}
	arr=(int*)malloc(n*sizeof(ELEMTYPE));
	printf("请输入%d个叶节点的权值：\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	HuffmanTree* huffmanTree=NULL;
	huffmanTree=createHuffmanTree(arr, n);


	printf("此哈弗曼树的叶节点的编码为：\n");
	Huffman_code(huffmanTree,0);
	return 0;
}
