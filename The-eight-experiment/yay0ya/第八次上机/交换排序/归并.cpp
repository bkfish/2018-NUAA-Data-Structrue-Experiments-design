#include <iostream>
using namespace std;
#include <stdio.h>
 
void Merge(int sourceArr[],int tempArr[],int startIndex,int midIndex,int endIndex)
{
    int i = startIndex,j=midIndex+1,k=startIndex;
    while(i!=midIndex+1&&j!=endIndex+1)
    {
        if(sourceArr[i]>sourceArr[j])
            tempArr[k++]=sourceArr[j++];
        else
            tempArr[k++]=sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++]=sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++]=sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i]=tempArr[i];
}
 
//内部使用递归
void MergeSort(int sourceArr[],int tempArr[],int startIndex,int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;//避免溢出int
        MergeSort(sourceArr,tempArr,startIndex,midIndex);
        MergeSort(sourceArr,tempArr,midIndex+1,endIndex);
        Merge(sourceArr,tempArr,startIndex,midIndex,endIndex);
    }
}
 
int main(int argc, char * argv[])
{
   	int n,*p,*q,*temp;
   	cin>>n;
   	p=new int [n];
   	q=new int [n];
   	temp=p;
   	for(int i=0;i<n;i++){
   		cin>>*temp;
   		temp++;
	   } 
    MergeSort(p,q,0,n-1);
    temp=p;
    for(int i=0; i<n; i++)
     {
		cout<<*temp<<" ";
    	temp++;
    }
    cout<<endl;
    return 0;
}
