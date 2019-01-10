/*
消除类游戏是深受大众欢迎的一种游戏，游戏在一个包含有n行m列的游戏棋盘上进行，
棋盘的每一行每一列的方格上放着一个有颜色的棋子，当
一行或一列上有连续三个或更多的相同颜色的棋子时，这些棋子都被消除。
当有多处可以被消除时，这些地方的棋子将同时被消除。
现在给你一个n行m列的棋盘，棋盘中的每一个方格上有一个棋子，请给出经过一次消除后的棋盘。

请注意：一个棋子可能在某一行和某一列同时被消除。

输入格式
　　输入第一行包含两个整数n, m，用空格分隔，分别表示棋盘的行数和列数。
　　接下来n行，每行m个整数，用空格分隔，分别表示每一个方格中的棋子的颜色。颜色使用1至9编号。
输出格式
　　输出n行，每行m个整数，相邻的整数之间使用一个空格分隔，表示经过一次消除后的棋盘。如果一个方格中的棋子被消除，则对应的方格输出0，否则输出棋子的颜色编号。
样例输入
4 5
2 2 3 1 2
3 4 5 1 4
2 3 2 1 3
2 2 2 4 4
样例输出
2 2 3 0 2
3 4 5 0 4
2 3 2 0 3
0 0 0 4 4
样例说明
　　棋盘中第4列的1和第4行的2可以被消除，其他的方格中的棋子均保留。
样例输入
4 5
2 2 3 1 2
3 1 1 1 1
2 3 2 1 3
2 2 3 3 3
样例输出
2 2 3 0 2
3 0 0 0 0
2 3 2 0 3
2 2 0 0 0
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int pri;
	int last;
}Elem;

int main() {
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	
//	Elem **W = (Elem**)malloc(sizeof(Elem*) * n);
//	for (int i = 0; i < n; i++) {
//		Elem *temp = (Elem*)malloc(sizeof(Elem) * m);
//		for (int j = 0; j < m; j++) {
//			scanf("%d", &temp[j].pri);
//			temp[j].last = temp[j].pri;
//		}
//		W[i] = temp;
//	}
	
	Elem W[n][m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &W[i][j].pri);
			W[i][j].last = W[i][j].pri;
		}
	}
	
	// 消每一行 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m-1;) {
			int k = j+1;
			int same = 1;	// 从当前开始与当前位相同且连续的数的个数
			while ((k < m) && (W[i][j].pri == W[i][k].pri)) {
				k++;
				same++;
			} 
			if (same >= 3) {
				k = j;
				while (k <= j+same-1) {
					W[i][k].last = 0;
					k++;
				}	
			}
			j += same;
		}
	}
	
	// 消每一列，从列开始遍历 
	for (int col = 0; col < m; col++) {
		for (int row = 0; row < n-1;) {
			int k = row+1;
			int same = 1;	// 从下一位开始与当前位相同且连续的数的个数
			while ((k < n) && (W[row][col].pri == W[k][col].pri)) {
				k++;
				same++;
			} 
			if (same >= 3) {
				k = row;
				while (k <= row+same-1) {
					W[k][col].last = 0;
					k++;
				}	
			}
			row += same;
			//printf("%d  %d\n", col, row);
		}
	}
	
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", W[i][j].last);
		} 
		printf("\n");
	}
	
//	for (int i=0; i<n; i++) free(W[i]);
//	free(W);
}



