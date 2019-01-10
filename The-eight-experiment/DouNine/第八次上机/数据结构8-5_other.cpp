#include<iostream>
#include<vector>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	int num[1005];
	for (int i=0; i<=1000; i++) num[i] = 0;
	
	vector<int> p;
	for (int i=0; i<n; i++) {
		if (!num[a[i]]) p.push_back(a[i]);
		num[a[i]]++;
	}
	
	for (int i=0; i<p.size(); i++) {
		int max = p[i];
		int maxPos = i;
		for (int j=i; j<p.size(); j++) {
			if (num[p[j]] > num[max] || (num[p[j]] == num[max] && p[maxPos] > p[j])) {
				max = p[j];
				maxPos = j;
			}
		}
		p[maxPos] = p[i];
		p[i] = max;
	}
	
	for (int i=0; i<p.size(); i++) {
		cout<<p[i]<<" "<<num[p[i]]<<endl;
	}
}
