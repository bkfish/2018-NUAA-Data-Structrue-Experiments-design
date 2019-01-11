/*
[问题描述]
　　JSON (JavaScript Object Notation) 是一种轻量级的数据交换格式，
	可以用来描述半结构化的数据。JSON 格式中的基本单元是值 (value)，
	出于简化的目的本题只涉及 2 种类型的值：
　　* 字符串 (string)：字符串是由双引号 " 括起来的一组字符（可以为空）。
		如果字符串的内容中出现双引号 "，在双引号前面加反斜杠，也就是用 \" 表示；
		如果出现反斜杠 \，则用两个反斜杠 \\ 表示。
		反斜杠后面不能出现 " 和 \ 以外的字符。例如：""、"hello"、"\"\\"。
　　* 对象 (object)：对象是一组键值对的无序集合（可以为空）。
		键值对表示对象的属性，键是属性名，值是属性的内容。
		对象以左花括号 { 开始，右花括号 } 结束，键值对之间以逗号 , 分隔。
		一个键值对的键和值之间以冒号 : 分隔。键必须是字符串，
		同一个对象所有键值对的键必须两两都不相同；值可以是字符串，也可以是另一个对象。
		例如：
		{}、{"foo": "bar"}、{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}。
　　除了字符串内部的位置，其他位置都可以插入一个或多个空格使得 JSON 的呈现更加美观，
	也可以在一些地方换行，不会影响所表示的数据内容。
	例如，上面举例的最后一个 JSON 数据也可以写成如下形式。
　　{
　　"Mon": "weekday",
　　"Tue": "weekday",
　　"Sun": "weekend"
　　}
　　给出一个 JSON 格式描述的数据，以及若干查询，编程返回这些查询的结果。
输入格式
　　第一行是两个正整数 n 和 m，分别表示 JSON 数据的行数和查询的个数。
　　接下来 n 行，描述一个 JSON 数据，保证输入是一个合法的 JSON 对象。
　　接下来 m 行，每行描述一个查询。给出要查询的属性名，
	要求返回对应属性的内容。需要支持多层查询，各层的属性名之间用小数点 . 连接。
	保证查询的格式都是合法的。
[基本要求]
输出格式
　　对于输入的每一个查询，按顺序输出查询结果，每个结果占一行。
　　如果查询结果是一个字符串，则输出 STRING <string>，其中 <string> 是字符串的值，中间用一个空格分隔。
　　如果查询结果是一个对象，则输出 OBJECT，不需要输出对象的内容。
　　如果查询结果不存在，则输出 NOTEXIST。
样例输入
10 5
{
	"firstName": "John",
	"lastName": "Smith",
	"address": {
		"streetAddress": "2ndStreet",
		"city": "NewYork",
		"state": "NY"
	},
	"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
样例输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
[基本要求] 
（1）要求从文本文件中输入；
（2）本题目其实就是一棵普通的树（即每个结点的孩子数不固定，不能单纯采用n叉树来解决），
	可以考虑使用孩子兄弟表示法等进行表示和存储；
（3）严格按照要求的输入输出格式进行数据的输入、输出（训练CSP考试中的格式化输入输出的正确性）；
（4）选做：使用图形界面（或字符格式化摆成的树形结构，参考Linux下的tree命令），
	以树状形式显示输入的JSON格式数据。
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<windows.h>

using namespace std; 

typedef struct TNode 
{
	char key[100];
	char value[100];
	TNode *child;
	TNode *brother;
}*Tree;

// 全局变量 
FILE *fp;
char fileName[] = "json3.txt";


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

// 先序遍历
void TraverseTree(Tree tree) 
{
	if (tree) 
	{
		printf("%s:%s\n", tree->key, tree->value);
		TraverseTree(tree->brother);
		TraverseTree(tree->child);
	}
}

// 销毁
void DestroyTree(Tree &tree) 
{
	if (tree) 
	{
		DestroyTree(tree->brother);
		DestroyTree(tree->child);
		free(tree);
	}
}

// 字符串处理函数
void HandleStr(char *source, int start, int end, char *dist) 
{
	//printf("before handle: %s  start: %d---%c  end: %d---%c\n", source, start, source[start], end, source[end]);
	int i = start+1;
	int j = 0;
	while (i != end) 
	{
		if (source[i] == '\\') i++;
		dist[j] = source[i];
		i++;
		j++;
	}
	dist[j] = '\0';
	//printf("after handle : %s\n", dist);
}

// 检测是否遇到空字符(超限)，若遇到则重新读取字符串 
void Check(char* &str, int &pos) 
{
	if (pos >= strlen(str)) 
	{
		fscanf(fp, "%s", str);
		pos = 0;
	}
}

// 建树函数，递归 
void CreateTree(Tree &tree, char *str, int &i) 
{
	
	TNode *preNode = tree, *node;
	bool flag = false;	// 判断是否为根节点 
	i++;				// i++避过'{' 
	Check(str, i);
	
	while (str[i] != '}') 
	{
		node = (TNode*)malloc(sizeof(TNode));
		
		//printf("前一半======%s\n", str);
		if (str[i] == '"') 
		{
			int j = i;
			while (str[j] != ':' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->key);
			i = j;
			Check(str, i);
		}
		i++;
		Check(str, i);
		
		//printf("后一半=====%s\n", str);
		if (str[i] == '{') 
		{
			strcpy(node->value, "object");
			CreateTree(node->child, str, i);	// 值是一个对象，则递归操作 
		}
		else if (str[i] == '"') 
		{
			node->child = NULL; 
			int j = i;
			while (str[j] != ',' && str[j] != '}' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->value);
			i = j;
			Check(str, i);
		}
		
		// 若为第一个结点则将结点指针赋给tree指针 
		if (!flag) 
		{
			tree = node;
			flag = true;
		}
		// 不是第一个结点，则将上个结点的兄弟指向当前结点 
		else preNode->brother = node;
		preNode = node;
		
		// 适用于最后一个没有','的情况 
		if (str[i] == '}') break;
		i++;
		Check(str, i);
	}
	node->brother = NULL;
	i++;	// 使指针指向'}'的下一个，适用于对象包含对象的情况 
}
 
// 找value值
char* FindValue(Tree tree, char *str) 
{
	int i = 0;
	char key[1000];
	while (str[i]!='.' && i<strlen(str)) 
{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	
	TNode *node = tree;
	while (node) 
	{
		if (strcmp(node->key, key) == 0) 
		{
			if (str[i] == '.') 
			{
				int j = 0;
				char nextStr[1000];
				i++;
				while (i<strlen(str)) 
				{
					nextStr[j] = str[i];
					i++;
					j++;
				}
				nextStr[j] = '\0';
				return FindValue(node->child, nextStr);
			}
			else return node->value;
		}
		node = node->brother;
	}
	return NULL;
} 

// 显示树 
void ShowTree(Tree tree, int tab) 
{	
	TNode *node = tree;
	while (node) 
	{
		for (int i=0; i<tab; i++) printf("|  ");
		printf("|--%s", node->key);
		if (node->child) 
		{
			printf("\n");
			ShowTree(node->child, tab+1);
		}
		else printf(":%s\n", node->value);
		node = node->brother;
	}
} 


int main() 
{
	fileOpen("r");
	
	int n = 0, m = 0;
	fscanf(fp, "%d%d", &n, &m);
	
	Tree tree = NULL;
	char strLine[10000];
	fscanf(fp, "%s", strLine);
	int start = 0;
	CreateTree(tree, strLine, start);	// 1位置开始忽略开始的'{'
	
	system("cls");	// 清屏 
	//TraverseTree(tree);
	printf("+\n");
	ShowTree(tree, 0);
	printf("\n\n按任意键继续");
	getchar();
	system("cls");
	
	// 读取输入数据 
	for (int i=0; i<m; i++) 
	{
		fscanf(fp, "%s", strLine);
		char *ret = FindValue(tree, strLine);
		char value[1000];
		if (!ret) sprintf(value, "NOTEXIST");
		else if (strcmp(ret, "object") == 0) sprintf(value, "OBJECT");
		else sprintf(value, "STRING %s", ret);
		printf("%s\n", value);
	}
	
	DestroyTree(tree);
	fileClose();
}
