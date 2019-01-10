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
	
	int cur = 0, i = 0, j = n-1;
	while (cur < j) {
		if (a[cur] == 0) {
			int t = a[i];
			a[i] = a[cur];
			a[cur] = t;
			i++;
			cur++;
		}
		if (a[cur] == 2) {
			int t = a[j];
			a[j] = a[cur];
			a[cur] = t;
			j--;
		}
		if (a[cur] == 1) {
			cur++;
		}
	}
	
	for (int i=0; i<n; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
