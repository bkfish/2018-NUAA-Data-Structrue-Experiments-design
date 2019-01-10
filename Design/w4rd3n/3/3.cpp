#include<iostream>
#include<fstream>
#include<cstring>
#include<string> 
#include<cstdlib>

using namespace std;

typedef struct Json
{
	bool flag;
	//标识是不是OBJECT 
	string key;
	//键 
	string value;
	//值 
}json;
//映射键值的结构体 

fstream file;
int n,m;
json test[10000];
//hash映射数组 

string nowKey;
string tempKey;
string nowValue;
//现在正在处理的key和value

int flag = 0;
//标识现在处理的是key还是value

int hash(char * p)
{
	int x = 1,y;
	string key = p;
	//用于处理碰撞
	 
	for(;*p;p++)
	{
		x *= *p;
		x -= *p / 2;
		x %= 10000;
	}
	y = x;
	
	while(test[x].key.size() && !(test[x].key == key.substr(5,1000)))
	//如果发生碰撞，则向后移一位 
	{
		//cout << "hash(" << test[x].key << "):" << x << endl;
		x++;
		x %= 10000;
		if(x == y)
		{
			cout << "Error hash,memery is out!!!\n";
			exit(0);
		}
		//防止溢出 
	}
	//cout << "hash(" << test[x].key << "):" << x << endl;
	
	return x;
}
//hash函数 

void toJson(char * line)
{
	while(*line)
	{
		if(*line == '{')
		//对象的开始 
		{
			if(nowKey.size())
			//改变父节点的字符串 
			{
				nowKey = tempKey;
				nowKey += '.';
				tempKey = nowKey;
				flag ^= 1;
			}
			else
			//第一个'{'字符特殊处理 
			{
				nowKey = "json."; 
				tempKey = nowKey;
			}
		}
		else if(*line == '"')
		//处理字符串 
		{
			if(!flag)
			//处理key 
			{
				line++;
				while(*line != '"')
				{
					if(*line == '\\')
					{
						line++;
					}
					tempKey += *line;
					line++;
				}
				//cout << tempKey << ":";
			}
			else
			//处理value 
			{
				line++;
				while(*line != '"')
				{
					if(*line == '\\')
					{
						line++;
					}
					nowValue += *line;
					line++;
				}
				//cout << nowValue << "\n";
			}
		}
		else if(*line == ':' || *line == ',' || *line == '}')
		//转变和结束 
		{
			flag ^= 1;
			if(*line == ',' || *line == '}')
			//保存键值映射到json数组 
			{
				test[hash((char *)tempKey.c_str())].key = tempKey.substr(5,1000);
				if(!nowValue.size())
				{
					test[hash((char *)tempKey.c_str())].value = "OBJECT";
					test[hash((char *)tempKey.c_str())].flag = 1;
				}
				else
				{
					test[hash((char *)tempKey.c_str())].value = nowValue;
					test[hash((char *)tempKey.c_str())].flag = 0;
				}
				//cout << test[hash((char *)tempKey.c_str())].key << ":" << test[hash((char *)tempKey.c_str())].value << endl;
				if(*line == ',')
				{
					tempKey = nowKey;
				}
				nowValue = "";
			}
			if(*line == '}')
			//结束一个对象，修改父节点字符串 
			{
				flag ^= 1;
				if(nowKey == "json.")
				{
					nowKey = "";
					tempKey = nowKey;
				}
				else
				{
					nowKey = nowKey.substr(0,nowKey.rfind("."));
					tempKey = nowKey;
					//cout << tempKey << endl;
					nowKey = nowKey.substr(0,nowKey.rfind(".") + 1);
					nowValue = "";
					//cout << nowKey << endl;
				}
			}
		}
		
		line++;
	}
	
	return;
}
//将文本信息处理成json结构体 

void getValue(char * line)
{
	string s = "json.";
	
	s += line;
	
	if(test[hash((char *)s.c_str())].value.size())
	{
		if(!test[hash((char *)s.c_str())].flag)
		{
			cout << "STRING ";
		}
		cout << test[hash((char *)s.c_str())].value << endl;
	}
	else
	{
		cout << "NOTEXIST" << endl;
	}
	
	return;
}
//通过json结构体获得当前查询的value  

int main()
{
	char line[1000];
	file.open("3.txt",ios::in);
	
	file >> n >> m;
	file.getline(line,1000);
	//丢弃空行 
	while(n--)
	{
		file.getline(line,1000);
		//cout << line << endl;
		
		toJson(line);
		//处理当前行 
	}
	
	while(m--)
	{
		file.getline(line,1000);
		
		getValue(line);
		//处理当前查询 
	} 
	
	return 0;
}
