#include<iostream>
using namespace std;
#include<string.h>
#include<stdlib.h>
#include<fstream>
typedef struct goods{
	string name;
	int sold;
	int price;
}goods;
typedef struct goodlink{
	goods *data; 
	int numbers;//指代商品的数量  
}goodlink;//物品的链
 
