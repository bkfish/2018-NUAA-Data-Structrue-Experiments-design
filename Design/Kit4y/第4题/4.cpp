#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string> 
#define INF 0x7fffffff 

using namespace std;

fstream source,Huffman,code,decodes;
//文件流对象 

typedef struct Node
{
	int key;
	//对应字符 
	int count;
	//出现次数
	int p;
	//父结点
	int l;
	int r;
	//左右子结点 
}node;

typedef struct Json
{
	int val;
	string key;
}json;
//映射编码和字符 

node counts[256];
//统计字符出现次数
int num;
//统计出现的字符数 
int bitmap[40000];
int length; 
//用于存储二进制Huffman编码，和使用位的长度
vector<string> codes;
//用于存储字符串形式的编码
Json test[10000];
//用于通过Huffman编码字符串索引到对应字符 

int hash(string p)
{
	int x = 1,y;
	string key = p;
	//用于处理碰撞
	 
	for(int i = 0;i < p.size();i++)
	{
		x *= p[i];
		x -= p[i] / 2;
		x %= 10000;
	}
	y = x;
	
	while(test[x].key.size() && !(test[x].key == key))
	//如果发生碰撞，则向后移一位 
	{
		x++;
		x %= 10000;
		if(x == y)
		{
			cout << "Error hash,memery is out!!!\n";
			exit(0);
		}
		//防止溢出 
	}
	
	return x;
}
//hash函数

void setBit(int * bit,int i)
{
	bit[i / sizeof(int) / 8] |= 1 << (i % (sizeof(int) * 8));
	
	return;
}
//设置指定的位为1 

void clearBit(int * bit,int i)
{
	bit[i / sizeof(int) / 8] &= (1 << (i % (sizeof(int) * 8))) ^ 0xffffffff;
	
	return;
}
//设置指定的位为0 

bool getBit(int * bit,int i)
{
	return bit[i / sizeof(int) / 8] & 1 << (i % (sizeof(int) * 8));
}
//获得指定的位的值 

void Init()
{
	source.open("source.txt",ios::in);
	//读取原始英文文章 
	source >> noskipws;
	//不忽略空格和换行 
	
	Huffman.open("Huffman.txt",ios::out);
	//存储各字符出现次数和编码
	
	code.open("code.dat",ios::out | ios::binary);
	//存储二进制形式的编码后的文章
	
	decodes.open("decode.txt",ios::out);
	//存储二进制形式的编码后的文章
	
	for(int i = 0;i < 128;i++)
	{
		counts[i].key = i;
	}
	//初始化node中的key值 
}
//初始化文件流和结构体数组 

void Fini()
{
	source.close();
	Huffman.close();
	code.close();
	decodes.close();
	
	return;
}
//关闭文件流 

void create()
{
	for(int i = 0;i < num - 1;i++)
	{
		int min1 = INF,min2 = INF;
		int a = 0,b = 0,j = 0;
		while(j < 256 && counts[j].count)
		{
			if(!counts[j].p && counts[j].count < min2)
			{
				if(counts[j].count < min1)
				{
					min2 = min1; 
					min1 = counts[j].count;
					b = a;
					a = j;
				}
				else
				{
					min2 = counts[j].count;
					b = j;
				}
			}
			j++;
		} 
		if(j < 256)
		{
			counts[a].p = j;
			counts[b].p = j;
			counts[j].l = a;
			counts[j].r = b;
			counts[j].count = min1 + min2;
			//cout << j << ".  " << "l:" << counts[j].l << ",r:";
			//cout << counts[j].r << ",count:" << counts[j].count <<endl;
		}
	}
	
	return;
}
//创建Huffman树 

void count()
{
	char x;
	
	source >> x;
	while(!source.eof())
	{
		counts[x].count++;
		source >> x;
		//cout << x;
	}
	
	for(int i = 0;i < 128;i++)
	{
		if(counts[i].count)
		{
			num++;
		}
		else
		{
			counts[i].count = INF;
		}
	}
	
	source.close();
	source.open("source.txt",ios::in); 
	source >> noskipws;
	//重新打开准备编码
	 
	return;
}
//计算字符出现的次数 

void encode()
{
	for(int i = 0;i < 128;i++) {
		string temp;
		int j = i;
		int p = counts[i].p;
		while(p) {
			if (counts[p].l == j)temp.insert(0,"0");
			else temp.insert(0,"1");
			j = p;
			p = counts[p].p;
		}
		codes.push_back(temp);
	}
	
	for(int i = 0;i < 128;i++) {
		if(counts[i].count == INF)
		{
			continue;
		}
		//cout << (char)i << ".  " << "val is " << counts[i].count << ", code is " << codes[i] << endl;
		Huffman << setw(10) << counts[i].key;
		Huffman << setw(10) << counts[i].count;
		Huffman << setw(10) << codes[i];
		Huffman << endl;
	}
	Huffman.close();
	Huffman.open("Huffman.txt",ios::in);
	//重新打开准备解码成文本 
	
	char x;
	
	source >> x;
	while(!source.eof())
	{
		//cout << "string:" << codes[x] << "\t\tbit:";
		string s = codes[x];
		for(int i = 0;i < s.size();i++)
		{
			if(s[i] == '0')
			{
				clearBit(bitmap,length);
				//cout << getBit(bitmap,length);
				length++;
			}
			else if(s[i] == '1')
			{
				setBit(bitmap,length);
				//cout << getBit(bitmap,length);
				length++;
			}
		}
		//cout << "\t\tchar:" << x << endl;
		source >> x;
	}
	
	code << length << "\n";
	code.write((char *)bitmap,length / 8 + 1);
	
	code.close();
	code.open("code.dat",ios::in | ios::binary);
	//读取二进制形式的编码后的文章准备解码 
	
	
	return; 
}
//进行Huffman编码并以字符串形式保存，写入Huffman文件和code文件 

void decode()
{
	//cout << length << endl;
	code >> length;
	char pad[100];
	int pad2;
	//cout << length << endl;
	//cout << hex << bitmap[1] << endl;
	code.getline(pad,100);
	code.read((char *)bitmap,length / 8 + 1);
	//cout << hex << bitmap[1] << endl;
	code.clear();
	
	string key;
	int val;
	Huffman >> val;
	while(!Huffman.eof())
	{
		Huffman >> pad2;
		Huffman >> key;
		//cout << key << endl;
		//cout << val << endl;
		test[hash(key)].key = key;
		test[hash(key)].val = val;
		Huffman >> val;
	}
	
	string m;
	char n;
	for(int i = 0;i < length;i++)
	{
		if(getBit(bitmap,i))
		{
			m += '1';
		}
		else
		{
			m += '0';
		}
		if(test[hash(m)].key.size())
		{
			n = test[hash(m)].val;
			//cout << "str:" << m << "\t\tval: " << (char)n << endl; 
			decodes << n;
			m = "";
		}
	}
	
	return;
}
//通过Huffman编码规则解密编码后的文件 

int main()
{
	Init();
	
	count();
	create();
	encode();
	decode();
	
	Fini(); 
	
	return 0;
}
