#include <stdio.h>
#include <stdlib.h>

//单向链表定义
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *LinkList;

/* 链表创建 */
LinkList CreatLink(int num)
{
    int data;

    //p指向当前链表中最后一个结点，q指向准备插入的结点。
    LinkList head = NULL, rearNode = NULL, newNode;

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data);
        newNode = (LinkList)malloc(sizeof(LNode));
        newNode -> data = data;
        newNode -> next = NULL;
        if (i == 0)                 //头结点
        {
            head = newNode;
        }
        else
        {
            rearNode -> next = newNode;
        }
        rearNode = newNode;
    }
    return head;
}

LinkList LinkInsertSort(LinkList head)
{
    LinkList originList, nodeScan, preNode, newNode;

    if (head == NULL)
        return head;

    //分离原链表为有序和无序链表
    originList = head -> next;

    //有序链表的第一个节点L指向节点
    head -> next = NULL;

    //遍历无序链表
    while (originList)
    {
        newNode = originList;
        originList = originList -> next;

        preNode = NULL;

        //寻找元素插入位置
        for (nodeScan = head; (nodeScan != NULL) && (nodeScan -> data < newNode -> data); preNode = nodeScan, nodeScan = nodeScan -> next);

        //循环退出表示查找到节点插入的位置
        if (nodeScan == head)
            head = newNode;
        else
            preNode -> next = newNode;

        newNode -> next = nodeScan;
    }

    return head;
}
/* 链表输出函数 */
void PrintLink(LinkList head)
{
    LinkList nodeScan;
    for (nodeScan = head; nodeScan ;nodeScan = nodeScan->next)
    {
        printf("%-3d ", nodeScan->data);
    }
}
int main()
{
    LinkList head;
    int listLen;
    printf("输入链表节点个数：\n");
    scanf("%d", &listLen);
    printf("输入元素值：\n");

    head = CreatLink(listLen);

    head = LinkInsertSort(head);
    printf("排序后：\n");
    PrintLink(head);
    putchar('\n');
    return 0;
}

