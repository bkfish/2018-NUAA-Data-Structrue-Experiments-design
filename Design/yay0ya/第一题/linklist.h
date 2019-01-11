#include"goods.h"
#define Max 50 
#define Inscrent 10 
typedef goodlink SElemType;
typedef struct shop{
	int id;
	string name;
	int credit;
	SElemType goods;
	struct shop *next;//指针指向下一个商铺 
}sNode,*Shop;
bool Initlinklist(Shop &S){
	sNode *p,*head;
	head=NULL; 
	for(int i=0;i<Max;i++){
		p=new sNode;
		p->next=head;
		head=p;
	}
	S=head;
	return 1;//创造max个结点
}
bool goodfilein(sNode *p,fstream &file){
	int n=p->goods.numbers;//来记录商品的数量
	goods *goodp;//商品指针
	goodp=p->goods.data;//这个指向商品的第一个值 
	file<<n;//传入商品的数量 
	for(int i=0;i<n;i++){
		file<<goodp->name;//向文件中输入商品的名字
		file<<goodp->price;//输入商品的价格
		file<<goodp->sold;//输入商品的销量 
	}//完成一个商铺输入后及下附属的商品输入 
	return 1; 
}
bool goodfileout(sNode *p,fstream f){
	int n;
	f>>n;//传出商品的数量
	goods *goodp;
	goodp=p->goods.data;//将该指针指向这个p中商品的数量数据 
	p->goods.data=new goods[n];//为商品中goods的结点申请n个空间
	p->goods.numbers=n;//将商品的数量赋值给p结点中的数量
	for(int i=0;i<n;i++){
		file>>goodp.name;
		file>>goodp.price;
		file>>goodp.sold;
		goodp++;//完成文件中的内容输出给商铺对象 
	}
	return 1; 
}
bool filein(Shop S){
	fstream file("data.txt",ios::in);
	if(!file.is_open()){
		cout<<"文件打开失败\n";
		return 0;
	}
	sNode *p=S;//将p设置为 
	while(p!=NULL){
		file<<p->name;
		file<<p->credit;
		goodfilein(p,file);//将物品的信息写入文件 
		p=p->next;
	}//将变更后的数据写入文件
	file.close();
	return 1; 
}
bool createlinklist(Shop &S){
	fstream file;
	file.open("data.txt",ios::in|ios::out);//以输入输出的方式打开一个文件
	sNode *p;
	p=S;
	if(!file,is_open())
		{
			cout<<"file open ERROR\n";
			exit(0);
		}//如果文件打开失败
	for(int i=0;i<Max;i++){
		p->id=i+1;
		if(!file.eof())
			break;
		file>>p->name;
		file>>p->credit; 
		p=p->next;//将所有的id赋予 商铺 
	}
	file.close();
	return 1;	 
}
bool AddOneShop(Shop &S){
	sNode *p;
	p=S;
	if(p==NULL){
	//如果本来S这个链表中不包含任何的商铺信息
		p=new sNode;
		p->id=1;
		cout<<"输入商铺的名字\n";
		cin>>p->name;
		cout<<"输入商铺的信誉\n";
		cin>>p->credit;
		p->next=S;
		S=p;	
	}
	else{
		while(p->next!=NULL){
			p=p->next;
			}
		sNode q;
		p->next=q;
		q.next=NULL;
		q.id=p->id+1;
		cout<<"输入商铺的名字\n";
		cin>>q.name;
		cout<<"输入商铺的信誉\n";
		cin>>q.credit;
		}	
		if(!filein(S)){
			cout<<"文件写入失败\n";
			return 0;
		}
		return 1;

}//AddOneShop

bool DeleteOneShop(Shop &S,int id){
	sNode *p,*q;
	q=S;
	p=S;
	while(p!=NULL){
		if(p->id==id)
			break;
		q=p;	
		p=p->next;
	}
	if(p==NULL){
		cout<<"不存在此商铺\n";
		return 0;
	}
	if(q==p){
		//判断这个结点是否是头结点
		q=p->next;//如果是头结点，则删除头；
		S=q;
		free(p);//释放结点空间 
	}
	else{//不是头结点 
		q->next=p->next;//将这个结点删除
		free(p);//释放p这个结点 
	}
	p=S;
	int count=1;
	while(p!=NULL){
		p->id=count;
		count++;
		p=p->next;//重新为商铺的id赋值 
	}
	//将变更后的商铺写入文件 
	if(!filein(S)){
			cout<<"文件写入失败\n";
			return 0;
	}
		return 1;
}
bool deletegoods(Shop &S,int number,string name)
//S为商铺的链表，通过编号number定位商铺的位置，string匹配，找到需要删除的商品
{
	sNode *p;
	int count=0; 
	p=S;
	if(S==NULL){
		cout<<"没有商铺存在\n";
		return 0;//报错退出 
	}
	while(p!=NULL){//指针不为空 
		if(p->id==number)//如果p所指的商铺id符合要求
		{
			break;
		 }
		 p=p->next;
		 count++; 
	}
	if(number<1||number>count&&p==NULL){
		cout<<"不存在id为"<<number<<"的商铺\n";
		return 0;//退出 
	}
	goods *goodp,*goodq;
	if(p->id==number)//商铺的店铺id与number匹配
	{
		count=0;
		goodp=p->goods.data;//goodp指针指向goods的数据 
		for(int i=0;i<p->goods.numbers;i++)//当遍历的元素小于商铺中存在的元素时
		{
			if(goodp.name==name)//商品名称与商铺中存在的商品名称相匹配
			{
				free(goodp);//将这个空间的东西释放 
				break;//
			 }
			 count++; 
		 }
		 if(count==p->goods.numbers){
		 	cout<<"查无此商品\n";
		 	return 0;//报错 
		 }
		 
	 }//完成删除操作
	 //对文件重新进行写入
	 filein(S);
	 return 1;//完成删除操作 
 }
bool addgoods(Shop &S,int number){
		sNode *p;
	int count=0; 
	p=S;
	if(S==NULL){
		cout<<"没有商铺存在\n";
		return 0;//报错退出 
	}
	while(p!=NULL){//指针不为空 
		if(p->id==number)//如果p所指的商铺id符合要求
		{
			break;
		 }
		 p=p->next;
		 count++; 
	}
	if(number<1||number>count&&p==NULL){
		cout<<"不存在id为"<<number<<"的商铺\n";
		return 0;//退出 
	}
	//完成商铺的查找功能下面尽心插入商品的操作
	goods *goodp;
	if(p->id==number)//如果商铺id与要查找的id相同
	{
		goodp=p->goods.data;
		goodp=(goods*)realloc((p->goods.numbers+1)*goods);
		for(int i=0;i<p->goods.numbers;i++){
			goodp++;
		}
		cout<<"请输入商品的名称\n";
		cin>>goodp->name;
		cout<<"请输入商品的价格\n";
		cin>>goodp->price;
		cout<<"请输入商品的销售数量\n";
		cin>>goodp->sold;
		filein(S);//完成增加商品的操作; 
	 }
	 return 1; 
}

