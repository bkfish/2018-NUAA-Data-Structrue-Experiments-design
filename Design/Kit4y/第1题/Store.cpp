#include"Store.h"
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<sstream>
#include<string>
#include<cstring>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define TRUE 1
#define FALSE 0
using namespace std;
bool CreateStore(Store *&S)//S是Store链表的头结点
{
    S = new Store;
    if(!S)
        exit(OVERFLOW);
    S -> storeId = 0;
    S -> pdt = NULL;
    S -> storeCredit = 0;
    S -> next = NULL;
    return OK;
}
bool InsertStore(Store *&S)
{
    if(!S)
        return ERROR;
    Store *newStore = new Store;
    if(!newStore)
        exit(OVERFLOW);
    newStore -> pdt = new Product;
    Product *pdt = newStore->pdt;
    pdt->next = NULL;
    pdt->salesVolume = 0;//初始化商铺的商品数目为0
    string name;
    int num = 0;
    cout << "********************** "<< endl;
    cout << "请输入建立商铺的信息！"<< endl;
    cout << "商铺名：";
    cin >> name;
    cout << "信誉度：";
    cin >> num;
    newStore->storeCredit = num;
    cout << newStore->storeName<<endl;
    newStore->storeName = name;
    newStore ->next = NULL;
    cout << "**********************"<<endl;
    S->storeId++;//商铺总数+1
    newStore->storeId = S->storeId;
    if(S->next == NULL)
        S->next = newStore;
    else
    {
        Store *now = S->next;
        while(now->storeId != S->storeId-1)
            now = now->next;
        now->next = newStore;
    }
    return OK;
}
bool DeleteStore(Store *&S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Store *now = S->next;
    Store *last = S;
    while(now->storeId != id && now != NULL )
    {
        last = now;
        now = now->next;
    }

    last->next = now->next;
    free(now->pdt);
    free(now);
    now = last->next;
    while(now != NULL)
    {
        now->storeId--;
        now = now->next;
    }
    S->storeId--;
    return OK;
}

bool checkMessage(Store *&S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = snow->pdt;
    cout << endl << "******************************" << endl;
    cout << "*该店铺信息如下：" << endl;
    cout << "*店铺号：" << snow->storeId << endl;
    cout << "*店铺名：" << snow->storeName << endl;
    cout << "*店铺信誉度：" << snow->storeCredit << endl;
    cout << "*商品信息：";
    if(pnow->next == NULL)
        cout << "无商品信息！" << endl;
    else
        cout << "该商铺有" << pnow->salesVolume << "个产品" << endl;
    cout << "******************************" << endl;
    cout<<endl;
    pnow = pnow->next;
    while(pnow != NULL)
    {
        cout << "******************************" << endl;
        cout << "商品名：" << pnow->pdtName << endl;
        cout << "商品价格：" << pnow->pdtprice << endl;
        cout << "商品销量：" << pnow->salesVolume << endl;
        cout << "******************************" <<endl<<endl;
        pnow = pnow->next;
    }
    return OK;
}

