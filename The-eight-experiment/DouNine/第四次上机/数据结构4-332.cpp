/*
用循环队列，求k阶斐波那契数列前n项。 
循环队列长度为k，结束后留在循环队列应是k阶斐波那契数列最后k项。
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int font, rear;
	int length;
}Queue;

int main() {
	printf("请输入k、n：");
	int k = 0, n = 0;
	scanf("%d%d", &k, &n); 
	int *q = (int*)malloc(4*k);
	
	Queue queue;
	queue.font = queue.rear = queue.length = 0;
	int sum = 0;
	for(int i=0; i<=n; i++) {
		if(i < k-1) {
			q[queue.rear] = 0;
			queue.rear++; 
		}
		if(i == k-1) {
			q[queue.rear] = 1;
			queue.rear++;
			sum = 1;
		}
		if(i > k-1) {
			int temp = sum - q[queue.font%k];
			queue.font++;
			q[queue.rear%k] = sum;
			//printf("-----------%d\n", sum);
			queue.rear++;
			sum += temp;
		}
	}
	
	for(int i=queue.font; i<queue.rear; i++) {
		//printf("================%d\n", i);
		printf("%d\n", q[i%k]);
	}
	
	free(q);
} 
