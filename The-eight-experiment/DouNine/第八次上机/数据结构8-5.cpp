/*
问题描述
　　给定n个整数，请统计出每个整数出现的次数，按出现次数从多到少的顺序输出。
输入格式
　　输入的第一行包含一个整数n，表示给定数字的个数。
　　第二行包含n个整数，相邻的整数之间用一个空格分隔，表示所给定的整数。
输出格式
输出多行，每行包含两个整数，分别表示一个给定的整数和它出现的次数。
按出现次数递减的顺序输出。如果两个整数出现的次数一样多，则先输出值较小的，然后输出值较大的。
样例输入
12
5 2 3 3 1 3 4 2 5 2 3 5
样例输出
3 4
2 3
5 3
1 1
4 1
*/
#include<iostream>

using namespace std;

typedef struct {
	int key;
	int value;
}Map;

int n;

void Set(Map *map, int key) {
	int i = key%n;
	while (1) {
		if (map[i].key == -1 || map[i].key == key) {
			map[i].key = key;
			map[i].value++;
			return;
		}
		i++;
		if (i == n) i = 0;
	}
}

int main() {
	scanf("%d", &n);
	int num[n];
	for (int i=0; i<n; i++) {
		scanf("%d", &num[i]);
	}
	
	Map map[n];
	for (int i=0; i<n; i++) {
		map[i].key = -1;
		map[i].value = 0;
	}
	
	for (int i=0; i<n; i++) {
		Set(map, num[i]);
	}	
	
	for (int i=0; i<n; i++) {
		if (map[i].key == -1) continue;
		Map max = map[i];
		int maxPos = i;
		for (int j=i; j<n; j++) {
			if (map[j].key == -1) continue;
			if ((map[j].value > max.value) 
				|| (map[j].value == max.value && map[j].key < map[i].key)) {
				max = map[j];
				maxPos = j;
			}
		}
		map[maxPos] = map[i];
		map[i] = max;
	}
	
	for (int i=0; i<n; i++) {
		if (map[i].key != -1) cout<<map[i].key<<" "<<map[i].value<<endl;
	}
	
	return 0;
}


