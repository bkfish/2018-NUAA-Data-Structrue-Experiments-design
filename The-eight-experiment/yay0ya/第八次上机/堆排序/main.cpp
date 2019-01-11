#include"sqlist.h"
typedef Sqlist HeapType;

int main(){
	HeapType H;
	void HeapSort(HeapType &H);
	InitList_Sq(H);
	int n;
	Sqtype *p;
	p=H.elem;
	cin>>n;
	p++;
	for(int i=0;i<n;i++){
		cin>>*p;
		p++;
	}
	H.length=n;
	HeapSort(H);
	p=H.elem;
	p++;
	for(int i=1;i<n+1;i++){
		cout<<*p<<" ";
		p++;
	}
	return 0;
}
void HeapAdjust(HeapType &H,int s,int m){
	int LT(Sqtype n,Sqtype m);
	Sqtype rc=H.elem[s];//仅在以s为堆顶的这个子树下面，将叶结点根节点进行交换，形成一个顶堆 
	for(int j=2*s;j<=m;j*=2){//2*s,得到以s双亲的左边叶结点 
		if(j<m&&LT(H.elem[j],H.elem[j+1])) ++j;//LT比较左右孩子的大小， 
		if(!LT(rc,H.elem[j])) break;//比较双亲和两个孩子中最大的那个孩子的数值。（根据LT的定义表示形成大顶堆或者小顶堆 
		H.elem[s]=H.elem[j]; s=j;//交换父结点与子节点的值 
	}
	H.elem[s]=rc;
}
void HeapSort(HeapType &H){
	//对顺序表进行堆排序
	for(int i=H.length/2;i>0;i--)//H.length/2 得到最后一个内节点；i--不断向前移动一个结点 
		HeapAdjust(H,i,H.length);//对不符合堆排序的值，进行排序 
	for(int i=H.length;i>1;--i){// 
		int temp;
		temp=H.elem[1];
		H.elem[1]=H.elem[i];
		H.elem[i]=temp;//将堆顶记录和当前未经排序的子序列Hr中最后一个记录进行交换 
	
		HeapAdjust(H,1,i-1);
	} 
}//HeapSort 
int LT(Sqtype n,Sqtype m){
	if(n>m) return 0;
	return 1;
}
