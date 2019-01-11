#include<iostream>
using namespace std;
int main(){
	int Partition(int *p,int low,int high);
	void Qsort(int *p,int low,int high);
	int *p,n,low,high;
	cin>>n;
	p=new int [n];
	for(int i=0;i<n;i++){
		cin>>p[i];
	}
	cout<<endl;
	Qsort(p,0,n-1);
	for(int i=0;i<n;i++){
		cout<<p[i]<<" ";
	}
	cout<<endl;
	return 0;
} 
int Partition(int *p,int low,int high){
	int record=low;
	int flag=p[low];
	while(low<high){
		while(low<high&&p[high]>=flag) 
			high--;
		p[low]=p[high];
		while(low<high&&p[low]<=flag) 
			low++;
		p[high]=p[low];
	}
	p[low]=flag;
	return low;
}
void Qsort(int *p,int low,int high){
	int record;
	if(low<high){
		record=Partition(p,low,high);
		Qsort(p,low,record-1);
		Qsort(p,record+1,high);
	}
}
