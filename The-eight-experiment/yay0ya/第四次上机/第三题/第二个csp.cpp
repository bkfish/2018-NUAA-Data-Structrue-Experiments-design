#include<iostream>
using namespace std;
int N=100;
int main(){
	int seat[N]={};
	int n,*p,add=0;
	void buyone(int *seat);
	void buytwo(int *seat);
	void buythree(int *seat);
	void buyfour(int *seat);
	void buyfive(int *seat);
	cin>>n;
	p=new int [n];
	for(int i=0;i<n;i++){
		cin>>p[i];
		while(p[i]==0||p[i]>5){
			cout<<"重新输入该票数\n";
			cin>>p[i]; 
		}
		add+=p[i];
	}
	while(add>N){
		cout<<"请重新输入购买的票数"<<endl;
		for(int i=0;i<n;i++){
		cin>>p[i];
		add+=p[i];
	} 	
	}
	cout<<"购买的票数分别为\n";
	cout<<endl;
	for(int i=0;i<n;i++){
		switch(p[i]){
			case 1:buyone(seat),cout<<endl;break;
			case 2:buytwo(seat),cout<<endl;break;
			case 3:buythree(seat),cout<<endl;break;
			case 4:buyfour(seat),cout<<endl;break;
			case 5:buyfive(seat),cout<<endl;break;
		}
		}
	return 0;
	}
	
void buyone(int *seat){
	for(int i=0;i<N;i++){
		if(seat[i]==0){
			seat[i]=1;
			cout<<i+1<<" ";
			break;
		}
	}
}
void buytwo(int *seat){
	int flag=0;
	for(int i=0;i<N;i++){
		if(seat[i]==0&&seat[i+1]==0&&(i+1)%10!=5&&(i+1)%10!=0){
			cout<<i+1<<" "<<i+2;
			seat[i]=1;
			seat[i+1]=1;
			flag=1;
			break;
		}
	
		}	
		if(flag==0){
		buyone(seat);//如果检索后不存在连续的两个位置 
		buyone(seat);//就一张一张的购买票 
}
}
void buythree(int *seat){
	int flag=0;
	for(int i=0;i<N;i++){
		if(seat[i]==0&&seat[i+1]==0&&seat[i+2]==0&&(i+1)%10!=5&&(i+1)%10!=4&&(i+1)%10!=0&&(i+1)%10!=9){
			seat[i]=1;
			seat[i+1]=1;
			seat[i+2]=1;
			flag=1;
			cout<<i+1<<" "<<i+2<<" "<<i+3;
			break;
		}
		}
		if(flag==0)
		{
			buyone(seat);
			buyone(seat);
			buyone(seat);
		}
}

void buyfour(int *seat){
	int flag=0;
	for(int i=0;i<N;i++){
		if(seat[i]==0&&seat[i+1]==0&&seat[i+2]==0&&seat[i+3]==0&&(i+1)%10!=5&&(i+1)%10!=4&&(i+1)%10!=3&&(i+1)%10!=8&&(i+1)%10!=0&&(i+1)%10!=9){
			seat[i]=1;
			seat[i+1]=1;
			seat[i+2]=1;
			seat[i+3]=1;
			flag=1;
			cout<<i+1<<" "<<i+2<<" "<<i+3<<" "<<i+4;
			break;
		}
		}
		if(flag==0)
		{
			buyone(seat);//如果检索后不存在连续的两个位置 
			buyone(seat);//就一张一张的购买票 
			buyone(seat);
			buyone(seat);
		}
}
void buyfive(int *seat){
	int flag=0;
	for(int i=0;i<N;i++){
		if(seat[i]==0&&seat[i+1]==0&&seat[i+2]==0&&seat[i+3]==0&&(i+1)%10!=5&&(i+1)%10!=4&&(i+1)%10!=3&&(i+1)%10!=2&&(i+1)%10!=8&&(i+1)%10!=7&&(i+1)%10!=0&&(i+1)%10!=9){
			seat[i]=1;
			seat[i+1]=1;
			seat[i+2]=1;
			seat[i+3]=1;
			seat[i+4]=1;
			flag=1;
			cout<<i+1<<" "<<i+2<<" "<<i+3<<" "<<i+4<<" "<<i+5;
			break;
		}
		}
		if(flag==0)
		{
			buyone(seat);//如果检索后不存在连续的两个位置 
			buyone(seat);//就一张一张的购买票 
			buyone(seat);
			buyone(seat);
			buyone(seat);
		}
}
