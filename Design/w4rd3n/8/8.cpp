#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include<string>
#include<time.h>

using namespace std;

fstream file; 

string sfz[20] = {
	"666888200001010001","666888200001010002","666888200001010003","666888200001010004","666888200001010005",
	"666888200001010006","666888200001010007","666888200001010008","666888200001010009","666888200001010000",
	"666888200001010010","666888200001010020","666888200001010030","666888200001010040","666888200001010050",
	"666888200001010060","666888200001010070","666888200001010080","666888200001010090","666888200001010100",
};

string name[20] = {
	"cws","bbb","ccc","aaa","ddd","eee","fff","ggg","hhh","jjj",
	"www","sss","zzz","xxx","rrr","ttt","yyy","uuu","iii","ooo",
};

typedef struct Record
{
    string id;
	//身份证号
    string name;
    //姓名
    string flyId;
    //航班号
    string flyDate;
    //航班日期
    int distance;
    //里程
    int conflict;
    //冲突数量 
    struct Record * next;
    //单向链表 
}record;
//记录 

record records[10000];
record hash1[10000];
record * hash2[10000];

typedef struct PassengerRecord
{
    string id;
    //身份证号 
    string name;
    //姓名 
    int allDistance;
    //里程数统计 
    int rate;
    //乘机频率 
}passengerRecord;
//乘客记录 

void setData()
{
	file.open("data.txt",ios::out);
	
	string id = "66688820000101";
	
	srand(time(0));
	
	for(int i = 0;i < 200;i++)
	{
		int j = rand() % 20;
		file << sfz[j] << endl;
		file << name[j] << endl;
		file << "NH" << rand() % 200 << endl;
		file << "2019" << rand() % 12 + 1 << rand() % 28 + 1 << endl;
		file << rand() % 3000 + 1000 << endl;
	}
	
	file.close();
	
	return;
}

int getData()
{
    file.open("data.txt",ios::in);
    
    if(!file.is_open())
    {
        cout << "Error open file data.txt" << endl;
        exit(1);
    }
    
    int num = 1;
    
    while(!file.eof())
    {
        getline(file,records[num].id);
        getline(file,records[num].name);
        getline(file,records[num].flyId);
        getline(file,records[num].flyDate);
        file >> records[num].distance;
        file.ignore();
        num++;
    }
    
    file.close();
    
    return num - 1;
}

void Hash1(int num)
//开发定址 
{
	for(int i = 1;i <= num;i++)
	{
		int x = 1,y;
		int conflict = 0;
		string id = records[i].id;
		//用于处理碰撞
	 
		for(int j = 0;j < id.size();j++)
		{
			x *= id[j];
			x -= id[j] / 2;
			x %= 10000;
		}
		y = x;
	
		while(hash1[x].id.size())
		//如果发生碰撞，则向后移一位 
		{
			x++;
			conflict++;
		
			if(x > 9999)
			{
				x %= 10000;
			}
		
			if(x == y)
			{
				cout << "Error hash,memery is out!!!\n";
				exit(0);
			}
			//防止溢出 
		}
		
		hash1[x].id = records[i].id;
		hash1[x].name = records[i].name;
		hash1[x].flyId = records[i].flyId;
		hash1[x].flyDate = records[i].flyDate;
		hash1[x].distance = records[i].distance;
		hash1[x].conflict = conflict;
	}
	
	return;
}

void Hash2(int num)
//链地址法
{
    for(int i = 1;i <= num;i++)
    {
        int x = 1;
		int conflict = 0;
		string id = records[i].id;
		//用于处理碰撞
	 
		for(int j = 0;j < id.size();j++)
		{
			x *= id[j];
			x -= id[j] / 2;
			x %= 10000;
		}
		
        record * now = hash2[x]->next;
        record * pre = hash2[x];
        
        while(now && !(now->id == id))
        {
            pre = now;
            now = now->next;
            conflict++;
        }
        
        record * temp = new record();
        temp->id = records[i].id;
        temp->name = records[i].name;
        temp->flyId = records[i].flyId;
        temp->flyDate = records[i].flyDate;
        temp->distance = records[i].distance;
        temp->conflict = conflict;
        
        temp->next = now;
        pre->next = temp;
		//将temp插入到pre指针和now指针中间
    }
    
    return;
}

void search1(string id)
{
    int x = 1;
	 
	for(int i = 0;i < id.size();i++)
	{
		x *= id[i];
		x -= id[i] / 2;
		x %= 10000;
	}
	
	while(hash1[x].id.size())
	//如果发生碰撞，则向后移一位 
	{
		if(hash1[x].id == id)
		{
			cout << "Id:" << hash1[x].id << endl;
    		cout << "name:" <<hash1[x].name << endl;
    		cout << "flyId:" << hash1[x].flyId <<endl;
    		cout << "flyDate:" << hash1[x].flyDate << endl;
    		cout << "distance:" << hash1[x].distance << endl << endl;
		}
		
		x++;
	}
	
	return;
}

