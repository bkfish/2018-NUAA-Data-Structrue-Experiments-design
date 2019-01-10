/**
 * 九大排序：C++
 *
 * @author Kitty
 * @date 2019/1/8
 */
/*
6、排序算法比较 （必做）（排序）
[问题描述]
利用随机函数产生10个样本，每个样本有20000个随机整数（并使第一个样本是正序，第二个样本是逆序），利用直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序8种排序方法进行排序（结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。
 [基本要求]
（1） 原始数据存在文件中，用相同样本对不同算法进行测试；
（2） 屏幕显示每种排序算法对不同样本所花的时间；*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>   
#include<time.h> 
#define N 30000
clock_t start,finish;
using namespace std;
char fileName[10][11]={"data_0.txt","data_1.txt","data_2.txt",
					   "data_3.txt","data_4.txt","data_5.txt",
					   "data_6.txt","data_7.txt","data_8.txt",
					   "data_9.txt"};
/*
 * 1、插入排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void insertSort(int *a,int n) 
{
	start=clock();
	int i,j,k;
	for(i=1;i<n;i++)
	{
		//为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
		for(j=i-1;j>=0;j--)
		{
			if(a[j]<a[i])
				break;
		}
		if(j!=i-1)
		{
			//比a[i]大的后移
			int temp=a[i];
			for(k=i-1;k>j;k--)
			a[k+1]=a[k];
			 //将a[i]放到正确位置上
			a[k+1]=temp;
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"1、插入排序：     "<<Time<<"s\n";
}
/*
 * 2、希尔排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void shell_sort(int *a, int n)
{
	start=clock();
	int i,j,gap,temp;
	// gap为步长，每次减为原来的一半。
	for(gap=n/2;gap>0;gap/=2)
	{
		// 共gap个组，对每一组都执行直接插入排序
		for(int i=0;i<gap;i++)
		{
			for(j=i+gap;j<n;j+=gap)
			{
				// 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
				if(a[j-gap]>a[j])
				{
					temp=a[j];
					int k=j-gap;
					while(k>=0&&a[k]>temp)
					{
						a[k+gap]=a[k];
						k-=gap;
					}
					a[k+gap]=temp;
				}
			}
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"2、希尔排序耗时： "<<Time<<"s\n";
}
/*
 * 3、冒泡排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void bubbleSort(int *a,int n)
{
	start=clock(); 
	int i,j,temp=0;
	for(i=0;i<n;i++)
	{
		 // 将最大的数据放在末尾
		for(j=n-i-1;j<n-1;j++)
		{
			//n-i-1可以直接用0代替，本代码更优化 
			if(a[j]>a[j+1])
			{
				// 交换a[j]和a[j+1]
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"3、冒泡排序耗时： "<<Time<<"s\n";
}
/*
 * 4、快速排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     l -- 数组的左边界(例如，从起始位置开始排序，则l=0)
 *     r -- 数组的右边界(例如，排序截至到数组末尾，则r=a.length-1)
 */
