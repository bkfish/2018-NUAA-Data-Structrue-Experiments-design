#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N,K,w,s,c;
int key[100001];

typedef struct Action
{
    int num;
    int time;
    int flag;
}action;
//保存借钥匙和还钥匙两个动作，flag为0表示借，flag为1表示还 

vector<action> a;
action temp;

bool cmp(action a,action b){
    if(a.time != b.time)
    //先按时间排 
	{
        return a.time < b.time;
    }
	else if(a.flag != b.flag)
	//先还再借 
	{
        return a.flag > b.flag;
    }
	else
	//编号从小到大 
	{
        return a.num < b.num;
    }
}
//用于比较的函数 

int main()
{
    cin >> N >> K;
    
    for(int i = 1;i <= N;i++)
	{
        key[i]=i;
    } 
    //初始化钥匙的位置 
    
    while(K--)
	{
        cin >> w >> s >> c;
        
        temp.num = w;
        temp.time = s;
        temp.flag = 0;
        a.push_back(temp);
        //借钥匙
        temp.num = w;
        temp.time = s + c;
        temp.flag = 1;
        a.push_back(temp); 
        //还钥匙
    } 
    
    sort(a.begin(),a.end(),cmp);
    //排序
    
    for(int i = 0;i < a.size();i++)
	{
        if(a[i].flag == 1)
        //还钥匙
		{
            for(int k = 1;k <= N;k++)
			{
                if(key[k] == 0)
				{
                    key[k] = a[i].num;
                    break;
                }
            }
        }
		else
		//借钥匙 
		{
            for(int j = 1;j <= N;j++)
			{
                if(key[j] == a[i].num)
				{
                    key[j] = 0;
                    break;
                }
            }
        }
    } 

    for(int i = 1;i <= N;i++)
	{
        cout << key[i] <<" ";
    }
    
    return 0;
}
