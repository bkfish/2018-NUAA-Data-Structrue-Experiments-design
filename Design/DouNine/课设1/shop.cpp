/*
设计一个程序，对商铺信息管理，商铺信息包括：商铺编号，商铺名，信誉度（0-5），
（商品名称1，价格1，销量1），（商品名称2，价格2，销量2），（商品名称3，价格3，销量3）…。
商品名称包括(毛巾，牙刷，牙膏，肥皂，洗发水，沐浴露等6种以上商品)，
每个商铺具有其中事先确定若干商品及价格，由文件输入，销量初始为0。
[基本要求]
（1）建立一个单向链表存储所有商铺信息（至少30个），以编号为序，编号从1开始递增，
	从文件中读取数据，并能将数据存储在文件。商铺信息结点的数据结构自行设计。
（2）可以增、删商铺。增加商铺，编号自动加一，插入链表尾部；
	删除商铺，以编号为准，并修改后续结点的编号，保持编号连续性。可增、删商品。
（3）查询某一种商品名称，建立一个双向循环链表，结点信息是包含该商品的
	所有商铺编号、商铺名、信誉度、商品名称、价格、销量，以信誉度从高至低，并按销量排序，并逐一显示。
（4）购买某一商铺的商品，修改单向链表中商品的信息的销量。
（5）建立一个顺序结构，按商品名Hash分配地址，存储当前每种商品总销量并输出。 
（6）任何的商铺信息变化，实现文件存储。
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;

// 商品 
typedef struct WareNode 
{
	char wareName[100];	// 商品名字 
	int price;			// 价格 
	int sales;			// 销量 
	int shopId;			// 店铺编号
	WareNode *pre, *next; 
}*WareList;

// 店铺 
typedef struct ShopNode 
{
	int shopId;
	char shopName[100];
	int shopCredit;
	int wareCount;
	WareList wareList;
	ShopNode *next;
}*ShopList;

// hash商品 
typedef struct 
{
	bool flag;
	char wareName[100];
	int sales;
}HashWare;

// 全局变量 
FILE *fp;
char fileName[] = "shopDate.txt";

ShopList sList;	// 店铺链表 
int shopCount = 0;

WareList wList;	// 商品列表（双向链表） 
HashWare hash[10000];


// 打开文件 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// 查找店铺
ShopNode* FindShop(int shopId) 
{
	ShopNode *sNode = sList->next;
	while (sNode)
	{
		//printf("====shopId:%d\n", sNode->shopId);
		if (sNode->shopId == shopId) 
		{
			return sNode;
		} 
		sNode = sNode->next;
	}
	printf("find shop fail, no this shop, shopId is %d\n", shopId);
	return NULL;
}

// 显示商品信息
void ShowWareInfo(WareNode *ware) 
{
	printf("  |------------------------------------\n  |\n");
	printf("  |商品名字：%s\n  |商品价格：%d    商品销量：%d\n  |\n", ware->wareName, ware->price, ware->sales);
	ShopNode *shop = FindShop(ware->shopId);
	printf("  |所属商铺编号：%2d\n  |商铺名字：%s    商铺信誉度：%d\n  |\n", shop->shopId, shop->shopName, shop->shopCredit);
	printf("  |------------------------------------\n");
} 

// 显示店铺信息
void ShowShopInfo(ShopNode *shop) 
{
	printf("===============================================\n");
	printf("店铺编号：%2d	店铺名：%s	信誉度：%d\n\n所拥有商品个数：%d\n\n", shop->shopId, shop->shopName, shop->shopCredit, shop->wareCount);
	printf("店铺商品如下：\n");
	WareNode *wNode = shop->wareList->next;
	while (wNode) 
	{
		ShowWareInfo(wNode);
		wNode = wNode->next;
	}
	printf("===============================================\n");
}

// 显示店铺链表中所有商铺信息
void ShowShopList() 
{
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		ShowShopInfo(sNode);
		sNode = sNode->next;
	}
}

// 对商品名进行哈希映射
int Hash(char *wareName) 
{
	int pos = (wareName[0] * wareName[1] + 12345678) % 10000;
	//cout<<pos<<endl;
	while (1) 
	{
		if (hash[pos].flag == false || strcmp(hash[pos].wareName, wareName) == 0) break;
		pos++;
		if (pos >= 10000) pos = 0;
	}
	hash[pos].flag = true;
	strcpy(hash[pos].wareName, wareName);
	return pos;
}

// 初始化，从文件中读取数据 
void Init() 
{	
	// 初始化店铺链表，即从文件中读取数据 
	fileOpen("r");
	
    sList = (ShopNode*)malloc(sizeof(ShopNode));
    sList->shopId = 0;
    sList->next = NULL;
    ShopNode *sLast = sList;	// 指向店铺链表的最后一个结点 
    fscanf(fp, "%d", &shopCount);
    for (int i=0; i<shopCount; i++) 
    {
    	// 读取店铺信息
    	ShopNode *sNode = (ShopNode*)malloc(sizeof(ShopNode));
    	fscanf(fp, "%d%s%d%d", &sNode->shopId, sNode->shopName, &sNode->shopCredit, &sNode->wareCount);
    	sNode->next = NULL;
    	sNode->wareList = (WareNode*)malloc(sizeof(WareNode));
    	sNode->wareList->next = NULL;
    	sNode->wareList->pre = NULL;
    	
    	// 读取商铺商品信息 
    	WareNode *wLast = sNode->wareList;	// 指向商品链表最后一个结点的指针 
    	for (int j=0; j<sNode->wareCount; j++) 
    	{
    		WareNode *wNode = (WareNode*)malloc(sizeof(WareNode));
    		fscanf(fp, "%s%d%d", wNode->wareName, &wNode->price, &wNode->sales);
    		wNode->shopId = sNode->shopId;
    		wNode->next = NULL;
    		wLast->next = wNode;
    		wNode->pre = wLast;
    		wLast = wNode;
		}
		
		// 将last指向新结点 
		sNode->next = NULL; 
		sLast->next = sNode;
		sLast = sNode;
	}
	fileClose();
	
	//ShowShopList();
	
	// 初始化哈希表 
	for (int i=0; i<10000; i++) 
	{
		hash[i].flag = false;
		hash[i].sales = 0;
	}
	// 遍历店铺链表，初始化每个商品的销量 
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		// 遍历该店铺的商品链表 
		WareNode *wNode = sNode->wareList->next;
		while (wNode) 
		{
			int pos = Hash(wNode->wareName);
			hash[pos].sales += wNode->sales; 
			wNode = wNode->next;
		}
		sNode = sNode->next;
	} 
}

// 初始化要查询商品的双向链表
void InitWareList() 
{
	wList = (WareNode*)malloc(sizeof(WareNode));
	wList->next = NULL;
	wList->pre = NULL;
}

// 销毁商品链表
void DestroyWareList(WareList &wList) 
{
	WareNode *wNode = wList;
	while (wNode) 
	{
		WareNode *temp = wNode->next;
		free(wNode);
		wNode = temp;
	}
	printf("销毁商品链表成功\n");
}

// 结束，将数据存回到文件中 
void Finish() 
{
	// 销毁店铺链表，同时将数据存回到文件中 
	fileOpen("w+");
	ShopNode *sNode = sList->next;
	free(sList);	// free头指针
	fprintf(fp, "%d\n", shopCount);
	while (sNode) 
	{
		//ShowShopInfo(sNode);
		ShopNode *temp = sNode->next;
		// 输出店铺信息到文件 
    	fprintf(fp, "%d   %s   %d   %d\n", sNode->shopId, sNode->shopName, sNode->shopCredit, sNode->wareCount);
    	// 输出店铺商品到文件 
		WareNode *wNode = sNode->wareList->next; 
		while (wNode) 
		{
    		fprintf(fp, "   %s   %d   %d\n", wNode->wareName, wNode->price, wNode->sales);
    		wNode = wNode->next;
		}
		// 销毁该店铺的商品链表 
		DestroyWareList(sNode->wareList);
		// free商铺结点 
		free(sNode);
		sNode = temp;
	}
	fileClose();
	//printf("销毁店铺链表成功\n");
}
 
// 增加店铺
void AddShop(ShopNode *shopNode) 
{
	shopCount++;
	
	// 找到最后一个 
	ShopNode *sNode = sList;
	while (sNode->next) 
	{
		sNode = sNode->next;
	}
	sNode->next = shopNode;
	
	shopNode->shopId = sNode->shopId + 1;
	shopNode->wareCount = 0;
	shopNode->wareList = (WareNode*)malloc(sizeof(WareNode));
	shopNode->wareList->next = NULL;
	shopNode->next = NULL;
	
	printf("增加店铺成功\n");
}

// 删除店铺
void DeleteShop(int shopId) 
{
	ShopNode *sNode = sList->next, *sNPre = sList;
	bool isFind = false;
	while (sNode) 
	{
		if (sNode->shopId == shopId) 
		{
			ShowShopInfo(sNode);
			DestroyWareList(sNode->wareList);
			sNPre->next = sNode->next;
			free(sNode);
			
			// 使得被删除店铺的后面店铺的编号都减一 
			sNode = sNPre->next;
			while (sNode) 
			{
				sNode->shopId--;
				// 对应商品的商铺编号也要-- 
				WareNode *wNode = sNode->wareList->next;
				while (wNode) 
				{
					wNode->shopId--;
					wNode = wNode->next;
				}
				sNode = sNode->next;
			}
			
			isFind = true;
			break;
		}
		else 
		{
			sNPre = sNode;
			sNode = sNPre->next;
		} 
	}
	if (!isFind) 
	{
		printf("delete shop fail, no this shop, shopId is %d\n", shopId);
	}
	shopCount--;
} 

// 增加店铺商品
void AddShopWare(int shopId, WareNode *wNode) 
{
	ShopNode *shop = FindShop(shopId);
	shop->wareCount++;
	
	WareNode *ware = shop->wareList;
	while (ware->next) 
	{
		if (strcmp(ware->wareName, wNode->wareName) == 0) 
		{
			ShowWareInfo(ware);
			printf("该商品已存在\n");
			return;
		}
		ware = ware->next;
	}

	ware->next = wNode;
	wNode->shopId = shopId;
	wNode->pre = ware;
	wNode->next = NULL;
} 

// 删除店铺商品
void DeleteShopWare(int shopId, char *wareName) 
{
	ShopNode *shop = FindShop(shopId);
	WareNode *ware = shop->wareList->next, *preWare = shop->wareList; 
	
	bool isFind = false; 
	while (ware) 
	{
		if (strcmp(ware->wareName, wareName) == 0) 
		{
			ShowWareInfo(ware);
			preWare->next = ware->next;
			free(ware);
			ware = preWare->next;
			shop->wareCount--;
			isFind = true;
			break;
		}
		else 
		{
			preWare = ware;
			ware = ware->next;
		}
	}
	
	if (!isFind) printf("delete fail, no this ware, ware name is %s", wareName);
}

// 初始化并显示要查询商品的双向链表 
void ShowWareList(char *wareName) 
{
	// 遍历店铺链表 
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		// 遍历该店铺的商品链表 
		WareNode *wNode = sNode->wareList->next;
		while (wNode) 
		{
			// 如果该商品是要查询的商品 
			if (strcmp(wNode->wareName, wareName) == 0) 
			{
				// 申请新结点，并将要插入商品结点信息复制到其中 
				WareNode *newWare = (WareNode*)malloc(sizeof(WareNode));
				newWare->shopId = wNode->shopId;
				strcpy(newWare->wareName, wNode->wareName);
				newWare->sales = wNode->sales;
				newWare->price = wNode->price;
				
				// 遍历已排好序的商品链表 
				WareNode *ware = wList->next, *preWare = wList;	// 已排好序的结点 
				while (ware) 
				{
					ShopNode *temp = FindShop(newWare->shopId);	// 要插入的结点 
					ShopNode *tempCmp = FindShop(ware->shopId);	// 已经排好序的链表中的结点 
					// 如果插入点的信誉度高则插前 
					if ((temp->shopCredit > tempCmp->shopCredit)
						|| (temp->shopCredit == tempCmp->shopCredit && ware->sales > wNode->sales)) break;
					preWare = preWare->next;
					ware = ware->next;
				}
				// 插入 
				newWare->next = ware;
				if (ware) ware->pre = newWare;
				preWare->next = newWare;
				newWare->pre = preWare;
				break; 
			}
			wNode = wNode->next;
		}
		sNode = sNode->next;
	}
	
	printf("****************%s******************\n", wareName);
	WareNode *ware = wList->next;
	while (ware) 
	{
		ShowWareInfo(ware);
		ware = ware->next;
	}
	printf("***********************************\n");
} 

// 显示选项
void choose() 
{
	system("cls");
	printf("\n|---------------------------|\n");
	printf("|0.退出                     |\n");
	printf("|1.增加店铺                 |\n");
	printf("|2.删除店铺                 |\n");
	printf("|3.显示所有店铺             |\n");
	printf("|4.增加店铺商品             |\n");
	printf("|5.删除店铺商品             |\n");
	printf("|6.查询商品                 |\n");
	printf("|7.购买商品                 |\n");
	printf("|8.显示每种商品的销量       |\n");
	printf("|---------------------------|\n");
	printf("\n请输入你的选择(1-8):\n");
}


int main() 
{
	Init();
	
	int n = 0;
	choose();
	scanf("%d", &n);
	while (n) 
	{
		if (0 >= n || n > 8) 
		{
			printf("error! try again\n");
			printf("\n请输入你的选择(1-8):\n");
			scanf("%d", &n);
			continue;
		}
		char wareName[100];
		int shopId = 0;
		switch (n) 
		{
			// 增加店铺 
			case 1: 
			{
				ShopNode *sNode = (ShopNode*)malloc(sizeof(sNode)); 
				printf("请输入你要增加的店铺信息，依次输入店铺名和店铺信誉度：\n");
				scanf("%s%d", sNode->shopName, &sNode->shopCredit);
				AddShop(sNode);
				break;
			}
			// 删除店铺 
			case 2: 
			{
				printf("请输入你要删除的店铺编号：\n");
				scanf("%d", &shopId);
				DeleteShop(shopId);
				break;
			}
			// 显示所有店铺
			case 3: 
			{
				ShowShopList();
				break;
			} 
			// 增加店铺商品
			case 4: 
			{
				WareNode *wNode = (WareNode*)malloc(sizeof(WareNode));
				printf("请输入你要增加店铺商品的店铺编号：\n");
				scanf("%d", &shopId);
				printf("请输入要增加商品的信息，请依次输出商品名、价格、销量：\n");
				scanf("%s%d%d", wNode->wareName, &wNode->price, &wNode->sales);
				AddShopWare(shopId, wNode);
				// 该商品总销量增加 
				hash[Hash(wareName)].sales += wNode->sales;
				break;
			}
			// 删除店铺商品
			case 5: 
			{
				printf("请输入你要删除店铺商品的店铺编号：\n");
				scanf("%d", &shopId);
				printf("请输入要删除商品的名字：\n");
				scanf("%s", wareName);
				DeleteShopWare(shopId, wareName); 
				break;
			}
			// 查询商品
			case 6: 
			{
				printf("请输入你要查询商品的名字：\n");
				scanf("%s", wareName);
				InitWareList(); 
				ShowWareList(wareName);
				DestroyWareList(wList);	// 销毁该商品的双向链表 
				break;
			}
			// 购买商品
			case 7: 
			{
				printf("请输入你要购买的商品的名字和店铺的编号：\n");
				scanf("%s%d", wareName, &shopId);
				ShopNode *shop = FindShop(shopId);
				
				// 修改该店铺对应商品的销量，遍历该店铺的商品链表 
				WareNode *ware = shop->wareList->next;
				while (ware) 
				{
					// 如果该商品是要查询的商品 
					if (strcmp(ware->wareName, wareName) == 0) 
					{
						ware->sales++;
					}
					ware = ware->next;
				}
				
				// 该商品总销量加一 
				hash[Hash(wareName)].sales++;
				break;
			}
			// 显示每种商品的销量
			case 8: 
			{
				printf("请输入你要查询商品销量的商品名：\n");
				scanf("%s", wareName);
				int pos = Hash(wareName);
				//cout<<pos<<endl;
				printf("该商品销量为：%d\n", hash[pos].sales);
				break;
			}
		}
		printf("\n\n\n>>>>>>>>>>>>>>>>>>>>>您要返回主菜单吗？(1是的/0退出)：");
		scanf("%d", &n);
		while (n != 0 && n != 1) 
		{
			printf("sorry, try again.\n");
			printf("\n>>>>>>>>>>>>>>>>>>>>>您要返回主菜单吗？(1是的/0退出)：");
			scanf("%d", &n);
		}
		if (n == 0) break; 
		
		choose();
		scanf("%d", &n);
	}
	printf("\nBye~\n");
	
	Finish(); 
}
