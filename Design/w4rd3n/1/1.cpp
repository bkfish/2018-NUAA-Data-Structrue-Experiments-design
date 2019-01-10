#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct Commodity
{
	int sales;
	double price;
	char name[20];
}commodity;
//商品

typedef struct Shop
{
	int id;
	int num;
	char name[20];
	int credibility;
	commodity * cmdt;
	//指向商铺对应的商品列表 
}shop;
//商铺

typedef struct ShopList
{
	shop sp;
	struct ShopList * next;
	//单向链表 
}shopList;
//商铺列表

typedef struct ShopListOfCommodity
{
	int id;
	int sales;
	char name[20];
	int credibility;
	struct ShopListOfCommodity * next;
	struct ShopListOfCommodity * last;
	//双向链表 
}shopListOfCommodity;
//对应商品的商铺列表结点

typedef struct CommodityShopList
{
	commodity cmdt;
	shopListOfCommodity * spl;
	//单向链表 
}commodityShopList;
//对应商品的商铺列表

shopList * head,* tail;
//商铺列表的头和尾 
commodityShopList cmdt[10000];
//建立一个顺序结构，按商品名Hash分配地址，存储当前每种商品总销量并输出。 
int num;
//当前商铺数量，用于设置id 

void clear()
{
	head = tail = NULL;
	memset(cmdt,0,10000 * sizeof(commodityShopList));
	num = 0; 
}
//清除当前状态。 

int hash(char * p)
{
	int x = 1,y;
	char * name = p;
	
	for(;*p;p++)
	{
		x *= *p;
		x -= *p / 2;
		x %= 10000;
	}
	y = x;
	//用于发现开的数组满了 
	
	while(cmdt[x].cmdt.name[0] && strcmp(cmdt[x].cmdt.name,name))
	//如果发送碰撞，则向后移一位 
	{
		x++;
		x %= 10000;
		if(x == y)
		{
			printf("Error hash,memery is out!!!\n");
			system("pause"); 
			exit(0);
		}
		//防止溢出 
	}
	
	return x;
}
//hash函数 

