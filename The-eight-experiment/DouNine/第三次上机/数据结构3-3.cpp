#include<stdio.h>

int num[8];
int flag = 0;

void show() {
	flag++;
	printf("µÚ%dÖÖ£º", flag);
	for(int i=0; i<8; i++) printf("%d ", num[i]);
	printf("\n");
}

bool check(int length) {
	for (int i = 0; i < length-1; i++) {
	 	for (int j = i+1; j < length; j++) {
	 	 	if (num[i] == num[j] || num[j]-num[i] == j-i || num[i]-num[j] == j-i) {
	 	 		return false;
	 	 	}
	 	}
	}
	return true;
}

void fun(int i) {
	if(i == 8) {
		show();
		return;
	}	
	for(num[i]=1; num[i]<=8; num[i]++) {
		if(check(i+1)) fun(i+1);
	}
	return;
}

int main() {
	fun(0);
	printf("========%d\n", flag);
} 
