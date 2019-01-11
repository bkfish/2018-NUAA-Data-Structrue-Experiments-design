#include<iostream>
using namespace std;
#include"stack.h"
#define N 8
 int count=0;
int main() {
	void eightqueen(int*quenn,int n);
	int data[N]={};
	eightqueen(data,0);

}
void eightqueen(int *queen,int n){
	int i=0,j=0,flag;
	if(n==N)
		{
			count++;	
			printf("µÚ%dÖÖ\n",count);
			for(i=0;i<N;i++){
				for(j=0;j<N;j++){
					if(queen[i]==j)
					printf("*");
					else
					printf("0");
				}
			printf("\n");
			}
		}
		for(i=0;i<N;i++){
			queen[n]=i;flag=1;
			for(j=0;j<n;j++){
				if(queen[j]==i||queen[j]-j==i-n||n+i==j+queen[j]){
					flag=0;
					break;
				}
			}
			if(flag==1){
				eightqueen(queen,n+1); 
			}
		}
}

