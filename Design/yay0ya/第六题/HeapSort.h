#include"MergeSort.h" 

void HEAPSORT(){
	void HeapSort(int H[],int n);
	int n=20001;
  	int L1[20001]={};
	char name[10]="7.txt";
	int i=0,j;
	readfile(L1,name);
	HeapSort(L1,n);
		fstream file;
	file.open("72.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L1[i]<<" ";
	}
	file.close();
}
void HeapAdjust(int H[],int s,int m){
	int rc=H[s];//仅在以s为堆顶的这个子树下面，将叶结点根节点进行交换，形成一个顶堆 
	for(int j=2*s;j<=m;j*=2){//2*s,得到以s双亲的左边叶结点 
		if(j<m&&LT(H[j],H[j+1])) ++j;//LT比较左右孩子的大小， 
		if(!LT(rc,H[j])) break;//比较双亲和两个孩子中最大的那个孩子的数值。（根据LT的定义表示形成大顶堆或者小顶堆 
		H[s]=H[j]; s=j;//交换父结点与子节点的值 
	}
	H[s]=rc;
}
void HeapSort(int H[],int n){
	//对顺序表进行堆排序
	for(int i=n/2;i>0;i--)//H.length/2 得到最后一个内节点；i--不断向前移动一个结点 
		HeapAdjust(H,i,n);//对不符合堆排序的值，进行排序 
	for(int i=n;i>1;--i){// 
		int temp;
		temp=H[1];
		H[1]=H[i];
		H[i]=temp;//将堆顶记录和当前未经排序的子序列Hr中最后一个记录进行交换 
	
		HeapAdjust(H,1,i-1);
	} 
}//HeapSort 
