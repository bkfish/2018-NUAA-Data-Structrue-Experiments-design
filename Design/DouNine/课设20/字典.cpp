/*
[问题描述]
利用键树结构，建立一个微型电子字典。
[基本要求]
实现生词的加入，单词的查找、删除，修改等操作。
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;

typedef struct TNode
{
	char type;	// type值：1表示是单词结尾，0则表示不是 
	char ch;
	TNode *child;
	TNode *brother;
}*Tree;

// 全局变量 
FILE *fp;
char fileName[] = "testWord.txt";


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

// 显示树 
void ShowTree(Tree tree, int tab) 
{	
	TNode *node = tree;
	while (node) 
	{
		for (int i=0; i<tab; i++) printf("|  ");
		printf("|--%c(%d)\n", node->ch, node->type);
		if (node->child) 
		{
			ShowTree(node->child, tab+1);
		}
		node = node->brother;
	}
}

// 显示单词树 
void ShowWordTree(Tree tree, char *word, int tab) 
{
	if (!tree) return;
	
	TNode *node = tree;
	char nextWord[100];
	strcpy(nextWord, word);
	int next = strlen(nextWord);
	while (node) 
	{
		nextWord[next] = node->ch;
		nextWord[next+1] = '\0';
		
		for (int i=0; i<tab; i++) printf("|  ");
		if (node->type) printf("|--%c(%s)\n", node->ch, nextWord);
		else printf("|--%c\n", node->ch);
		
		ShowWordTree(node->child, nextWord, tab+1);
		node = node->brother;
	}
}

// 增加单词
void AddWord(Tree &tree, char *word) 
{
	if (strlen(word) == 0) return;
	
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	// 如果树为空，则建树 
	if (!tree) 
	{
		tree = (TNode*)malloc(sizeof(TNode));
		tree->child = NULL;
		tree->brother = NULL;
		tree->ch = ch;
		tree->type = 0;
	}
	
	// 在兄弟中找匹配 
	TNode *node = tree, *pre = NULL;
	while (node && node->ch <= ch) 
	{
		if (node->ch == ch) 
		{
			if (strlen(word) == 1) node->type = 1;
			AddWord(node->child, nextWord);
			return;
		}
		pre = node;
		node = node->brother;
	}
	
	// 如果兄弟没找到匹配的，就新建结点 
	TNode *newNode = (TNode*)malloc(sizeof(TNode));
	newNode->child = NULL;
	newNode->ch = ch;
	newNode->type = 0; 
	newNode->brother = node;
	
	if (!pre) tree = newNode;
	else pre->brother = newNode;
	
	if (strlen(word) == 1) newNode->type = 1;
	AddWord(newNode->child, nextWord);
} 

// 删除单词 
void DeleteWord(Tree &tree, char *word) 
{
	if (strlen(word) == 0) return;
	
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	TNode *node = tree, *pre = NULL;
	while (node) 
	{
		if (node->ch == ch) 
		{
			// 先将该字符之后的字符删去 
			DeleteWord(node->child, nextWord);
			// 删除当前字符 
			if (pre) 
			{
				pre->brother = node->brother;
				free(node);
			}
			else 
			{
				tree = node->brother;
				free(node);
			}
		}
		pre = node;
		node = node->brother;
	}
}

// 查找单词，存在返回true，不存在返回false 
Tree FindWord(Tree tree, char *word) 
{
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	TNode *node = tree;
	while (node) 
	{
		if (node->ch == ch) 
		{
			if (strlen(word) == 1) 
			{
				return node;
			}
			else return FindWord(node->child, nextWord);
		}
		node = node->brother;
	}
	
	return NULL;
}

// 修改单词 
void ModifyWord(Tree &tree, char *word, char *newWord) 
{
	printf("----%s %s----\n", word, newWord);
	
	char ch = word[0], newCh = newWord[0];
	char nextWord[100], nextNewWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	for (int i=0; i<strlen(newWord); i++) nextNewWord[i] = newWord[i+1];
	
	TNode *node = tree;
	while (node) 
	{
		printf("%c %c\n", node->ch, ch);
		if (node->ch == ch) 
		{
			if (ch != newCh) 
			{
				
				node->ch = newCh;
			}
			if (strlen(newWord) == 1) 
			{
				node->type = 1;
				DeleteWord(node->child, nextWord);
			}
			else if (strlen(word) == 1) 
			{
				node->type = 0;
				AddWord(node->child, nextNewWord);
			}
			else ModifyWord(node->child, nextWord, nextNewWord);
		}
		node = node->brother;
	}
}

// 补全单词
void CompleteWord(Tree tree, char *word) 
{
	if (!tree) return;
	
	TNode *node = tree;
	char nextWord[100];
	strcpy(nextWord, word);
	int next = strlen(nextWord);
	while (node) 
	{
		nextWord[next] = node->ch;
		nextWord[next+1] = '\0';
		
		if (node->type) 
		{
			printf("-->%s\n", nextWord);
		}
		CompleteWord(node->child, nextWord);
		node = node->brother;
	}
} 

// 初始化树
void CreateTree(Tree &tree) 
{
	char word[100];
	while (!feof(fp)) 
	{
		fscanf(fp, "%s", word);
		//printf("%s\n", word);
		AddWord(tree, word);
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

// 显示选项
void choose() 
{
	system("cls");
	printf("\n|---------------------------|\n");
	printf("|0.退出                     |\n");
	printf("|1.增加单词                 |\n");
	printf("|2.删除单词                 |\n");
	printf("|3.修改单词                 |\n");
	printf("|4.查找单词                 |\n");
	printf("|5.显示单词树               |\n");
	printf("|---------------------------|\n");
	printf("\n请输入你的选择(0-5):\n");
}


int main() 
{
	fileOpen("r");
	
	Tree tree = NULL;
	CreateTree(tree);
	
	int n = 0;
	choose();
	scanf("%d", &n);
	while (n) 
	{
		if (n <= 0 || n > 5) 
		{
			printf("error! try again\n");
			printf("\n请输入你的选择(0-5):\n");
			scanf("%d", &n);
			continue;
		}
		
		char word[100];
		switch (n) 
		{
			// 增加单词 
			case 1: 
			{
				printf("请输入您要增加的单词：\n");
				scanf("%s", word);
				AddWord(tree, word);
				printf("增加成功！"); 
				break;
			}
			// 删除单词 
			case 2: 
			{
				printf("请输入您要删除的单词：\n");
				scanf("%s", word);
				DeleteWord(tree, word);
				printf("删除成功！");
				break;
			}
			// 修改单词 
			case 3: 
			{
				printf("请输入您要修改的单词：\n");
				scanf("%s", word);
				if (!FindWord(tree, word)) 
				{
					printf("no this word\n");
					break;
				}
				char newWord[100];
				printf("请输入修改后的单词：\n");
				scanf("%s", newWord);
				ModifyWord(tree, word, newWord);
				printf("修改成功！");
				break;
			}
			// 查找单词 
			case 4: 
			{
				printf("请输入您要查找的单词：\n");
				scanf("%s", word);
				Tree node = FindWord(tree, word);
				if (node && node->type) printf("find this word\n");
				else 
				{
					printf("no find this word\n");
					if (node) 
					{
						printf("\ni guess you want to find these words:\n\n");
						CompleteWord(node->child, word);
					}
				}
				break;
			}
			// 显示单词树 
			case 5: 
			{
				printf("*\n");
				ShowWordTree(tree, "", 0);
				break;
			}
		}
		
		printf("\n");
		system("pause");
		choose();
		scanf("%d", &n);
	}
	
	DestroyTree(tree);
	fileClose();
}
