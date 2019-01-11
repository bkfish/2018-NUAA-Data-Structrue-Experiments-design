#include<cstdio>
#include<cstdlib>
#include<windows.h> 
#include<iostream>
#include<queue>

using namespace std;

typedef struct {
	int keyId;
	int time;
}Key;

int main() {
	
	int n = 0, k = 0;
	scanf("%d%d", &n, &k);
	
	int w = 0, s = 0, c = 0;
	Key *borrow = (Key*)malloc(sizeof(Key) * k), *ret = (Key*)malloc(sizeof(Key) * k);
	for (int i=0; i<k; i++) {
		scanf("%d%d%d", &w, &s, &c);
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
	
	// for (int i=0; i<k; i++) printf("%d %d\n", borrow[i].keyId, borrow[i].time);
	// for (int i=0; i<k; i++) printf("%d %d\n", ret[i].keyId, ret[i].time);
	
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
		
		//ShowBox(n, box, cur.time - time, key);
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
	for (int i=1; i<=n; i++) printf("%d ", box[i]);

	
	free(borrow);
	free(ret);
}
