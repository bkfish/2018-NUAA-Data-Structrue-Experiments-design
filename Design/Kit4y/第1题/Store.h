#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED
#include<iostream>
#include<cstdio>
#include"Product.h"
using namespace std;
typedef struct Store
{
    int storeId;//头结点存商铺数目
    string storeName;
    int storeCredit;
    Product *pdt;
    struct Store *next;
}Store;

bool CreateStore(Store *&S);//S是Store链表的头结点
bool InsertStore(Store *&S);
bool checkMessage(Store *&S,int id);
bool DeleteStore(Store *&S,int id);
bool InsertProduct(Store *S,int id);
bool DeleteProduct(Store *&S,int id,string pdtName);
bool ChangeProduct(Store *S,int id,string pdtName);
bool Purchase(Store *S,int id,string pdtName,int num);
void readTxT(Store *&S);
void writeTXT(Store *&S);
bool TraverseStore(Store *&S);
#endif // STORE_H_INCLUDED
