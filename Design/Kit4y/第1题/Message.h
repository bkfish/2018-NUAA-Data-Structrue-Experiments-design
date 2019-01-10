#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"Store.h"
using namespace std;
typedef struct SortMessage //建立一个双向循环链表，结点信息是包含该商品的所有商铺编号、商铺名、信誉度、商品名称、价格、销量，以信誉度从高至低，并按销量排序，并逐一显示。
{
    int id;//存放拥有该商品的商铺的下标
    string StoreName;
    string pdtName;
    double pdtPrice;
    int salesVolume;
    struct SortMessage *next;
    struct SortMessage *last;
}SortMessage;
bool CreateSort(Store *&S,string pdtName,SortMessage *&SortM);
bool ShowMessage(SortMessage *&SortM);

#endif // MESSAGE_H_INCLUDED
