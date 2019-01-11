#include"BTree.h"

#define BMT_TEST
#ifdef BMT_TEST
//BMT: 10 45 24 53 90 3 37 50 61 70 100
int main(void)
{
    BTree t;

    int n;
    cout << "输入数的个数：" << endl;
    cin >> n;
    cout << "输入各个数的值：" << endl;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        t.insert_BTree(temp);
    }
    Node * head = t.gethead();
    t.WalkThrough(head);

    int key;
    cout << "输入需要删除的值：" << endl;
    cin >> key;
    t.Delete_BTree(key);
    head = t.gethead();
    t.WalkThrough(head);

    return 0;
}
#endif
