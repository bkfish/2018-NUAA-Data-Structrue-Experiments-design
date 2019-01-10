
/*某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着相似的兴趣爱好，形成一个朋友圈。一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，如果A和B是朋友，且B和C是朋友，则A和C也是朋友。请编写程序计算最大朋友圈中有多少人。 
[基本要求]
（1）输入说明：输入的第一行包含两个正整数N (N<=30 000)和M (M<=1000)，分别代表学校的学生总数和俱乐部的个数。随后的M行每行按以下格式给出一个俱乐部的信息，其中学生从1-N编号：
第i个俱乐部的人数Mi（空格）学生1（空格）学生2… 学生Mi 
（2）输出说明：输出一个整数，表示在最大朋友圈中有多少人。
（3）测试用例： 
输入  7 4
      3 1 2 3
      2 1 4
      3 5 6 7
      1 6 
  输出  4*/
#include<cstdio>
#include<cstdlib>

void Connect(int *arr, int a, int b) {
	int i=a;
	while (arr[i] && arr[i] != a) {
		i = arr[i];
	}
	
	int j=b;
	while (arr[j] && arr[j] != b) {
		j = arr[j];
	}
	
	arr[i] = b;
	arr[j] = a;
}

int main() {
	
	int n=0, m=0;
	scanf("%d%d", &n, &m);
	int *stu = (int*)malloc(sizeof(int) * (n+1));
	for (int i=0; i<=n; i++) stu[i] = 0;
	for (int i=0; i<m; i++) {
		int count=0;
		scanf("%d", &count);
		int *club = (int*)malloc(sizeof(int) * count);
		for (int j=0; j<count; j++) {
			scanf("%d", &club[j]);
		}
		for (int j=1; j<count; j++) {
			Connect(stu, club[j-1], club[j]);
		}
		free(club);
	}
	
	int max=0;
	for (int i=1; i<=n; i++) {
		int count=1;
		int j=i;
		while (stu[j] && stu[j] != i) {
			j = stu[j];
			count++;
		}
		if (count > max) max = count;
	}
	printf("%d", max);
	free(stu);
	system("pause");
}