void quickSort(int *a, int l, int r)
{
    if (l < r)
    {
		int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
				j--; // 从右向左找第一个小于x的数
            if(i < j)
				{
					a[i]=a[j];
					a[j]=x; 
					i++;
				}
            while(i < j && a[i] < x)
				i++; // 从左向右找第一个大于x的数
            if(i < j)
				{
					a[j]=a[i];
					a[i]=x;
					j--;
				}
        }
        a[i] = x;
        quickSort(a, l, i-1); /* 递归调用 */
        quickSort(a, i+1, r); /* 递归调用 */
    }
}
/*
 * 5、选择排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void selectSort(int* a, int n)
{
	start=clock(); 
	int i;		// 有序区的末尾位置
	int j;		// 无序区的起始位置
	int min;	// 无序区中最小元素位置

	for(i=0; i<n; i++)
	{
		min=i;

		// 找出"a[i+1] ... a[n]"之间的最小元素，并赋值给min。
		for(j=i+1; j<n; j++)
		{
			if(a[j] < a[min])
				min=j;
		}

		// 若min!=i，则交换 a[i] 和 a[min]。
		// 交换之后，保证了a[0] ... a[i] 之间的元素是有序的。
		if(min != i)
		{
			int tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"5、选择排序耗时： "<<Time<<"s\n";
}
/* 
 * 6、堆排序 
 * 6.1、(最大)堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *     其中，N为数组下标索引值，如数组中第1个数对应的N为0。
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
void maxHeapDown(int* a, int start, int end)
{
    int c = start;			// 当前(current)节点的位置
    int l = 2*c + 1;		// 左(left)孩子的位置
    int tmp = a[c];			// 当前(current)节点的大小
    for (; l <= end; c=l,l=2*l+1)
    {
		// "l"是左孩子，"l+1"是右孩子
        if ( l < end && a[l] < a[l+1])
            l++;		// 左右两孩子中选择较大者，即m_heap[l+1]
        if (tmp >= a[l])
            break;		// 调整结束
		else			// 交换值
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}
/*
 * 6.2、堆排序(mian)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void heapSort(int* a, int n)
{
    int i,tmp;

    // 从(n/2-1) --> 0逐次遍历。遍历之后，得到的数组实际上是一个(最大)二叉堆。
    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapDown(a, i, n-1);

    // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for (i = n - 1; i > 0; i--)
    {
        // 交换a[0]和a[i]。交换后，a[i]是a[0...i]中最大的。
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		// 调整a[0...i-1]，使得a[0...i-1]仍然是一个最大堆。
		// 即，保证a[i-1]是a[0...i-1]中的最大值。
        maxHeapDown(a, 0, i-1);
    }
}

/*
 * 7、归并排序 
 * 7.1、将一个数组中的两个相邻有序区间合并成一个
 *
 * 参数说明：
 *     a -- 包含两个有序区间的数组
 *     start -- 第1个有序区间的起始地址。
 *     mid   -- 第1个有序区间的结束地址。也是第2个有序区间的起始地址。
 *     end   -- 第2个有序区间的结束地址。
 */
void merge(int* a, int start, int mid, int end)
{
    int *tmp = new int[end-start+1];	// tmp是汇总2个有序区的临时区域
    int i = start;			// 第1个有序区的索引
    int j = mid + 1;		// 第2个有序区的索引
    int k = 0;				// 临时区域的索引

    while(i <= mid && j <= end)
    {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
    }

    while(i <= mid)
        tmp[k++] = a[i++];

    while(j <= end)
        tmp[k++] = a[j++];

	// 将排序后的元素，全部都整合到数组a中。
	for (i = 0; i < k; i++)
		a[start + i] = tmp[i];

	delete[] tmp;
}
/*
 * 7.2、归并排序(main)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 数组的起始地址
 *     end -- 数组的结束地址,初始为n-1 
 */
void mergeSort(int* a, int start, int end)
{
    if(a==NULL || start >= end)
        return ;

    int mid = (end + start)/2;
    mergeSort(a, start, mid); // 递归排序a[start...mid]
    mergeSort(a, mid+1, end); // 递归排序a[mid+1...end]

	// a[start...mid] 和 a[mid...end]是两个有序空间，
	// 将它们排序成一个有序空间a[start...end]
    merge(a, start, mid, end);
}
/*
 * 8、基数排序
 */
/*
 * 8.1、获取数组a中最大值
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
*/
int getMax(int a[], int n)
{
	int i, max;

	max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}
/*
 * 8.2、对数组按照"某个位数"进行排序(桶排序)
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 *     exp -- 指数。对数组a按照该指数进行排序。
 *
 * 例如，对于数组a={50, 3, 542, 745, 2014, 154, 63, 616}；
 *    (01) 当exp=1表示按照"个位"对数组a进行排序
 *    (02) 当exp=10表示按照"十位"对数组a进行排序
 *    (03) 当exp=100表示按照"百位"对数组a进行排序
 *    ...
 */
