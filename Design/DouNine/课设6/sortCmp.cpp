/*
[问题描述]
利用随机函数产生10个样本，每个样本有20000个随机整数（并使第一个样本是正序，第二个样本是逆序），
利用直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序8种排序方法
进行排序（结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。
 [基本要求]
（1） 原始数据存在文件中，用相同样本对不同算法进行测试；
（2） 屏幕显示每种排序算法对不同样本所花的时间；
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>

using namespace std;


// 全局变量 
FILE *fp;
char fileName[10];

clock_t start,finish;	// 开始时间，结束时间 
double totalTime;		// 总的时间 


// 打开文件 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    // else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    // else printf("file has been closed\n");
    return;
} 

// 开始时间 
void timeStart() 
{
	cout<<"程序开始\n";
	start = clock();
}

// 结束时间 
void timeFinish() 
{
	finish = clock();
   	totalTime = (double)(finish-start)/CLOCKS_PER_SEC;
   	cout<<"程序结束，运行时间为"<<totalTime<<"秒！\n\n";
}

// 重置测试数组
void Reset(int *testNum, int *num, int n) 
{
	//cout<<"\n重置\n"; 
	for (int i=0; i<n; i++) 
	{
		testNum[i] = num[i];
		//cout<<testNum[i]<<" ";
	}
	//cout<<endl;
} 

// 遍历数组
void Traverse(int *num, int n) 
{
	cout<<"\n遍历数组：\n"; 
	for (int i=0; i<n; i++) 
	{
		cout<<num[i]<<" ";
	}
	cout<<endl;
}

// 冒泡排序
void BubbleSort(int *num, int n) 
{
	for (int i=0; i<n; i++) 
	{
		bool allSort = true;
		for (int j=1; j<n-i; j++) 
		{
			if (num[j] < num[j-1]) 
			{
				int temp = num[j];
				num[j] = num[j-1];
				num[j-1] = temp;
				allSort = false;
			}
		}
		if (allSort) break;
	}
}

// 选择排序
void SelectSort(int *num, int n) 
{
	for (int i=0; i<n; i++) 
	{
		int min = num[i], pos;
		for (int j=i+1; j<n; j++) 
		{
			if (num[j] < min) 
			{
				min = num[j];
				pos = j;
			}
		}
		num[pos] = num[i];
		num[i] = min;
	}
} 

// 插入排序 
void InsertSort(int *num, int n, int start, int grep) 
{
	// 对第i个数往前面已排好序的数组插入 
	for (int i=start; i<n; i+=grep) 
	{
		// 当j位置数小于j-1位置数时，交换；若大于则不交换 
		for (int j=i; j>=0+grep && num[j]<num[j-grep]; j-=grep) 
		{
			int temp = num[j];
			num[j] = num[j-grep];
			num[j-grep] = temp;
		}
	}
}

// 归并排序
void MergerSort(int *num, int n) 
{
	// 递归终止条件 
	if (n == 1) return;
	
	int mid = n/2;
	// 对前半部分归并排序 
	MergerSort(num, mid);
	// 对后半部分归并排序 
	MergerSort(num+mid, n-mid);
	
	// 将排好序两部分合并到temp数组 
	int *temp = (int*)malloc(sizeof(int) * n);
	int i = 0, j = mid, k = 0;
	while (i<mid && j<n) 
	{
		if (num[i] <= num[j]) 
		{
			temp[k] = num[i];
			i++;
		} else 
		{
			temp[k] = num[j];
			j++;
		}
		k++;
	}
	// i指针未到中间 
	while (i<mid) 
	{
		temp[k] = num[i];
		k++;
		i++;
	}
	// j指针未到结尾 
	while (j<n) 
	{
		temp[k] = num[j];
		k++;
		j++;
	}
	
	// 将排序好的temp数组赋给num 
	for (int i=0; i<n; i++) num[i] = temp[i]; 
	free(temp);
}

// 希尔排序 
void ShellSort(int *num, int n) 
{
	// 对每隔5个数的序列排序，一共有5个这样序列 ，起始点分别为0,1,2,3,4 
	for (int i=0; i<5; i++) InsertSort(num, n, i, 5);
	// 对每隔3个数的序列 
	for (int i=0; i<3; i++) InsertSort(num, n, i, 3);
	InsertSort(num, n, 0, 1);
} 

// 快速排序
void QuickSort(int *num, int n) 
{
	// 递归终止条件 
	if (n <= 1) return;
	
	int i = 0, j = n-1;
	int temp = num[i];	// 将i位置的数先存起来，i位置现在相当于“空” 
	while (i<j) 
	{
		while (num[j] >= temp && j>i) j--;
		// 此处直接将j位置不合格的数放在i位置就可以了，因为i位置本来就是“空的” 
		num[i] = num[j]; 
		while (num[i] <= temp && i<j) i++;
		num[j] = num[i];
	}
	num[i] = temp;
	
	QuickSort(num, i);
	QuickSort(num+i+1, n-i-1);	// 此处不用再把pos位置的数传进去排序了！！ 
} 

// 堆排序中的筛选算法
void HeapAdjust(int *num, int n, int pos) 
{
	int lchild = 2*pos+1, rchild = 2*pos+2;	// 左孩子和右孩子的位置 
	int maxPos;
	while (pos<n && lchild<n) 
	{
		// 找到孩子中最大那个孩子 
		if (num[lchild] >= num[rchild]) maxPos = lchild;
		else if (rchild < n) maxPos = rchild;
		
		// 如果筛选点小于孩子中最大的，则筛下去继续操作 
		if (num[pos] < num[maxPos]) 
		{
			int temp = num[maxPos];
			num[maxPos] = num[pos];
			num[pos] = temp;
			
			pos = maxPos;
			lchild = 2*pos+1, rchild = 2*pos+2;
		}
		else break;
	}
}

// 堆排序（完全二叉树排序）
void HeapSort(int *num, int n) 
{ 
	// 从底往顶逐个筛选，建成小顶堆 
	for (int i=n-1; i>=0; i--) 
	{
		HeapAdjust(num, n, i);
	}

	// 交换第一个和最后一个，再对第一个筛选 
	for (int i=n-1; i>0; i--) 
	{
		int temp = num[0];
		num[0] = num[i];
		num[i] = temp;
		HeapAdjust(num, i, 0);
	}
}

// 基数排序
void RadixSort(int *num, int n, int limit) 
{
	queue<int> radix[10];
	
	// i是余数 
	for (int i=1; i<limit; i*=10) 
	{
		for (int j=0; j<n; j++) 
		{
			radix[num[j]/i%10].push(num[j]);
		}
		int j=0;
		for (int k=0; k<10; k++) 
		{
			while (!radix[k].empty()) 
			{
				num[j] = radix[k].front();
				radix[k].pop();
				j++;
			}
		}
	}
}


int main() 
{
	int count = 20000, limit = 0;
	int *num = (int*)malloc(sizeof(int) * count);
	int *testNum = (int*)malloc(sizeof(int) * count);
	
	for (int i=1; i<=10; i++) 
	{
		printf("\n*******************第%d份数据*******************\n", i);
		sprintf(fileName, "data%d.txt", i);
		fileOpen("r");
		fscanf(fp, "%d%d", &count, &limit);
		for (int j=0; j<count; j++) 
		{
			fscanf(fp, "%d", &num[j]);
			testNum[j] = num[j];
		}
		
		cout<<"===冒泡排序===\n";
		timeStart();
		BubbleSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===选择排序===\n";
		timeStart();
		SelectSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===插入排序===\n";
		timeStart();
		InsertSort(testNum, count, 0, 1);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===归并排序===\n";
		timeStart(); 
		MergerSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===希尔排序===\n";
		timeStart(); 
		ShellSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===快速排序===\n";
		timeStart(); 
		QuickSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===堆排序===\n";
		timeStart(); 
		HeapSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// 重置测试数组
		cout<<"===基数排序===\n";
		timeStart(); 
		RadixSort(testNum, count, limit);
		timeFinish();
		//Traverse(testNum, count);
		
		fileClose();
	}
	
	free(num);
	free(testNum);
}
