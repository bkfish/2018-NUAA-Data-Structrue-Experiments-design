#include<iostream>
using namespace std;
void BubbleSort(int* a,int len)
{
    
    bool flag = true;//标志用于判断是否有序
    for(int i = 0;i < len;++i)//外循环
    {
        for(int j = 0;j < len-i-1;++j)//内循环，每次循环比较len-i-1次
        {
            if(a[j]>a[j+1])
            {
                int temp;
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                flag = false;
            }
        }
        if(flag)//如果有序直接跳出
        {
            break;
        }
    }
}
int main()
{
    int n,*p,*q;
    cin>>n;
    p=new int [n];
    q=p;
    for(int i=0;i<n;i++){
    	cin>>*q;
    	q++;
	}
    BubbleSort(p,n);
	for(int i=0;i<n;i++){
		cout<<*p<<" ";
		p++;
	}
	return 0;
}
