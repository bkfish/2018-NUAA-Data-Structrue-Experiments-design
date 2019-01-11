#include"SelectSort.h" 
void MergeLT(int sourceArr[],int tempArr[],int startIndex,int midIndex,int endIndex)
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
void MSLT(int sourceArr[],int tempArr[],int startIndex,int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;//避免溢出int
        MSLT(sourceArr,tempArr,startIndex,midIndex);
        MSLT(sourceArr,tempArr,midIndex+1,endIndex);
        MergeLT(sourceArr,tempArr,startIndex,midIndex,endIndex);
    }
}
 
void MergeSortLT()
{
   	int n=20001;
  	int L1[20001]={};
	char name[10]="6.txt";
	int i=0,j;
	readfile(L1,name);
	int L2[n]={};
    MSLT(L1,L2,1,n-1);
    	fstream file;
	file.open("62.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L1[i]<<" ";
	}
	file.close();
}
 
void MergeRT(int sourceArr[],int tempArr[],int startIndex,int midIndex,int endIndex)
{
    int i = startIndex,j=midIndex+1,k=startIndex;
    while(i!=midIndex+1&&j!=endIndex+1)
    {
        if(sourceArr[i]<sourceArr[j])
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
void MSRT(int sourceArr[],int tempArr[],int startIndex,int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;//避免溢出int
        MSRT(sourceArr,tempArr,startIndex,midIndex);
        MSRT(sourceArr,tempArr,midIndex+1,endIndex);
        MergeRT(sourceArr,tempArr,startIndex,midIndex,endIndex);
    }
}
 
void MergeSortRT()
{
   	int n=20001;
  	int L1[20001]={};
	char name[10]="6.txt";
	int i=0,j;
	readfile(L1,name);
	int L2[n]={};
    MSRT(L1,L2,1,n-1);
    	fstream file;
	file.open("63.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L1[i]<<" ";
	}
	file.close();
}
