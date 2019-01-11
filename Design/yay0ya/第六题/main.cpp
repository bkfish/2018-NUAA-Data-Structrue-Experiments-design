
#include"RadixSort.h"
#include<time.h>
int main() {
	clock_t start_time=clock();
	{
		insertsortRT();
	}
	clock_t  end_time=clock();
	cout<<"直接插入顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间
	start_time=clock();
	{
		insertsortLT();
	}
	end_time=clock();
	cout<<"直接插入逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	start_time=clock();
	{
		ShellSortRT();
	}
	end_time=clock();
	cout<<"希尔插入顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	start_time=clock();
	{
		ShellSortLT();
	}
	end_time=clock();
	cout<<"希尔插入逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	
		start_time=clock();
	{
		BubbleSortRT();
	}
	end_time=clock();
	cout<<"冒泡排序顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
		start_time=clock();
	{
		BubbleSortLT();
	}
	end_time=clock();
	cout<<"冒泡排序逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
		start_time=clock();
	{
		QuickSortRT();
	}
	end_time=clock();
	cout<<"快速排序顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
			start_time=clock();
	{
		QuickSortLT();
	}
	end_time=clock();
	cout<<"快速排序逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
		
		start_time=clock();
	{
		SelecSortRT();
	}
	end_time=clock();
	cout<<"选择排序顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
			start_time=clock();
	{
		SelecSortLT();
	}
	end_time=clock();
	cout<<"选择排序逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
			start_time=clock();
	{
		MergeSortRT();
	}
	end_time=clock();
	cout<<"归并排序顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	start_time=clock();
	{
		MergeSortLT();
	}
	end_time=clock();
	cout<<"归并排序逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	
	start_time=clock();
	{
		HEAPSORT();
	}
	end_time=clock();
	cout<<"堆排序逆序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	
	start_time=clock();
	{
		RadixSort();
	}
	end_time=clock();
	cout<<"基数排序顺序时间是:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间  
	
	return 0;
}