bool InsertProduct(Store *S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Product *newPdt = new Product;
    string Name;
    int num;
    cout << "**********************" << endl;
    cout << "请输入加入商品的信息！" << endl;
    cout << "商品名称：";
    cin >> Name;
    cout << "商品价格：";
    cin >> num;
    newPdt->pdtprice = num;
    newPdt->pdtName = Name;
    newPdt->salesVolume = 0;
    cout << "**********************" << endl;
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = snow->pdt;
    pnow->salesVolume++;
    while(pnow->next != NULL)
        pnow = pnow->next;
    pnow->next = newPdt;
    newPdt->next = NULL;
    return OK;
}
bool DeleteProduct(Store *&S,int id,string pdtName)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *p = snow->pdt;
    p->salesVolume--;
    Product *pnow = (snow->pdt)->next;
    Product *plast = snow->pdt;
    while(pnow != NULL && pnow->pdtName != pdtName)
    {
        plast = pnow;
        pnow = pnow->next;
    }
    if(pnow == NULL)
    {
        cout << "没有找到该商品！" << endl;
        return ERROR;
    }
    cout << "该商品信息为：" << endl;
    cout << "Name：" << pnow->pdtName << endl;
    cout << "price：" << pnow->pdtprice << endl;
    cout << "volume：" << pnow->salesVolume << endl;
    plast->next = pnow->next;
    plast = plast->next;
    delete(pnow);
    return OK;
}
bool ChangeProduct(Store *S,int id,string pdtName)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = (snow->pdt)->next;
    while(pnow != NULL && pnow->pdtName != pdtName)
        pnow = pnow->next;
    if(pnow == NULL)
    {
        cout << "没有找到该商品！" << endl;
        return ERROR;
    }
    cout << "你选择的商品信息如下" << endl;
    cout << "商品名称：" << pnow->pdtName << endl;
    cout << "商品价格：" << pnow->pdtprice << endl;
    cout << "商品销量：" << pnow->salesVolume << endl << endl;
    int choose;
    cout << "请选择要修改的信息！" <<endl;
    cout << "1：商品名称" << endl;
    cout << "2：商品价格" << endl;
    cout << "3: 商品名称及价格" << endl;
    cin >> choose;
    if(choose == 1)
    {
        cout << "请输入新的商品名称：";
        cin >> pnow->pdtName;
        return OK;
    }
    else if(choose == 2)
    {
        cout << "请输入新的商品价格：";
        cin >> pnow->pdtprice;
        return OK;
    }
    else if(choose == 3)
    {
        cout << "请输入新的商品名称：";
        cin >> pnow->pdtName;
        cout << "请输入新的商品价格：";
        cin >> pnow->pdtprice;
        return OK;
    }
    else
        cout << "输入错误，请重新输入！"<<endl;
}
bool Purchase(Store *S,int id,string pdtName,int num)
{
        if(id > S->storeId || id <= 0)
    {
        cout << "不存在该店铺！" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = (snow->pdt)->next;
    while(pnow != NULL && pnow->pdtName != pdtName)
        pnow = pnow->next;
    if(pnow == NULL)
    {
        cout << "没有找到该商品！" << endl;
        return ERROR;
    }
    cout << "你选择的商品信息如下" << endl;
    cout << "商品名称：" << pnow->pdtName << endl;
    cout << "商品价格：" << pnow->pdtprice << endl;
    cout << "商品销量：" << pnow->salesVolume << endl << endl;
    cout << "确定购买？(1为确定)" << endl;
    int choose = 0;
    cin >> choose;
    if(choose == 1)
        pnow->salesVolume += num;
    cout << "恭喜你成功购买了 " << pnow->pdtName << " 商品 " << num << "件" << endl;
    return OK;
}

void readTxT(Store *&S)
{
    S = new Store;
    ifstream infile;
    infile.open("data.txt",ios::in);
    if(!infile.is_open())
    {
        cout << "文件打开失败！" << endl;
        exit(ERROR);
    }
    assert(infile.is_open());
    string str;
    stringstream ss;
    getline(infile,str);
    int Storenum;
    ss << str;
    ss >> Storenum;
    S->storeId = Storenum;//读入商铺个数
    for(int i = 0;i < S->storeId;i++)
    {
        int m;
        Store *newS = new Store;
        newS->pdt = new Product;
        Product *pdt = newS->pdt;
        newS->next = NULL;
        pdt->next = NULL;

        getline(infile,str);
        m = atoi(str.c_str());
        newS->storeId = m;//读入商铺ID

        getline(infile,str);
        newS->storeName = str;//读入商铺名

        getline(infile,str);
        m = atoi(str.c_str());
        newS->storeCredit = m;//读入商铺信息

        getline(infile,str);
        m = atoi(str.c_str());
        pdt->salesVolume = m;//读入商品个数
        cout << "店铺编号：" << newS->storeId << endl;
        cout << "店铺名：" << newS->storeName << endl;
        cout << "店铺信誉："<<newS->storeCredit << endl;
        cout << "店铺商品数：" << pdt->salesVolume << endl;
        cout << endl;
        for(int j = 0;j < pdt->salesVolume;j++)
        {
            Product *newP  = new Product;
            newP->next = NULL;

            getline(infile,str);
            newP->pdtName = str;//读入商品名

            getline(infile,str);
            double price = (double)atof(str.c_str());//string 转 double
            newP->pdtprice = price;//读入商品价格

            getline(infile,str);
            int volume = atoi(str.c_str());//string 转 int
            newP->salesVolume = volume;//读入商品销量

            /*cout << "Name：" << newP->pdtName << endl;
            cout << "price：" << price << "  " << newP->pdtprice << endl;
            cout << "volume：" << newP->salesVolume << endl;
            cout << endl;*/
            Product *pnow = newS->pdt;
            for(int k = 0;k < j;k++)
                pnow = pnow ->next;
            pnow->next = newP;//连上pdt链表
        }
        Store *snow = S;
        for(int k = 0;k < i;k++)
            snow = snow->next;
        snow->next = newS;
    }
    infile.close();
}

void writeTXT(Store *&S)
{
    ofstream outfile;
    outfile.open("data.txt",ios::out);
    if(!outfile.is_open())
    {
        cout << "文件打开失败！" << endl;
        exit(ERROR);
    }
    Store *snow = S->next;
    outfile << S->storeId << endl;
    for(int i = 0;i < S->storeId;i++)
    {

        outfile << snow->storeId << endl;
        outfile << snow->storeName << endl;
        outfile << snow->storeCredit << endl;
        Product *pnow = snow->pdt;
        int num  = pnow->salesVolume;
        outfile << pnow->salesVolume <<endl;
        for(int j = 0;j < num;j++)
        {
            pnow = pnow->next;
            outfile << pnow->pdtName << endl;
            outfile << pnow->pdtprice <<endl;
            outfile << pnow->salesVolume <<endl;
        }
        snow = snow->next;
    }
    outfile.close();
}
bool TraverseStore(Store *&S)
{
    Store *snow = S->next;

    for(int i = 0 ;i < S->storeId;i++)
    {
        Product *pnow = snow->pdt;
        int num = pnow->salesVolume;
        cout << "*******************" << endl;
        cout << "店铺编号：" << snow->storeId << endl;
        cout << "店铺名：" << snow->storeName << endl;
        cout << "店铺信誉："<<snow->storeCredit << endl;
        cout << "店铺商品数：" << pnow->salesVolume << endl;
        cout << "*******************" << endl;
        cout << endl;
        for(int j = 0;j < num;j++)
        {
            pnow = pnow->next;
            cout << "Name：" << pnow->pdtName << endl;
            cout << "price：" << pnow->pdtprice << endl;
            cout << "volume：" << pnow->salesVolume << endl;
            cout << endl;
        }
        snow = snow->next;
    }
}
