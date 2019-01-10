/*
碰撞的小球
问题描述
　　数轴上有一条长度为L（L为偶数)的线段，左端点在原点，右端点在坐标L处。有n个不计体积的小球在线段上，
	开始时所有的小球都处在偶数坐标上，速度方向向右，速度大小为1单位长度每秒。
　　当小球到达线段的端点（左端点或右端点）的时候，会立即向相反的方向移动，速度大小仍然为原来大小。
　　当两个小球撞到一起的时候，两个小球会分别向与自己原来移动的方向相反的方向，以原来的速度大小继续移动。
　　现在，告诉你线段的长度L，小球数量n，以及n个小球的初始位置，请你计算t秒之后，各个小球的位置。
提示
　　因为所有小球的初始位置都为偶数，而且线段的长度为偶数，可以证明，不会有三个小球同时相撞，小球到达线段端点
	以及小球之间的碰撞时刻均为整数。
　　同时也可以证明两个小球发生碰撞的位置一定是整数（但不一定是偶数）。
输入格式
　　输入的第一行包含三个整数n, L, t，用空格分隔，分别表示小球的个数、线段长度和你需要计算t秒之后小球的位置。
　　第二行包含n个整数a1, a2, …, an，用空格分隔，表示初始时刻n个小球的位置。
输出格式
　　输出一行包含n个整数，用空格分隔，第i个整数代表初始时刻位于ai的小球，在t秒之后的位置。

样例输入
3 10 5
4 6 8
样例输出
7 9 9

样例输入
10 22 30
14 12 16 6 10 2 8 20 18 4
样例输出
6 6 8 2 4 0 4 12 10 2
*/
#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct {
	int pos;	// 小球的位置 
	int dir;	// 小球的方向 
}Pellet;

int main() {
	int n, l, t;
	scanf("%d%d%d", &n, &l, &t);
	
	Pellet *pellet = (Pellet*)malloc(sizeof(Pellet) * n);
	int *p = (int*)malloc(sizeof(int) * n);
	for (int i=0; i<n; i++) {
		scanf("%d", &pellet[i].pos);
		p[i] = i;			// “指针”指向小球本来位置 
		pellet[i].dir = 1;	// 小球初始向右 
	}
	
	// 将p这个“指针”数组，根据“指针”指向的值排序
	for (int i=0; i<n-1; i++) {
		int min = pellet[p[i]].pos;
		int temp;
		for (int j=i+1; j<n; j++) {
			if (pellet[p[j]].pos < min) {
				min = pellet[p[j]].pos;
				// 将“指针”交换 
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
	
	// 用排序好的“指针”数组进行上述过程
	// 每过一秒 
	for (int i=0; i<t; i++) {
		// 遍历“指针”数组 
		for (int j=0; j<n; j++) {
			pellet[p[j]].pos += pellet[p[j]].dir;	// 根据每个球的方向（1或-1）进行移位 
			// 如果小球和左边一个小球位置相同，则将两个小球都改变方向 
			if ((j != 0) && (pellet[p[j-1]].pos == pellet[p[j]].pos)) {
				pellet[p[j]].dir = 0 - pellet[p[j]].dir;
				pellet[p[j-1]].dir = 0 - pellet[p[j-1]].dir;
			}
			// 如果小球碰壁了，反向 
			else if ((pellet[p[j]].pos == l) || (pellet[p[j]].pos == 0)) {
				pellet[p[j]].dir = 0 - pellet[p[j]].dir;
			}
		}
	}
	
	for (int i=0; i<n; i++) {
		printf("%d ", pellet[i].pos);
	}
	
	free(pellet);
	free(p);
} 



