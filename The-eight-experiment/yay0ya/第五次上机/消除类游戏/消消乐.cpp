#include<iostream>
using namespace std;
int main(){
	int n1[100][100]={};
	int n2[100][100]={};
	int N,M;
	cin>>N;
	cin>>M;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>n1[i][j];
			n2[i][j]=n1[i][j];
		}
	}
	int record=0,flag=0;
	for(int i=0;i<N;i++){
		record=n1[i][0];
		flag=0;
		for(int j=0;j<M;j++){
			if(record!=n1[i][j]){
				record=n1[i][j];
				flag=0;
			}
			if(record==n1[i][j]){
				flag++;
			}
			if(flag>2){
				for(int t=0;t<flag;t++){
					n1[i][j-t]=0;
				}
			}
	}
	}
	for(int j=0;j<M;j++){
		record=n2[0][j];
		flag=0;
		for(int i=0;i<N;i++){
			if(record!=n2[i][j]){
				record=n2[i][j];
				flag=0;
			}
			if(record==n2[i][j]){
				flag++;
			}
			if(flag>2){
				for(int t=0;t<flag;t++){
					n2[i-t][j]=0;
				}
			}
		}
	
	}
	cout<<endl;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(n2[i][j]==0){
				n1[i][j]=0;
			}
			cout<<n1[i][j]<<" ";
		}
		cout<<endl;
	}
}
