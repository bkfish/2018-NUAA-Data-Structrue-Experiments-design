#include<stdio.h>
#include<stdlib.h>

int mem[30001];
//mem[i]的值为i的朋友，组成一个环形链表 

void join(int x[],int a,int b)
{
	int i = a;
	
	while(x[i] && x[i] != a)
	{
		i = x[i];
	}
	
	int j = b;
	
	while(x[j] && x[j] != b)
	{
		j = x[j];
	}
	//找到a和b在环形链表中的前一个 
	
	//printf("%d\n",i);
	//printf("%d\n",j);
	
	x[i] = b;
	x[j] = a;
	//合并环形链表 
	
	return; 
}

int main()
{
	int n,m;
	
	scanf("%d %d",&n,&m);
	
	while(m--)
	{
		int num,a,b;
		
		scanf("%d",&num);
		
		if(num)
		//防止num为0 
		{
			scanf("%d",&a);
		}
		else
		{
			continue;
		}
		
		for(int j = 0;j < num - 1;j++)
		{
			b = a;
			
			scanf("%d",&a);
			join(mem,a,b);
		}
	}
	
	int max = 0x80000000;
	for(int i = 1;i <= n;i++)
	{
		int num = 1;
		//自己算一个 
		
		int j = i;
		
		while(mem[j] && mem[j] != i)
		{
			j = mem[j];
			num++;
		}
		//获得朋友圈数量 
		
		if(num > max)
		{
			max = num;
		}
	}
	
	printf("%d", max);
	
	return 0;
}

