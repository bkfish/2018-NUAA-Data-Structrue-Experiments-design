/*
[问题描述]
对一篇不少于2000字符的英文文章（source.txt），统计各字符出现的次数，
实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。
[基本要求]
（1）输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
（2）在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，
	编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符’0’和’1’表示。
（3）实现解码功能。
*/
#include<cstdio>
#include<cstring>
#include<cstdlib> 
#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

// 可能出现的字符种类 
#define CharCount 300

// 位操作的数据格式 
#define dataType unsigned int
#define dataLen 32

// 字符结构体，字符为结构体数组下标 
typedef struct 
{
	int count;		// 该字符出现的次数 
	dataType code;	// 该字符的编码转整型 
	char codeLen; 	// 二进制编码的长度
}Char;

// Huffman树的结点结构体 
typedef struct 
{
	char ch;
	int weight;
	int parent;
	int lchild, rchild;
}HuffmanTree;


// 全局变量 
FILE *fp;
char fileName[100];


// 打开文件 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// 建哈夫曼树表
void CreateHuffmanTree(HuffmanTree * &hTree, int n, int m) 
{
	// 经过n-1次找两个最小值 
	for (int i=1; i<=n-1; i++) 
	{
		int fMin = INT_MAX, sMin = INT_MAX-1;	// 初始化第一小和第二小的权值 
		int fMinP = 0, sMinP = 0;            	// 权值第一小和第二小的位置 
		int j = 1;
		// 遍历所有已经有权值的结点 
		while (j<m && hTree[j].weight) 
		{
			// 如果该结点没有双亲，且权值小于第二小的权值 
			if ((!hTree[j].parent) && (hTree[j].weight < sMin)) 
			{
				// 如果该权值小于第一个小的权值 
				if (hTree[j].weight < fMin) 
				{
					sMin = fMin;
					sMinP = fMinP; 
					fMin = hTree[j].weight;
					fMinP = j;
				}
				// 如果在第一和第二小权值中间 
				else 
				{
					sMin = hTree[j].weight;
					sMinP = j;
				}
			}
			j++;
		}
		// j最后停在没有权值的新结点的那一行，将上述两个结点变为新结点的孩子 
		if (j < m) 
		{

			hTree[fMinP].parent = j;
			hTree[sMinP].parent = j;
			
			hTree[j].lchild = fMinP;
			hTree[j].rchild = sMinP;
			hTree[j].weight = fMin + sMin;
		}
	}
	
//	cout<<"建哈夫曼树成功:\n";
//	for (int i=1; i<m; i++) {
//		cout<<hTree[i].ch<<" "<<hTree[i].weight<<" "<<hTree[i].parent<<" "<<hTree[i].lchild<<" "<<hTree[i].rchild<<endl;
//	}
}

// 设置x这个数第n比特位的值为bo(0,1) 
void SetBit(dataType &x, int n, int bo) 
{
	if (bo) x = x | 1U<<n;
	else x = x & ~(1U<<n);
}

// 获取x第n到第m(低位到高位)比特位的值，返回是数据类型 
dataType GetBit(dataType x, int n, int m) 
{
	return (x & ~(~0U<<(m-n+1))<<n) >>n;
}

// 将01字符串形式的二进制转化成整数 
void getCode(stack<char> hCode, dataType &code, char &codeLen) 
{
	codeLen = hCode.size();
	if (codeLen > dataLen) 
	{
		printf("出现超限编码！！\n");
		return ;
	}
	
	// 字符栈中的栈顶是二进制的高位 
	int i = codeLen-1;
	code = 0;
	while (!hCode.empty()) 
	{
		char bitCh = hCode.top();
		printf("%c", bitCh);
		SetBit(code, i, bitCh-'0');
		hCode.pop();
		i--;
	}
}

// 将整数转化成字符串形式的01二进制
stack<char> setCode(dataType code, char codeLen) 
{
	// 栈顶是高位 
	stack<char> hCode;
	int i = 0;
	while (i < codeLen) 
	{
		hCode.push(GetBit(code, i, i) + '0');
		i++;
	}
	return hCode; 
}

// 哈夫曼编码 
void HuffmanEnCode(HuffmanTree *hTree, int n, int m, Char *chs) 
{
	
	vector< stack<char> > hCodes;	// 存放Huffman编码结果的动态数组 
	stack<char> temp;
	// 遍历1到n号位置，从结点开始找双亲 
	for (int i=1; i<=n; i++) 
	{
		//cout<<i<<endl;
		int son = i;
		int parent = hTree[son].parent;	// 找到双亲
		// 当双亲不为空，即没有到头 
		while (parent) 
		{
			// 如果该结点是双亲的左孩子 
			if (hTree[parent].lchild == son) temp.push('0');
			// 如果是右孩子 
			else temp.push('1');
			// 找到上一代孩子爸爸 
			son = parent;
			parent = hTree[son].parent;
		}
		hCodes.push_back(temp);
		while (!temp.empty()) temp.pop();
	}
	
	printf("\n--------Huffman编码结果---------\n");
	// 遍历hCodes二维数组 
	for (int i=0; i<hCodes.size(); i++) 
	{
		printf("字符：%c---权重：%d---编码：", hTree[i+1].ch, hTree[i+1].weight);	// hCodes中0位置对应hTree中的1位置 
		getCode(hCodes[i], chs[hTree[i+1].ch].code, chs[hTree[i+1].ch].codeLen);
		printf("--->%d(len:%d)\n", chs[hTree[i+1].ch].code, chs[hTree[i+1].ch].codeLen);
	}
	printf("\n"); 
}

