#include<iostream>
using namespace std;
#include<stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define LINKSIZE 10
typedef int SElemType;
typedef struct shop{
	int id;
	char name[50];
	SElemType goods;
}shop;