void countSort(int *a, int n, int exp)
{
    int output[n]; 			// 存储"被排序数据"的临时数组
    int i, buckets[10] = {0};

	// 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;

	// 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

	// 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}
/*
 * 8.3、基数排序
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
 */
void radixSort(int *a, int n)
{
	start=clock(); 
    int exp;	// 指数。当对数组按各位进行排序时，exp=1；按十位进行排序时，exp=10；...
    int max = getMax(a, n);	// 数组a中的最大值

	// 从个位开始，对数组a按"指数"进行排序
    for (exp = 1; max/exp > 0; exp *= 10)
		      countSort(a, n, exp);
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"8、基数排序耗时： "<<Time<<"s\n";
}
/*
 * 9、(附加)桶排序排序
 */ 
/*
 * 9.1、获取数组a中最大值
 *
 * 参数说明：
 *     a -- 数组
 *     n -- 数组长度
*/
int getMaxforbucket(int *a, int n)
{
	int i, max;

	max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}
/*
 * 9.2、桶排序
 *
 * 参数说明：
 *     a -- 待排序数组
 *     n -- 数组a的长度
 */
void bucketSort(int* a, int n)
{
	int max=getMaxforbucket(a,n)+1;//获取最大值 
	int i, j;
    int *buckets;

    if (a==NULL || n<1 || max<1) //异常检验 
        return ;

    // 创建一个容量为max的数组buckets，并且将buckets中的所有数据都初始化为0。
    if ((buckets = new int[max])==NULL)
        return ;
    memset(buckets, 0, max*sizeof(int));

	// 1. 计数
    for(i = 0; i < n; i++) 
        buckets[a[i]]++; 

	// 2. 排序
	for (i = 0, j = 0; i < max; i++) 
		while( (buckets[i]--) >0 )
			a[j++] = i;
	delete[] buckets;
}
/*
 *产生样本 
 *二进制储存数 
 *随机函数产生10个样本每个样本有20000个随机整数?
 *并使第一个样本是正序，第二个样本是逆序
 *
 */
void PutData()
{
 
	for(int i=0;i<10;i++)
	{
		if(i==0) //正序 
		{
			FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
			for(int j=0;j<N;j++)
			{
				putw(j,out);
			}
			fclose(out);
			cout<<fileName[i]<<"整数产生成功！"<<endl;
		}
		else if(i==1) //逆序
		{
			FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
			for(int j=0;j<N;j++)
			{
				int num=N-j;
				putw(num,out);
			}
			fclose(out);
			cout<<fileName[i]<<"整数产生成功！"<<endl;
		 } 
		 else{
		 	FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
    		srand((unsigned)time(0)); //产生随机时间种子 
			for(int j=0;j<N;j++)
			{
				int ran_num=rand()%N; 
				putw(ran_num,out);
			}
			fclose(out);
			cout<<fileName[i]<<"整数产生成功！"<<endl;
			 
		 } 
	}
	cout<<"\n======================================\n"<<endl;
}
/*
 * 帮助数组从文件中读取获得数据 
 *参数说明：
 *     name -- 待读取文件名 
 *     a --  读取赋值的目标数组 
 */
void GetData(char *name,int * a)
{
	FILE *in;
	if((in=fopen(name,"rb"))==NULL)
    {
       printf("error");
       exit(0);
    }
    int j=0;
    while(!feof(in))
  	{
	a[j]=getw(in);
	j=j+1;
  	}
  	fclose(in);
  	return;
}
int main()
{
	double Time;
	int a[N+1];
	PutData();
	for(int i=0;i<10;i++)
	{
	cout<<"对文件 "<<fileName[i]<<" 内容排序时间结果为：";
	if(i==0) cout<<"(正序)"<<endl; 
	else if(i==1) cout<<"(逆序)"<<endl; 
	else cout<<endl;
	
	GetData(fileName[i],a);		//每次排序后从新拿到数据 
	insertSort(a,N); 
	
	GetData(fileName[i],a);
	shell_sort(a,N); 
	
	GetData(fileName[i],a);
	bubbleSort(a,N); 
	 
	GetData(fileName[i],a);
	start=clock();  
	quickSort(a,0,N-1);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"4、快速排序耗时： "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	selectSort(a,N); 
	
	GetData(fileName[i],a);
	start=clock();  
	heapSort(a,N);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"6、堆排序耗时：   "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	start=clock();  
	mergeSort(a,0,N-1);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"7、归并排序耗时： "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	radixSort(a,N); 
	
	GetData(fileName[i],a);
	start=clock(); 
	bucketSort(a,N); 
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//计算时间
	cout<<"9、桶排序耗时：   "<<Time<<"s\n";
	cout<<"\n======================================\n"<<endl;
	}
	system("pause");
}
