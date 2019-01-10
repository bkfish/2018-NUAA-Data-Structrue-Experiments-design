/*
实现交换、选择、归并等简单排序算法；
*/
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

clock_t start,finish;	// 开始时间，结束时间 
double totalTime;		// 总的时间 

void timeStart() {
	cout<<"\n程序开始\n";
	start = clock();
}

void timeFinish() {
	finish = clock();
   	totalTime = (double)(finish-start)/CLOCKS_PER_SEC;
   	cout<<"\n程序结束，运行时间为"<<totalTime<<"秒！"<<endl;
}

// 重置测试数组
void Reset(int *testNum, int *num, int n) {
	cout<<"\n重置\n"; 
	for (int i=0; i<n; i++) {
		testNum[i] = num[i];
		//cout<<testNum[i]<<" ";
	}
	//cout<<endl;
} 

// 遍历数组
void Traverse(int *num, int n) {
	cout<<"\n遍历数组：\n"; 
	for (int i=0; i<n; i++) {
		cout<<num[i]<<" ";
	}
	cout<<endl;
}

// 冒泡排序
void BubbleSort(int *num, int n) {
	for (int i=0; i<n; i++) {
		bool allSort = true;
		for (int j=1; j<n-i; j++) {
			if (num[j] < num[j-1]) {
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
void SelectSort(int *num, int n) {
	for (int i=0; i<n; i++) {
		int min = num[i], pos;
		for (int j=i+1; j<n; j++) {
			if (num[j] < min) {
				min = num[j];
				pos = j;
			}
		}
		num[pos] = num[i];
		num[i] = min;
	}
} 

// 归并排序
void MergerSort(int *num, int n) {
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
	while (i<mid && j<n) {
		if (num[i] <= num[j]) {
			temp[k] = num[i];
			i++;
		} else {
			temp[k] = num[j];
			j++;
		}
		k++;
	}
	// i指针未到中间 
	while (i<mid) {
		temp[k] = num[i];
		k++;
		i++;
	}
	// j指针未到结尾 
	while (j<n) {
		temp[k] = num[j];
		k++;
		j++;
	}
	
	// 将排序好的temp数组赋给num 
	for (int i=0; i<n; i++) num[i] = temp[i]; 
	free(temp);
}

// 快速排序
void QuickSort(int *num, int n) {
	// 递归终止条件 
	if (n <= 1) return;
	
	int i = 0, j = n-1;
	int temp = num[i];	// 将i位置的数先存起来，i位置现在相当于“空” 
	while (i<j) {
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
void HeapAdjust(int *num, int n, int pos) {
	int lchild = 2*pos+1, rchild = 2*pos+2;
	int maxPos;
	while (pos<n && lchild<n) {
		if (num[lchild] >= num[rchild]) maxPos = lchild;
		else if (rchild < n) maxPos = rchild;
		
		if (num[pos] < num[maxPos]) {
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
void HeapSort(int *num, int n) { 
	for (int i=n-1; i>=0; i--) {
		HeapAdjust(num, n, i);
	}

	for (int i=n-1; i>0; i--) {
		int temp = num[0];
		num[0] = num[i];
		num[i] = temp;
		HeapAdjust(num, i, 0);
	}
}

int main() {
	int count = 0, limit = 0;
	cout<<"请输入想排序的随机数的个数:\n";
	cin>>count;
	cout<<"请输入这些数的上限(小于等于某个数):\n"; 
	cin>>limit;
	
	cout<<"生成的无序随机数数组如下：\n";
	int *num = (int*)malloc(sizeof(int) * count);
	int *testNum = (int*)malloc(sizeof(int) * count);
	srand(time(0));
	for (int i=0; i<count; i++) {
		num[i] = rand()%limit;
		testNum[i] = num[i];
		cout<<num[i]<<" ";
	}
	cout<<endl;
	
	
	cout<<"\n============================冒泡排序=================================\n";
	timeStart();
	BubbleSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// 重置测试数组
	Reset(testNum, num, count);
	cout<<"\n============================选择排序=================================\n";
	timeStart();
	SelectSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// 重置测试数组
	Reset(testNum, num, count);
	cout<<"\n============================归并排序=================================\n";
	timeStart(); 
	MergerSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// 重置测试数组
	Reset(testNum, num, count);
	cout<<"\n============================快速排序=================================\n";
	timeStart(); 
	QuickSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	// 重置测试数组
	Reset(testNum, num, count);
//	int Num[10] = {2, 8, 3, 3, 5, 1, 9, 8, 0, 6};
//	count = 10;
//	Traverse(Num, count);
	cout<<"\n=============================堆排序=================================\n";
	timeStart(); 
	HeapSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	free(num);
	free(testNum);
}
