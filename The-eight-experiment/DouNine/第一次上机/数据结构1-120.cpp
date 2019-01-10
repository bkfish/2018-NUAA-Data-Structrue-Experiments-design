#include<stdio.h>
#include<stdlib.h>

int main() {
	int n;
	printf("请输入多项式P(x)的最高次幂："); 
	scanf("%d", &n);
	
	int *a = (int*)malloc(sizeof(int) * (n+1));
	for(int i=0; i<=n; i++) {
		printf("请输入幂为%d项的系数：", i);
		scanf("%d", &a[i]);
	}
	
	printf("多项式P(x)=%d*(x^%d)", a[0], 0);
	for(int i=1; i<=n; i++) {
		printf("+%d*(x^%d)", a[i], i);
	}
	printf("\n");
	
	int x0 = 0;
	printf("请输入x0：");
	scanf("%d", &x0);
	int sum = a[n];
	for(int i=n-1; i>=0; i--) {
		sum = sum * x0 + a[i];
	}
	
	printf("多项式P(x0)的值是：%d\n", sum);  
	free(a);
}
