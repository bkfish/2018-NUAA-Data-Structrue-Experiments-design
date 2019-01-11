#include"LinkList.h"
int main(){
	int N,M;
	int x1,x2,y1,y2;	
	point *click;
	W w;
	cout<<"input windows numbers"<<endl; 
	cin>>N;
	cout<<"input click numbers"<<endl;
	cin>>M;
	Createwindows(w,N);
	click=new point [M];
	CreateClick(click,M);
	idenfy(w,N,click,M);
	return 0;	
}
