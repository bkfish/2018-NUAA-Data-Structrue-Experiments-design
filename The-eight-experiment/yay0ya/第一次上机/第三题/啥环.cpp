#include<iostream>
using namespace std;
typedef struct Person
{
    int data;
    struct Person *next;
}node;
int main() {
    node *L, *r, *s;
    L = new node;
    r = L;
    int m, n, i;
    cin >> n >> m;
    for (i = 1; i <= n; i++) {
        s = new node;
        s->data = i;
        r->next = s;
        r = s;
    }
    r->next = L->next;
    node *p;
    p = L->next;
    delete L;
    while (p->next != p) {
        for (i = 1; i < m - 1; i++) {
            p = p->next;
        }
        cout << p->next->data << "->";
        p->next = p->next->next;
        p = p->next;
    }
    cout << p->data << endl;
    return 0;
}

