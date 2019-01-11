#include<iostream>
using namespace std;
typedef struct ball{
	int locate;//小球现在的位置
	bool state;//默认状态为1的时候前进，状态为0的时候反向 
}Ball;
int main(){
	int n;
	Ball *ball;
	cin>>n;//小球的个数
	ball=new Ball[n];
	
	int L;//线段的长度
	cin>>L;
	while(L%2!=0){
		cout<<"重新输入线段的长度\n";
		cin>>L;
	}
	
	int t;//记录t秒后小球的位置 
	cin>>t;
	for(int i=0;i<n;i++){
		cin>>ball[i].locate;
		while(ball[i].locate%2!=0){
			cout<<"重新输入该小球的位置\n";
			cin>>ball[i].locate; 
		}
		ball[i].state=1;//刚开始都默认小球向右走 
	}
	
	
	
	for(int i=0;i<n;i++){
		if(ball[i].locate==L){
			ball[i].state=0;//判断刚开始 是否有小球 
		}
		if(ball[i].locate==0){
			ball[i].state=1;
		}
	}
	
	//时间的增长中的判断 
	for(int i=0;i<t;i++){
		//判断是否有小球之间的相撞，如果有，则将小球之间的状态进行转换 
		for(int j=0;j<n;j++){
			for(int s=j+1;s<n;s++){
				if(ball[j].locate==ball[s].locate){
					int temp;
					temp=ball[j].state;
					ball[j].state=ball[s].state;
					ball[s].state=temp;
				}
			}
		}//for
		 
		//判断是否有小球撞墙，如果有小球撞墙，则将小球的状态→原来的1转换为0后退
		//是否有小球撞到后面的墙，有，则将0转换为1 
		for(int j=0;j<n;j++){
			if(ball[j].locate==L){
				if(ball[j].state==1){
				ball[j].state=0;
			}
			}
			if(ball[j].locate==0){
			ball[j].state=1;
		}
		}
		
	//给小球下一秒找位置，如果是后退的小球，小球位置--如果是前进的小球，小球位置++ 
		for(int j=0;j<n;j++){
			if(ball[j].state==0){
				ball[j].locate--;
			}
			if(ball[j].state==1){
				ball[j].locate++;
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<ball[i].locate<<" "; 
	}
	cout<<endl;
	return 0;
} 
