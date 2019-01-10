/*1、购物网站信息管理（必做）（线性表）
[问题描述]
设计一个程序，对商铺信息管理，商铺信息包括：商铺编号，商铺名，信誉度（0-5），（商品名称1，价格1，销量1），（商品名称2，价格2，销量2），（商品名称3，价格3，销量3）…。
商品名称包括(毛巾，牙刷，牙膏，肥皂，洗发水，沐浴露等6种以上商品)，每个商铺具有其中事先确定若干商品及价格，由文件输入，销量初始为0。
[基本要求]
（1）建立一个单向链表存储所有商铺信息（至少30个），以编号为序，编号从1开始递增，从文件中读取数据，并能将数据存储在文件。商铺信息结点的数据结构自行设计。
（2）可以增、删商铺。增加商铺，编号自动加一，插入链表尾部；删除商铺，以编号为准，并修改后续结点的编号，保持编号连续性。可增、删商品。
（3）查询某一种商品名称，建立一个双向循环链表，结点信息是包含该商品的所有商铺编号、商铺名、信誉度、商品名称、价格、销量，以信誉度从高至低，并按销量排序，并逐一显示。
（4）购买某一商铺的商品，修改单向链表中商品的信息的销量。
（5）建立一个顺序结构，按商品名Hash分配地址，存储当前每种商品总销量并输出。 
（6）任何的商铺信息变化，实现文件存储。*/
#include"Product.h"//商铺信息
#include"Store.h" //函数声明
#include"Message.h"//商品
#include"Store.cpp"//所有函数实现
#include"Message.cpp"//关于信息的简单函数声明
#define OK 1
#define ERROR 0
int main()
{
    Store *S;
    CreateStore(S);
    int count = 0;
    cout<<"233"<<endl;
    while(1)
    {
        cout << "请输入你要进行的操作！" << endl;
        cout << "1：增加商铺！" << endl;
        cout << "2：删去商铺！" << endl;
        cout << "3：增加商铺的商品！" << endl;
        cout << "4：删去商铺的商品！" << endl;
        cout << "5：改动商铺的商品信息！" << endl;
        cout << "6：购买商品！" << endl;
        cout << "7：查看商铺信息！" <<endl;
        cout << "8：输入商品名称商铺按销量高到低排列！" << endl;
        cout << "9：从文件里读出信息！" << endl;
        cout << "10：查看所有商铺！" << endl;
        cout << "11：写入文件！" <<endl;
        cout << "12：退出！" << endl;
        scanf("%d",&count);
        if(count == 1)
        {
            InsertStore(S);
        }
        if(count == 2)
        {
            int Id;
            cout << "请输入要删除的的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"是否确定：（Y/N）" << endl;
            cin >> ch;
            if(ch == 'Y')
                DeleteStore(S,Id);
        }
        if(count == 3)
        {
            int Id;
            cout << "请输入要增加商品的的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"是否确定：（Y/N）" << endl;
            cin >> ch;
            if(ch == 'Y')
                InsertProduct(S,Id);
        }
        if(count == 4)
        {
            int Id;
            string Name;
            cout << "请输入要删去商品的的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"是否确定：（Y/N）" << endl;
            cin >> ch;
            if(ch == 'Y')
            {
                cout << "请输入要删去的商品名称：";
                cin >> Name;
                DeleteProduct(S,Id,Name);
            }
        }
        if(count == 5)
        {
            int Id;
            string Name;
            cout << "请输入要改动信息的商品所在的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"是否确定：（Y/N）" << endl;
            cin >> ch;
            if(ch == 'Y')
            {
                cout << "请输入要改动信息的商品名称：";
                cin >> Name;
                ChangeProduct(S,Id,Name);
            }
        }
        if(count == 6)
        {
            int Id;
            string Name;
            int num;
            cout << "请输入要购买的商品所在的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
            cout << "请输入要购买的商品名称：";
            cin >> Name;
            cout << "请输入要购买的商品数量：";
            cin >> num;
            Purchase(S,Id,Name,num);
        }
        if(count == 7)
        {
            int Id;
            cout << "请输入要查找的商铺编号：";
            cin >> Id;
            checkMessage(S,Id);
        }
        if(count == 8)
        {
            string name;
            cout << "请输入要查找的商品" << endl;
            cin >> name;
            SortMessage *SortM;
            CreateSort(S,name,SortM);
            ShowMessage(SortM);
        }
        if(count == 9)
        {
            readTxT(S);
        }
        if(count == 10)
        {
            TraverseStore(S);
        }
        if(count == 11)
        {
            writeTXT(S);
        }
        if(count == 12)
        {
            return OK;
        }
        cout << endl;
    }
    return OK;
}
