#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
#include<iostream>
#include<cstdio>
using namespace std;
typedef struct Product //建立一个单向链表存储所有商铺信息（至少30个），以编号为序，编号从1开始递增，从文件中读取数据，并能将数据存储在文件。商铺信息结点的数据结构自行设计。
{
    string pdtName;
    double pdtprice;
    int salesVolume;//头结点存商品数目
    struct Product *next;
}Product;


#endif // PRODUCT_H_INCLUDED
