#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<windows.h>

using namespace std; 

typedef struct TNode {
	char key[100];
	char value[100];
	TNode *child;
	TNode *brother;
}*Tree;

// 全局变量 
FILE *fp;
char fileName[] = "json2.txt";


// 打开文件 
void fileOpen(char *method) {
	if((fp=fopen(fileName,method)) == NULL) {
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() {
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// 先序遍历
void TraverseTree(Tree tree) {
	if (tree) {
		printf("%s:%s\n", tree->key, tree->value);
		TraverseTree(tree->brother);
		TraverseTree(tree->child);
	}
}

// 销毁
void DestroyTree(Tree &tree) {
	if (tree) {
		DestroyTree(tree->brother);
		DestroyTree(tree->child);
		free(tree);
	}
}

// 字符串处理函数
void HandleStr(char *source, int start, int end, char *dist) {
	//printf("before handle: %s  start: %d---%c  end: %d---%c\n", source, start, source[start], end, source[end]);
	int i = start+1;
	int j = 0;
	while (i != end) {
		if (source[i] == '\\') i++;
		dist[j] = source[i];
		i++;
		j++;
	}
	dist[j] = '\0';
	//printf("after handle : %s\n", dist);
}

// 建树函数，递归 
void CreateTree(Tree &tree) {
	char str[1000]; 
	fscanf(fp, "%s", str);		// 读取'{'的下一行的字符串 
	int i = 0;
			
	TNode *preNode = tree, *node;
	bool isFirstNode = true;	// 判断是否为根节点 
	
	while (str[i] != '}') {
		node = (TNode*)malloc(sizeof(TNode));
		
		printf("前一半======%s\n", str);
		if (str[i] == '"') {
			int j = i;
			while (str[j] != ':') j++;
			HandleStr(str, i, j-1, node->key);
			i = j;	// i位置为':' 
		}
		i++;// 跳过':'到value部分 
		
		printf("后一半=====%s\n", str);
		if (str[i] == '{') {
			strcpy(node->value, "object");
			CreateTree(node->child);	// 值是一个对象，则递归操作建子树 
		}
		else if (str[i] == '"') {
			node->child = NULL; 
			int j = i;
			// j<str字符串长度是为了结束字符'}'前没有','的情况 
			while (str[j] != ',' && str[j] != '}' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->value);
			i = j;		// i位置为','或'}' 
		}
		
		// 为第一个结点时将node结点指针赋给tree指针 
		if (isFirstNode) {
			tree = node;
			isFirstNode = false;
		}
		// 不是第一个结点，则将上个结点的兄弟指针指向当前结点 
		else preNode->brother = node;
		preNode = node;
	
		fscanf(fp, "%s", str);
		i = 0;
	}
	node->brother = NULL;
}
 
// 找value值
char* FindValue(Tree tree, char *str) {
	int i = 0;
	char key[1000];
	while (str[i]!='.' && i<strlen(str)) {
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	
	TNode *node = tree;
	while (node) {
		if (strcmp(node->key, key) == 0) {
			if (str[i] == '.') {
				int j = 0;
				char nextStr[1000];
				i++;
				while (i<strlen(str)) {
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
void ShowTree(Tree tree, int tab) {	
	TNode *node = tree;
	while (node) {
		for (int i=0; i<tab; i++) printf("|  ");
		printf("|--%s", node->key);
		if (node->child) {
			printf("\n");
			ShowTree(node->child, tab+1);
		}
		else printf(":%s\n", node->value);
		node = node->brother;
	}
} 


int main() {
	fileOpen("r");
	
	int n = 0, m = 0;
	fscanf(fp, "%d%d", &n, &m);
	
	Tree tree = NULL;
	char strLine[10000];
	fscanf(fp, "%s", strLine);// 读取开始的'{'
	CreateTree(tree);
	
	system("cls");	// 清屏 
	//TraverseTree(tree);
	printf("+\n");
	ShowTree(tree, 0);
	printf("\n\n按任意键继续");
	getchar();
	system("cls");
	
	// 读取输入数据 
	for (int i=0; i<m; i++) {
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


