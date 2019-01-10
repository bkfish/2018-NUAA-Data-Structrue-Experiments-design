#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<time.h> 
#define N 40000

clock_t begin,end;
//用于计算排序函数消耗的时间 
char fileName[10][7]={"1.txt","2.txt","3.txt","4.txt","5.txt",
					  "6.txt","7.txt","8.txt","9.txt","10.txt"};
//样本名数组
int Data[N];
int reData[N];
//数据数组 

void insertSort(int a[],int n)
//插入排序 
//a为待排序数组
//n为数组长度 
{
	for(int i = 1;i < n;i++)
	{
		int j;
		for(j = i - 1;j >= 0;j--)
		//找到插入的位置 
		{
			if(a[j] < a[i])
				break;
		}
		
		if(j != i - 1)
		//如果不在最后面 
		{
			int temp = a[i];
			
			int k;
			for(k = i - 1;k > j;k--)
			//将插入位置及后面的元素向后移一位 
			{
				a[k + 1]=a[k];
			}
			
			a[k + 1]=temp;
			//插入元素 
		}
	}
	
	return;
}

void shellSort(int a[],int n)
//希尔排序 
//a为待排序数组
//n为数组长度
{
	for(int gap = n / 2;gap > 0;gap /= 2)
	//设置步长,每次减半 
	{
		for(int i = 0;i < gap;i++)
		//对每一组使用插入排序 
		{
			for(int j = i + gap;j < n;j += gap)
			{
				if(a[j - gap] > a[j])
				{
					int temp = a[j];
					int k = j - gap;
					
					while(k >= 0 && a[k] > temp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					
					a[k + gap] = temp;
				}
			}
		}
	}
	
	return;
}

void maopaoSort(int a[],int n)
//冒泡排序 
//a为待排序数组
//n为数组长度
{
	for(int i = 0;i < n;i++)
	//每次循环找出一个最值放在末尾 
	{
		for(int j = n - i - 1;j < n - 1;j++)
		{
			if(a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	
	return;
}

void quickSort(int a[],int l,int r)
//快速排序
//a为待排序数组
//n为数组长度
{
    if(l < r)
    {
    	return;
    }
    
	int i,j,x;

    i = l;
    j = r;
    x = a[i];
    //哨兵 
        
    while(i < j)
    {
        while(i < j && a[j] > x)
        //找第一个小于x的数
        {
        	j--;
		}
			
        if(i < j)
		{
			a[i] = a[j];
			a[j] = x; 
			i++;
		}
			
        while(i < j && a[i] < x)
        //找第一个大于x的数
        {
            i++;
		}
			
        if(i < j)
		{
			a[j] = a[i];
			a[i] = x;
			j--;
		}
    }
        
    a[i] = x;
        
    quickSort(a,l,i - 1);
    quickSort(a,i + 1,r);
    
    return;
}

void selectSort(int a[],int n)
//选择排序
//a为待排序数组
//n为数组长度
{
	int min;
	//无序区中最小元素位置

	for(int i = 0; i<n; i++)
	//逐渐增加有序区 
	{
		min = i;

		for(int j = i + 1;j < n;j++)
		//找出无序区的最小元素
		{
			if(a[j] < a[min])
			{
				min = j;
			}
		}
		if(min != i)
		//交换保证有序区元素是有序的
		{
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
	
	return;
}

void heapDown(int a[],int start,int end)
//堆排序下沉操作 
//a为待排序数组
//start为起始位置
//end为截至范围
{
    int l = 2 * start + 1;
	//左孩子的index 
    int r = l + 1;
    //右孩子的index 
    int temp = a[start];
    
    while(1)
    {
        if(l < end && a[l] < a[l + 1])
        //选择较大者
        {
        	l++;
        	if(temp >= a[r])
        	//调整结束
        	{
        		break;
			} 
			else
			//交换值
        	{
            	a[start] = a[r];
            	a[r] = temp;
        	}
        	
        	start = r;
        	r = 2 * r + 1;
        	
        	if(r > end)
        	{
        		break;
			}
		}
		else
		{
			if(temp >= a[l])
        	//调整结束
        	{
        		break;
			} 
			else
			//交换值
        	{
            	a[start] = a[l];
            	a[l] = temp;
        	}
        	
        	start = l;
        	l = 2 * l + 1;
        	
        	if(l > end)
        	{
        		break;
			}
		}
    }
    
    return;
}

void heapSort(int a[],int n)
//堆排序
//a为待排序数组
//n为数组长度
{
	for(int i = n / 2 - 1;i >= 0; i--)
    //逐次遍历得到一个最大二叉堆
    {
    	heapDown(a,i,n - 1);
	}

    for(int i = n - 1;i > 0;i--)
    //从最后一个元素开始对序列进行调整
    {
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		//交换使a[i]为最大
		
        heapDown(a, 0, i-1);
        //恢复最大堆
    }
    
    return; 
}

void merge(int a[],int start,int mid,int end)
//合并有序数组
//a为数组指针
//start到mid和mid到end为两个待排序数组 
{
    int temp[end - start + 1];
	//存放合并后的元素 
    int i = start;
	//第1个有序区的索引
    int j = mid + 1;
	//第2个有序区的索引
    int k = 0;
	//临时区域的索引

    while(i <= mid && j <= end)
    //合并数组 
    {
		if (a[i] <= a[j])
		{
			temp[k++] = a[i++];
		} 
		else
		{
			temp[k++] = a[j++];
		}
    }

    while(i <= mid)
    {
    	temp[k++] = a[i++];
	}

    while(j <= end)
    {
    	temp[k++] = a[j++];
	}
	//将剩余的数组元素放入temp 

	for(i = 0;i < k;i++)
	//将排序后的元素整合到数组a
	{
		a[start + i] = temp[i];
	}
	
	return;
}

void mergeSort(int a[],int start,int end)
//归并排序
//a为待排序的数组
//start和end为数组的起始地址和结束地址
{
    int mid;
    
    if(start >= end)
    {
    	return;
	}
    
	mid = (start + end) / 2;
    mergeSort(a,start,mid);
    mergeSort(a,mid + 1,end);

    merge(a,start,mid,end);
    
    return;
}

void countSort(int a[],int n,int exp)
//对数组按照某个位进行桶排序
//a为待排序数组
//n为数组长度
//exp为指数 
{
    int temp[n];
	//存储排序完元素的数组
	int buckets[10] = {0};

    for(int i = 0; i < n; i++)
    //桶排序
	{
		buckets[(a[i] / exp) % 10]++;
	}

    for(int i = 1;i < 10;i++)
    //更改buckets[i]为其在temp中的位置
    {
    	buckets[i] += buckets[i - 1];
	}

    for(int i = n - 1;i >= 0;i--)
    {
        temp[buckets[(a[i] / exp) % 10] - 1] = a[i];
        buckets[(a[i] / exp) % 10]--;
    }

    for(int i = 0;i < n;i++)
    {
    	a[i] = temp[i];
	}
        
    return;
}

void radixSort(int a[], int n)
//基数排序
//a为待排序数组
//n为数组长度
{
    int max;
	// 数组a中的最大值
	
	max = a[0];
    for(int i = 1;i < n;i++)
    {
    	if(a[i] > max)
    	{
    		max = a[i];
		}
	}

	// 从个位开始，对数组a按"指数"进行排序
    for(int i = 1;max / i > 0;i *= 10)
    {
    	countSort(a,n,i);
	}
	
	return;
}

void setData()
//产生10个样本每个样本有20000个随机整数
//并使前后两个样本分别为正序和逆序 
//使用二进制存储 
{
	FILE * out;
 
	for(int i = 0;i < 5;i++)
	{
		srand(time(0));
		for(int j = 0;j < N;j++)
		{
			Data[j] = rand() % 100000;
			reData[N - j - 1] = Data[j];
		}
		
		out = fopen(fileName[i * 2],"wb");
		
		if(!out)
		{
			printf("Error!!!fopen(%s,\"wb\");\n",fileName[i * 2]);
			system("pause");
			exit(1);
		}
		
		fwrite(Data,sizeof(int),N,out);
		fclose(out);
		
		out = fopen(fileName[i * 2 + 1],"wb");
		
		if(!out)
		{
			printf("Error!!!fopen(%s,\"wb\");\n",fileName[i * 2 + 1]);
			system("pause");
			exit(1);
		}
		
		fwrite(reData,sizeof(int),N,out);
		fclose(out);
	}
	
	return;
}

void getData(char name[],int a[])
//使用文件中的数据赋值数组a 
{
	FILE * in;
	
	in = fopen(name,"rb");
	
	if(!in)
    {
       	printf("Error!!!fopen(%s,\"rb\");\n",name);
		system("pause");
		exit(1);
    }
    
    fread(a,sizeof(int),N,in);
    
  	fclose(in);
  	
  	return;
}

int main()
{
	double Time;
	
	setData();
	
	for(int i = 0;i < 10;i++)
	{
		printf("the time of sort %s\n",fileName[i]);
		
		getData(fileName[i],Data);
		begin = clock();
		insertSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("1.insertSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		shellSort(Data,N); 
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("2.shellSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		maopaoSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("3.maopaoSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();
		quickSort(Data,0,N - 1);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("4.quickSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		selectSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("5.selectSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();
		heapSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("6.heapSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();  
		mergeSort(Data,0,N - 1);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("7.mergeSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock(); 
		radixSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("8.radixSort:%lf\n",Time);
	
		printf("-------------------------------------------\n\n");
	}
	
	return 0;
}
