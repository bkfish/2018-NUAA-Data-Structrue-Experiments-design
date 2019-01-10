/*2、公共钥匙盒（必做）（线性表，栈，队列）
[问题描述]
　　有一个学校的老师共用N个教室，按照规定，所有的钥匙都必须放在公共钥匙盒里，老师不能带钥匙回家。每次老师上课前，都从公共钥匙盒里找到自己上课的教室的钥匙去开门，上完课后，再将钥匙放回到钥匙盒中。
　　钥匙盒一共有N个挂钩，从左到右排成一排，用来挂N个教室的钥匙。一串钥匙没有固定的悬挂位置，但钥匙上有标识，所以老师们不会弄混钥匙。
　　每次取钥匙的时候，老师们都会找到自己所需要的钥匙将其取走，而不会移动其他钥匙。每次还钥匙的时候，还钥匙的老师会找到最左边的空的挂钩，将钥匙挂在这个挂钩上。如果有多位老师还钥匙，则他们按钥匙编号从小到大的顺序还。如果同一时刻既有老师还钥匙又有老师取钥匙，则老师们会先将钥匙全还回去再取出。
　　今天开始的时候钥匙是按编号从小到大的顺序放在钥匙盒里的。有K位老师要上课，给出每位老师所需要的钥匙、开始上课的时间和上课的时长，假设下课时间就是还钥匙时间，请问最终钥匙盒里面钥匙的顺序是怎样的？
[基本要求]
输入格式
　　输入的第一行包含两个整数N, K。
　　接下来K行，每行三个整数w, s, c，分别表示一位老师要使用的钥匙编号、开始上课的时间和上课的时长。可能有多位老师使用同一把钥匙，但是老师使用钥匙的时间不会重叠。
　　保证输入数据满足输入格式，你不用检查数据合法性。
输出格式
　　输出一行，包含N个整数，相邻整数间用一个空格分隔，依次表示每个挂钩上挂的钥匙编号。
样例输入
5 2
4 3 3
2 2 7
样例输出
1 4 3 2 5
样例说明
　　第一位老师从时刻3开始使用4号教室的钥匙，使用3单位时间，所以在时刻6还钥匙。第二位老师从时刻2开始使用钥匙，使用7单位时间，所以在时刻9还钥匙。
　　每个关键时刻后的钥匙状态如下（X表示空）：
　　时刻2后为1X345；
　　时刻3后为1X3X5；
　　时刻6后为143X5；
　　时刻9后为14325。
课程设计要求：
（1）要求从文本文件中输入；
（2）根据时间进程，将取走钥匙和归还钥匙分别视为事件，放入队列中，然后通过每个事件的先后发生对钥匙盒的状态进行变更；
（3）严格按照要求的输入输出格式进行数据的输入、输出（训练CSP考试中的格式化输入输出的正确性）；
（4）选做：通过图形界面来显示钥匙盒的即时状态，以及事件队列的状态。*/
#include<cstdio>
#include<cstdlib>
#include<windows.h> 
#include<iostream>
#include<queue>
//想写一个计时器 
using namespace std;
int timecount=0; 
typedef struct {
	int keyId;
	int time;
}Key;

// 全局变量 
FILE *fp;
char fileName[] = "input.txt";


// 打开文件 
void fileOpen(char *method) {
	if((fp=fopen(fileName,method)) == NULL) {
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// 关闭文件 
void fileClose() {
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
} 

// 显示图形界面
void ShowBox(int n, int *box, int time, int *key) {
	system("cls");
	cout<<"正在盒子里的钥匙"<<endl; 
	cout<<"                          "; 
	for (int i=1; i<=n; i++) {
		printf("-----");
	}
	printf("\n");
	cout<<"                          "; 
	for (int i=1; i<=n; i++) {
		if (box[i]) printf("| %2d ",box[i]);
		else printf("|    ");
	}
	printf("|\n");
	cout<<"                          "; 
	for (int i=1; i<=n; i++) {
		printf("-----");
	}
	printf("\n\n");
	cout<<"在老师手上的钥匙"<<endl; 
	cout<<"                          "; 
	for (int i=1; i<=n; i++) {
		if (key[i] == 0) printf(" %d ", i);
	}
	printf("\n\n\n\n\n\n\n");
	while(time>0)
	{
		Sleep(1000);
		time--;
		cout<<"                    第："<<timecount++<<"秒"<<endl;
	}


} 

int main() {
	fileOpen("r");
	
	int n = 0, k = 0;
	fscanf(fp, "%d%d", &n, &k);
	
	int w = 0, s = 0, c = 0;
	Key *borrow = (Key*)malloc(sizeof(Key) * k), *ret = (Key*)malloc(sizeof(Key) * k);//借出和返回的储存
	for (int i=0; i<k; i++) {
		fscanf(fp, "%d%d%d", &w, &s, &c);
		// 借出的钥匙号和时间 
		borrow[i].keyId = w;
		borrow[i].time = s;
		// 归还的钥匙号和时间 
		ret[i].keyId = w;
		ret[i].time = s + c;
	}
	
	// 对借出和归还的钥匙，根据时间从小到大排序 
	for (int i=0; i<k; i++) {
		for (int j=i; j<k; j++) {
			if (borrow[j].time < borrow[i].time || (borrow[j].time == borrow[i].time && borrow[j].keyId < borrow[i].keyId)) {
				Key temp = borrow[j];
				borrow[j] = borrow[i];
				borrow[i] = temp;
			}
			if (ret[j].time < ret[i].time || (ret[j].time == ret[i].time && ret[j].keyId < ret[i].keyId)) {
				Key temp = ret[j];
				ret[j] = ret[i];
				ret[i] = temp;
			}
		}
	}

	// 将事件放进队列中 
	queue<Key> q;
	int i = 0, j = 0;
	while (i<k && j<k) {
		if (borrow[i].time < ret[j].time) {
			q.push(borrow[i]);
			i++; 
		}
		else if (borrow[i].time > ret[j].time) {
			q.push(ret[j]);
			j++;
		}
		else {
			q.push(ret[j]);
			j++;
		}
	}
	while (i<k) {
		q.push(borrow[i]);
		i++;
	}
	while (j<k) {
		q.push(ret[j]);
		j++;
	}
	
	// 对key钥匙和box钥匙盒数组初始化。key数组：下标为编号，值为在box中的位置 
	int key[n+1], box[n+1]; 
	for (int i=1; i<=n; i++) {
		box[i] = i;
		key[i] = i;
	}
	// 根据队列进行事件安排
	int time = 0;
	while (!q.empty()) {
		Key cur = q.front();
		q.pop();
		
		ShowBox(n, box, cur.time - time, key);
		time = cur.time;
		
		// 如果该钥匙已经发在一个位置了，就取出 
		if (key[cur.keyId]) {
			box[key[cur.keyId]] = 0;
			key[cur.keyId] = 0;
		}
		else {
			for (int i=1; i<=n; i++) {
				if (box[i] == 0) {
					key[cur.keyId] = i;
					box[i] = cur.keyId;
					break;
				}
			}
		}
	}
	ShowBox(n, box, 1, key);

	
	printf("\n所有老师已经下课\n");
	
	free(borrow);
	free(ret);
	fileClose();
	system("pause"); 
}