void Init()
{
	FILE * file;
	shopList * now = NULL;
	shopList buf;
	
	file = fopen("1.dat","rb");
	if(!file)
	{
		printf("error: fopen(\"1.dat\",\"rb\")");
		exit(1);
	}
	//打开文件进行读取，带错误检测 
	
	int flag = 1;
	//用于标识是否是第一次fread 
	int i = 0,j = 1;
	//前者用于计数，后者用于判断是否新的节点排在第一个 
	
	while(1)
	{
		fread(&buf,sizeof(shopList),1,file);
		//读取到缓冲区 
		
		if(!feof(file))
		//判断是否到文件末尾 
		{
			num++;
			//每读取到一个，商铺数量加一 
			if(flag)
			//第一个商铺 
			{
				flag = 0;
				head = now = (shopList *)malloc(sizeof(shopList));
				//初始化链表头
				memcpy(now,&buf,sizeof(shopList)); 
				now->sp.id = num;
				//设置id 
				now->sp.cmdt = (commodity *)malloc(sizeof(commodity) * now->sp.num);
				//读取商铺对应的商品列表 
				fread(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
			}
			else
			//后面的商铺 
			{
				now->next = (shopList *)malloc(sizeof(shopList));
				memcpy(now->next,&buf,sizeof(shopList));
				now->next->sp.id = num;
				now = now->next;
				now->sp.cmdt = (commodity *)malloc(sizeof(commodity) * now->sp.num);
				fread(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
				//创建新的结点并将数据复制进去 
			}
			for(i = 0;i < now->sp.num;i++)
			//初始化商品对应的商铺列表 
			{
				if(cmdt[hash(now->sp.cmdt[i].name)].cmdt.name[0])
				//判断是否是第一次遇见此商品 
				{
					//如果不是第一次遇见此商品 
					shopListOfCommodity * now2 = cmdt[hash(now->sp.cmdt[i].name)].spl;
					//初始化一个指针用来遍历列表进行插入排序 
					cmdt[hash(now->sp.cmdt[i].name)].cmdt.sales += now->sp.cmdt[i].sales;
					//计算总销售量 
					while(now2->credibility > now->sp.credibility || (now2->credibility == now->sp.credibility && now2->sales > now->sp.cmdt[i].sales))
					//判断新商铺是否比当前商铺更靠后 
					{
						now2 = now2->next;
						//如果是，向后遍历 
						if(now2 == cmdt[hash(now->sp.cmdt[i].name)].spl)
						{
							j = 0;
							//表示次结点遍历完循环链表，应该在末尾，头节点不变 
							break;
						}
					}
					now2 = now2->last;
					shopListOfCommodity * temp = now2->next;
					now2->next = (shopListOfCommodity *)malloc(sizeof(shopListOfCommodity));
					now2->next->credibility = now->sp.credibility;
					now2->next->sales = now->sp.cmdt[i].sales;
					now2->next->id = now->sp.id;
					strcpy(now2->next->name,now->sp.name);
					//创建新的结点并将数据复制进去
					now2->next->last = now2;
					now2->next->next = temp;
					temp->last = now2->next;
					//双向循环链表的结点插入 
					if(now2->next->next == cmdt[hash(now->sp.cmdt[i].name)].spl && j)
					//如果当前为头节点，且j不置0，说明其比头节点“大” 
					{
						cmdt[hash(now->sp.cmdt[i].name)].spl = now2->next;
						j = 1; 
					}
				}
				else
				//第一次遇到 
				{
					cmdt[hash(now->sp.cmdt[i].name)].cmdt = now->sp.cmdt[i];
					cmdt[hash(now->sp.cmdt[i].name)].spl = (shopListOfCommodity *)malloc(sizeof(shopListOfCommodity));
					cmdt[hash(now->sp.cmdt[i].name)].spl->credibility = now->sp.credibility;
					cmdt[hash(now->sp.cmdt[i].name)].spl->sales = now->sp.cmdt[i].sales;
					cmdt[hash(now->sp.cmdt[i].name)].spl->id = now->sp.id;
					strcpy(cmdt[hash(now->sp.cmdt[i].name)].spl->name,now->sp.name);
					cmdt[hash(now->sp.cmdt[i].name)].spl->next = cmdt[hash(now->sp.cmdt[i].name)].spl;
					cmdt[hash(now->sp.cmdt[i].name)].spl->last = cmdt[hash(now->sp.cmdt[i].name)].spl;
					//初始化并建立双向循环链表 
				}
			}
		}
		else if(!flag)
		//如果读到文件尾且读入过数据 
		{
			now->next = NULL;
			tail = now;
			break;
		}
		//如果读到文件尾且为读入数据 
		else
		{
			head = tail = NULL;
			break;
		}
	}
	
	fclose(file);
	//关闭文件
	return;
}
//初始化商铺列表和所有商品对应的有序的商铺列表 

void Save()
{
	FILE * file;
	int nums = 1;
	//商铺id指示符 
	shopList * now = head;
	//初始化头指针用于遍历 
	
	file = fopen("1.dat","wb");
	if(!file)
	{
		printf("error: fopen(\"1.dat\",\"wb\")");
		exit(1);
	}
	
	while(now)
	{
		shopList * temp = now; 
		now->sp.id = nums++;
		fwrite(now,sizeof(shopList),1,file);
		fwrite(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
		now = now->next;
		//循环写入文件 
		free(temp->sp.cmdt);
		free(temp);
		//释放内存 
	}
	
	fclose(file);
	//关闭文件 
	return;
}
//将商铺信息和对应的商品信息以二进制形式保存在文件中 

void add()
{
	shopList now;
	//保存用户输入 
	int x = 0;
	//用于读数据和充当计数器 
	
	now.sp.id = ++num;
	//设置id 
	now.next = NULL;
	
	printf("Please input name of shop(length < 20):");
	fgets(now.sp.name,20,stdin);
	int l = strlen(now.sp.name);
	if(l != 19)
	{
		now.sp.name[l - 1] = '\0';
	}
	//清除fgets留下的换行符 
	
	printf("Please input credibility of shop(0-5):");
	scanf("%d",&x);
	fflush(stdin);
	//刷新缓冲区 
	if(x < 0||x > 5)
	{
		printf("Error number!!!\n");
		system("pause"); 
		return;
	}
	now.sp.credibility = x;
	
	x = 0;
	printf("Please input number of shop commodity:");
	scanf("%d",&now.sp.num);
	fflush(stdin);
	now.sp.cmdt = (commodity *)malloc(now.sp.num * sizeof(commodity));
	
	while(x++ < now.sp.num)
	{
		printf("Please input name of commodity %d(length < 20):",x);
		fgets(now.sp.cmdt[x - 1].name,20,stdin);
		l = strlen(now.sp.cmdt[x - 1].name);
		if(l != 19)
		{
			now.sp.cmdt[x - 1].name[l - 1] = '\0';
		}
		printf("Please input price of commodity %d:",x);
		scanf("%lf",&now.sp.cmdt[x - 1].price);
		fflush(stdin);
		printf("Please input sales of commodity %d:",x);
		scanf("%d",&now.sp.cmdt[x - 1].sales);
		fflush(stdin);
	}
	//读入对应的商品信息 
	
	if(head)
	//如果已经有头指针 
	{
		tail->next = (shopList *)malloc(sizeof(shopList));
		tail = tail->next;
		memcpy(tail,&now,sizeof(shopList));
	}
	else
	//没有则初始化 
	{
		head = tail = (shopList *)malloc(sizeof(shopList));
		memcpy(tail,&now,sizeof(shopList));
	}
	
	system("cls");
	//清空屏幕 
	return;
}
//按照用户输入增加商铺，编号自动加一，插入链表尾部。 

void del()
{
	printf("-----------------------------------");
	printf("Welcome to cws's shop manage system");
	printf("-----------------------------------\n");
	printf("-----------------------------------");
	printf("--what shop do you want to delete?-");
	printf("-----------------------------------\n");
	
	shopList * now = head,* last = NULL;
	
	while(now)
	{
		printf("%d:%s\n",now->sp.id,now->sp.name);
		now = now->next;
	}
	//遍历并打印商铺id和名字 
	
	printf("Please input the shop id:");
	int x;
	scanf("%d",&x);
	
	now = head;
	while(now && now->sp.id != x)
	{
		last = now;
		now = now->next;
	}
	//找到对应id商铺
	 
	if(!now)
	//没有找到，即now为NULL 
	{
		printf("Error id of shop!!!\n");
		system("pause");
		return;
	}
	
	if(last)
	//不是头指针 
	{
		last->next = now->next;
		if(!last->next)
		//如果为尾指针 
		{
			tail = last;
		}
		free(now->sp.cmdt);
		free(now);
		while(last->next)
		//将后面的指针对应的商铺id逐一减一 
		{
			last = last->next;
			last->sp.id--;
		}
	}
	else
	//删除的为头指针 
	{
		if(head == tail)tail = NULL;
		head = head->next;
		free(now->sp.cmdt);
		free(now);
	}
	
	system("cls");
	//清空屏幕 
	return;
}
//删除商铺，以编号为准，并修改后续结点的编号，保持编号连续性。 

void buy()
{
	printf("-----------------------------------");
	printf("Welcome to cws's shop manage system");
	printf("-----------------------------------\n");
	printf("-----------------------------------");
	printf("-what commodity do you want to buy?");
	printf("-----------------------------------\n");
	
	printf("Please input commodity name:");
	char name[20];
	
	fgets(name,20,stdin);
	int l = strlen(name),m;
	if(l != 19)
	{
		name[l - 1] = '\0';
	}
	//读入商品名字 
	
	commodityShopList x = cmdt[hash(name)];
	if(!(x.cmdt.name[0]))
	//判断是否有商铺有此商品 
	{
		printf("no sale of %s!!!\n",name);
		system("pause");
		return;
	}
	
	shopListOfCommodity * y = x.spl;
	
	printf("%d:%s,credibility: %d,sales: %d\n",y->id,y->name,y->credibility,y->sales);
	y = y->next;
	while(y != x.spl)
	{
		printf("%d:%s,credibility: %d,sales: %d\n",y->id,y->name,y->credibility,y->sales);
		y = y->next; 
	}
	//遍历商品对应的商铺列表并打印对应的商铺id，名字，信誉度，销量 
	
	printf("Please input shop id and number to buy like (1 4):");
	scanf("%d %d",&l,&m);
	
	shopList * now = head;
	while(now && now->sp.id != l)
	{
		now = now->next;
	}
	//找到对应的商铺结点
	 
	if(now)
	{
		int i = 0;
		for(;i < now->sp.num;)
		{
			if(!strcmp(now->sp.cmdt[i].name,name))
			{
				now->sp.cmdt[i].sales += m;
				break;
				//找到对应商品并增加销量 
			}
		}
	}
	else
	{
		printf("Error id!!!\n");
		system("pause");
		return;
	}
	
	system("cls");
	//清空屏幕 
	return;
}
//查询某一种商品名称，建立一个双向循环链表，结点信息是包含该商品的所有商铺编号、商铺名、信誉度、商品名称、价格、销量，以信誉度从高至低，并按销量排序，并逐一显示。
//购买某一商铺的商品，修改单向链表中商品的信息的销量。 
 
void menu()
{
	while(1)
	{
		printf("-----------------------------------");
		printf("Welcome to cws's shop manage system");
		printf("-----------------------------------\n");
		printf("-----------------------------------");
		printf("------what do you want to do?------");
		printf("-----------------------------------\n");
		printf("1.add shop\n");
		printf("2.delete shop\n");
		printf("3.buy\n");
		printf("4.exit\n");
	
		int x;
		scanf("%d",&x);
		fflush(stdin);
		system("cls");
	
		switch(x)
		{
			case 1:
				add();
				break;
			case 2:
				del();
				break;
			case 3:
				buy();
				break;
			case 4:
				return;
			default:
				printf("valid choice!!!\n");
				break;
		}
		
		Save();
		clear();
		Init();
		//任何的商铺信息变化，实现文件存储。
		
		system("cls");
		//清空屏幕 
	}
	
	return;
}
//用于交互的菜单界面 

int main()
{
	Init();
	//通过文件初始化 
	
	menu();
	
	return 0;
}
