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

// 检测是否遇到空字符(超限)，若遇到则重新读取字符串 
void Check(char* &str, int &pos) {
	if (pos >= strlen(str)) {
		scanf("%s", str);
		pos = 0;
	}
}

// 建树函数，递归 
void CreateTree(Tree &tree, char *str, int &i) {
	
	TNode *preNode = tree, *node;
	bool flag = false;	// 判断是否为根节点 
	i++;	// i++避过'{' 
	Check(str, i);
	
	while (str[i] != '}') {
		node = (TNode*)malloc(sizeof(TNode));
		
		//printf("前一半======%s\n", str);
		if (str[i] == '"') {
			int j = i;
			while (str[j] != ':' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->key);
			i = j;
			Check(str, i);
		}
		i++;
		Check(str, i);
		
		//printf("后一半=====%s\n", str);
		if (str[i] == '{') {
			strcpy(node->value, "object");
			CreateTree(node->child, str, i);	// 值是一个对象，则递归操作 
		}
		else if (str[i] == '"') {
			node->child = NULL; 
			int j = i;
			while (str[j] != ',' && str[j] != '}' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->value);
			i = j;
			Check(str, i);
		}
		
		// 若为第一个结点则将结点指针赋给tree指针 
		if (!flag) {
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
	
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	
	Tree tree = NULL;
	char strLine[10000];
	scanf("%s", strLine);
	int start = 0;
	CreateTree(tree, strLine, start);	// 1位置开始忽略开始的'{'
	
	// 读取输入数据 
	for (int i=0; i<m; i++) {
		scanf("%s", strLine);
		char *ret = FindValue(tree, strLine);
		char value[1000];
		if (!ret) sprintf(value, "NOTEXIST");
		else if (strcmp(ret, "object") == 0) sprintf(value, "OBJECT");
		else sprintf(value, "STRING %s", ret);
		printf("%s\n", value);
	}
	
	DestroyTree(tree);
}