// 哈夫曼解码 
char HuffmanDeCode(HuffmanTree *hTree, int n, int m, stack<char> hCode) 
{
	
	char ch, top;
	int pos = m-1;
	while (!hCode.empty()) 
	{
		top = hCode.top();
		//cout<<top<<"---"<<pos<<endl;
		hCode.pop();
		if (top == '0') pos = hTree[pos].lchild;
		else pos = hTree[pos].rchild;
	}
	// 如果孩子不为空(0)
	if (hTree[pos].lchild || hTree[pos].rchild) return 0;
	return hTree[pos].ch;
}


int main() 
{
	
	Char chs[CharCount];	// ASCII表中最多256个字符 
	for (int i=0; i<CharCount; i++) 
	{
		chs[i].count = 0;
	}
	
	// 读取文本文件，并统计字符出现次数 
	strcpy(fileName, "source.txt");
	fileOpen("r");
	char source[100000];		// 文本 
	int count = 0;			// 文本长度 
	int n = 0;				// 有多少个字符 
	while (!feof(fp)) 
	{
		fscanf(fp, "%c", &source[count]);
		printf("%c", source[count]);
		if (chs[source[count]].count == 0) n++;
		chs[source[count]].count++;
		count++;
	}
	fileClose();
	
	// 初始化Huffman树线性表 
	int m = 2*n;	// huffman树 数据结构(线性表) 的长度，即有多少个结点(2n-1个)
	HuffmanTree *hTree = (HuffmanTree*)malloc(sizeof(HuffmanTree) * m);
	for (int i=1; i<m; i++) 
	{
		hTree[i].weight = hTree[i].parent = hTree[i].lchild = hTree[i].rchild = 0;
	}
	// 将Huffman树线性表中1到n位置赋值 
	int j = 1;		
	for (int i=0; i<CharCount; i++) 
	{
		if (chs[i].count) 
		{
			hTree[j].parent = hTree[j].lchild = hTree[j].rchild = 0;
			hTree[j].weight = chs[i].count;
			hTree[j].ch = i; 
			j++;
		}
	}
	
	CreateHuffmanTree(hTree, n, m);		// 建Huffman树
	HuffmanEnCode(hTree, n, m, chs);	// Huffman编码 

	
	// 将字符出现次数和对应的二进制编码保存到文件 
	strcpy(fileName, "Huffman.txt");
	fileOpen("w");
	stack<char> hCode;
	for (int i=0; i<CharCount; i++) 
	{
		if (chs[i].count) 
		{
			//printf("字符：%c---权重：%d---编码：%d(len:%d)\n", i, chs[i].count, chs[i].code, chs[i].codeLen);
			fprintf(fp, "字符：%c---出现次数：%d---二进制编码：", i, chs[i].count);
			stack<char> hCode = setCode(chs[i].code, chs[i].codeLen);
			while (!hCode.empty()) 
			{
				fprintf(fp, "%c", hCode.top());
				hCode.pop();
			}
			fprintf(fp, "\n");
		}
	}
	fileClose();
	
	
	// 对文本进行编码并输出到二进制文件 
	strcpy(fileName, "code.dat");
	fileOpen("wb");
	queue<Char> q;	// 队列
	for (int i=0; i<count; ) 
	{
		int lenSum = 0;
		// 取多个字符，它们二进制编码长度加起来小于dataType数据二进制编码长度 
		while (1) 
		{
			lenSum += chs[source[i]].codeLen;
			if (lenSum > dataLen) break;
			q.push(chs[source[i]]);
			i++;
		}
		
		// 将这多个字符编码后的二进制数据，从dataType数据的高位开始存放 
		dataType data = 0;
		int pos = dataLen-1; 	// pos指向要存入文件的dataType数据高位 
		while (!q.empty()) 
		{
			Char temp = q.front();
			q.pop();
			int j = temp.codeLen-1, bo = 0;		// j该字符编码后的二进制的高位
			// j到达结尾，即该字符二进制编码全部存入dataType数据中 
			while (j>=0) 
			{
				bo = GetBit(temp.code, j, j);	// 获取该位置的二进制数
				SetBit(data, pos, bo);			// 设置dataType中pos位置的二进制数
				j--;
				pos--;
			}
		}
		fwrite(&data, sizeof(dataType), 1, fp);
	}
	fileClose();


	// 读取二进制文件并进行解码 
	strcpy(fileName, "code.dat");
	fileOpen("rb");
	char recode[10000];
	int i = 0;
	dataType data;
	// 每次从文件中读取一个dataType数据类型的数据 
	while (fread(&data, sizeof(dataType), 1, fp)) 
	{
		// 从该数据的高位开始 
		int pos = dataLen-1, j = 0;
		while (pos-j >= 0) 
		{
			dataType temp = GetBit(data, pos-j, pos);// GetBit是从低位到高位获取二进制数据 
			// 通过setCode将二进制转化成01字符串，再通过HuffmanDeCode查找该二进制对应的字符 
			char res = HuffmanDeCode(hTree, n, m, setCode(temp, j+1));
			// 如果返回字符不为空则说明找到了，输出 
			if (res) 
			{
				recode[i] = res;
				i++;
				printf("%c", res); 
				pos -= (j+1);	// pos-(j+1)才指向下一个二进制对应的字符数据 
				j = 0;
				continue;
			}
			j++;
		}
	}
	fileClose();
	
	
	// 将解码后的写入到文本 
	strcpy(fileName, "recode.txt");
	fileOpen("w");
	for (int i=0; i<count; i++) 
	{
		fprintf(fp, "%c", recode[i]);
	}
	fileClose();
	
	
	free(hTree);
}
