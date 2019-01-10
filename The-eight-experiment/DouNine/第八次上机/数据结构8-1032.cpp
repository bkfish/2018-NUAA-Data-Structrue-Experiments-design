/*
荷兰国旗
*/
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
	
int main() {
	srand(time(0));
	int n;
	cout<<"请输入色块条数：\n";
	cin>>n;
	int a[n];
	for (int i=0; i<n; i++) {
		a[i] = rand()%3;
	}
	
	for (int i=0; i<n; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	int i = 0, j = n-1, k;
	int temp, t;

	// 当i位置为0，前进 
	while (a[i] == 0) i++;
	// 当k位置为0或2时，前进 
	k = i; 
	while (a[k] != 1) {
		// 如果k位置为0，与i位置（i位置必为2）交换，i前进 
		if (a[k] == 0) {
			t = a[k];
			a[k] = a[i];
			a[i] = t;
			i++;
		}
		// k前进 
		k++;
	}
	// 拿到1存起来 
	temp = a[k];
	a[k] = a[i];
	
	int ki = i, kj = j; 
	while (1) {
		// j位置往前走，直到不为2 
		while (a[j] == 2) j--;
		// 若kj在j之后，则将kj=j 
		if (kj > j) kj = j;
		// 当kj位置为1或2时，kj-- 
		while (a[kj] != 0 && kj > ki) {
			// 当kj位置为2时，与j位置（j位置必为1）交换，j-- 
			if (a[kj] == 2) {
				t = a[kj];
				a[kj] = a[j];
				a[j] = t;
				j--;
			}
			kj--;
		}
		// 如果kj与ki相遇，则结束 
		if (kj == ki) break;
		// 当kj位置为0时，放到i位置（i位置原来为空），同时将j位置的1放到kj位置，j位置为空 
		a[i] = a[kj];
		a[kj] = a[j];
		
		// i位置同理 
		while (a[i] == 0) i++;
		if (ki < i) ki = i;
		while (a[ki] != 2 && ki < j) {
			if (a[ki] == 0) {
				t = a[ki];
				a[ki] = a[i];
				a[i] = t;
				i++;
			}
			ki++;
		}
		if (ki == kj) break;
		a[j] = a[ki];
		a[ki] = a[i];
	}
	a[i] = temp;
	
	for (int i=0; i<n; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
