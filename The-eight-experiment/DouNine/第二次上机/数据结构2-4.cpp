#include<stdio.h>
#include<stdlib.h>

int main() {
	
	int n = 0;
	scanf("%d", &n);
	int *a = (int*)malloc(sizeof(int) * n);
	for(int i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}	
	
	int temp = 0;
	for(int i=1; i<n; i++) {
		for(int j=i; j>0 && a[j-1]>a[j]; j--) {
			temp = a[j-1];
			a[j-1] = a[j];
			a[j] = temp;
		}
	} 
	
	/*
	for(int i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 
	printf("\n");
	*/
	
	int mid = a[n/2], low = 0, high = 0;
	for(int i=0; i<n; i++) {
		if(a[i] < mid) low++;
		else if(a[i] > mid) high++;
	}
	if(low == high) printf("%d", mid);
	else printf("-1");
}
