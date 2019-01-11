#include<iostream>
using namespace std;
#include<fstream>
#define none 32767
typedef struct Coupon{
	int data;
	bool use;
}Coupon,Goods; 
int  Partition(Coupon *p,int low,int high){
	int record=low;
	int flag=p[low].data;
	while(low<high){
		while(low<high&&p[high].data<=flag) 
			high--;
		p[low].data=p[high].data;
		while(low<high&&p[low].data>=flag) 
			low++;
		p[high].data=p[low].data;
	}
	p[low].data=flag;
	return low;
}
void Qsort(Coupon L[],int low,int high){
	int record;
	if(low<high){
		record=Partition(L,low,high);
		Qsort(L,low,record-1);
		Qsort(L,record+1,high);
	}
}
int main(){
	fstream file;
	file.open("data.txt",ios::in);
	int N;//表示优惠券的数额
	file>>N;
	Coupon coupon[N];//为优惠券们申请N个空间
	
	
	int i,j,k;
	for(i=0;i<N;i++){
		file>>coupon[i].data;
		coupon[i].use=0;//当use为0时表示不曾用过这张优惠券 
	}
	
	
	int M;//表示商品的数量
	file>>M;
	Goods goods[M];//为商品申请M个空间 
	for(i=0;i<M;i++){
		file>>goods[i].data;
		goods[i].use=0;//道理同上 
	}
	Qsort(coupon,0,N-1);
	Qsort(goods,0,M-1);
	 i=0;
	int add=0;
	while(coupon[i].data>0&&goods[i].data>0&&i<M&&i<N){
		add+=coupon[i].data*goods[i].data;
		coupon[i].use=1;
		goods[i].use=1;
		i++;
	}
	j=1;
	while(coupon[N-j].data<0&&goods[M-j].data<0&&j<=M&&j<=N){
		add+=coupon[N-j].data*goods[M-j].data;
		coupon[i].use=1;
		goods[i].use=1;
		j++;
	}
	cout<<add;
	return 0;
}