void search2(string id)
{
	int x = 1;
	
    for(int i = 0;i < id.size();i++)
	{
		x *= id[i];
		x -= id[i] / 2;
		x %= 10000;
	}
	
    record * now = hash2[x]->next;
    record * pre = hash2[x];
    
    while(now  && now->id != id)
    {
        pre = now;
        now = now->next;
    }
    
    while(now && now->id == id)
    {
        cout << "Id:" << now->id << endl;
        cout << "name:" << now->name << endl;
        cout << "flyId:" << now->flyId << endl;
        cout << "flyDate:" << now->flyDate << endl;
        cout << "distance:" << now->distance << endl << endl;
        now = now->next;
    }
    
    return;
}

int main()
{
	string aaa;
	
	cout << "Do you want to setData repeat?(Y or N)";
	cin >> aaa;
	if(aaa == "Y")
	{
		setData();
	}
	
    int conflictCount = 0;
    
    for(int i = 0;i < 10000;i++)
    {
        hash1[i].distance = -1;
        hash1[i].conflict = 0;
        hash2[i] = (record *)malloc(sizeof(record));
        hash2[i]->next = NULL;
        hash2[i]->conflict = 0;
    }
    //初始化数据
	 
    int num;
	
	num = getData();
    
    Hash1(num);
    Hash2(num);
    
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------开放定址-----------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    
    for(int i = 0;i < 10000;i++)
    {
        if(hash1[i].distance != -1)
        {
           cout << "i:" << setw(4) << i << ".  name:" << hash1[i].name << ".  flyId:" << setw(16) << hash1[i].flyId << endl;
           cout << "conflict:" << hash1[i].conflict <<endl;
           if(hash1[i].conflict)
           {
           		conflictCount++;
		   }
        }
    }
    
    cout << "conflictCount:" << conflictCount << endl;
    cout << endl;
    
    int Personcount = 0;
    
    passengerRecord Person_record[num + 1];
    
    for(int i = 1;i <= num;i++)
    {
        Person_record[i].allDistance = 0;
        Person_record[i].rate = 0;
    }
    
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------链地址法-----------------------------------------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    
    conflictCount = 0;
    
    for(int i = 1;i < 10000;i++)
    {
        if(hash2[i]->next)
        {
            Personcount++;
            record * now = hash2[i]->next;
            Person_record[Personcount].id = now->id;
            Person_record[Personcount].name = now->name;
            while(now)
            {
            	if(now->id == Person_record[Personcount].id)
            	{
            		Person_record[Personcount].allDistance += now->distance;
                	Person_record[Personcount].rate++;
				}
				else
				{
					Personcount++;
					Person_record[Personcount].id = now->id;
            		Person_record[Personcount].name = now->name;
            		Person_record[Personcount].allDistance += now->distance;
                	Person_record[Personcount].rate++;
				}
                
                cout << "i:" << setw(4) << i << ".  name:" << now->name << ".  flyId:" << setw(16) << now->flyId << endl;
           		cout << "conflict:" << now->conflict <<endl;
           		
                if(now->conflict)
           		{
           			conflictCount++;
		   		}
		   		
                now = now->next;
            }
        }
    }
    
    cout << "conflictCount:" << conflictCount << endl;
    cout << endl;
    cout << "Personcount:" << Personcount << endl;
    
    for(int i = 1;i <= Personcount;i++)
    {
        cout << "id:" << setw(4) << Person_record[i].id << ".  name:" << setw(10) << Person_record[i].name;
        cout << ".  allDistance:" << setw(6) << Person_record[i].allDistance << ".  rate:" << Person_record[i].rate <<endl;
    }
    
    string id;
    
    while(1)
    {
        cout << "input the id that you search(quit by \"quit\")" << endl;
        cin >> id;
        if(id != "quit")
        {
        	search1(id);
		}
        else
        {
        	break;
		}
    }
    
    int choose;
    
    while(1)
    {
        cout << endl << "Please input the standard data of vip" << endl;
        cout << "1:allDistance" << endl;
        cout << "2:rate" <<endl;
        cout << "3:exit" << endl;
        
        cin >> choose;
        
        if(choose == 1)
        {
            int allDistance = 0;
            cout << "Please input the min allDistance of vip" <<endl;
            cin >> allDistance;
            cout << "Here are vip:" << endl;
            for(int i = 1;i <= Personcount;i++)
            {
                if(Person_record[i].allDistance >= allDistance)
                {
                    cout << "id:" << setw(4) << Person_record[i].id << ".  name:" << setw(10) << Person_record[i].name;
        			cout << ".  allDistance:" << setw(6) << Person_record[i].allDistance << ".  rate:" << Person_record[i].rate <<endl;
                }
            }
        }
        else if(choose == 2)
        {
            int rate = 0;
            cout << "Please input the min rate of vip" <<endl;
            cin >> rate;
            cout << "Here are vip:" << endl;
            for(int i = 1;i <= Personcount;i++)
            {
                if(Person_record[i].rate >= rate)
                {
                    cout << "id:" << setw(4) << Person_record[i].id << ".  name:" << setw(10) << Person_record[i].name;
        			cout << ".  allDistance:" << setw(6) << Person_record[i].allDistance << ".  rate:" << Person_record[i].rate <<endl;
                }
            }
        }
        else if(choose == 3)
        {
        	return 0;
		}
		else
		{
			cout << "valid choice" << endl;
		}
    }
    
    for(int i = 0;i < 10000;i++)
    {
        free(hash2[i]);
    }
    
    return 0;
}
