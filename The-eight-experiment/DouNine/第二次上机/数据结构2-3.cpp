#include<stdio.h>
#include<stdlib.h>

int main() {
	
	int n = 0;
	scanf("%d", &n);
	
	int* a = (int*)malloc(sizeof(int) * n);
	for(int i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	
	int account = 0;
	for(int i=1; i<n-1; i++) {
		if((a[i]>a[i-1] && a[i]>a[i+1]) || (a[i]<a[i-1] && a[i]<a[i+1])) {
			account++;
		}
	}
	printf("%d", account);
	
	free(a);
}
 
