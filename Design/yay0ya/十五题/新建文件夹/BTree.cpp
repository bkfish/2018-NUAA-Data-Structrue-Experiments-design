#include"BTree.h"
BTree::BTree() {
    this->head = NULL;
}
//结点中，查找关键字序列，是否存在k，私有方法
int BTree::search(Node * & t,KeyType k) {
    int i = 0;
    for (int j = 1; j <= t->keynum; ++j) {
        if (t->key[j] <= k) {
            i = j;
        }
    }
    return i;
}

//遍历整个树，查找对应的关键字，公有方法，
bool BTree::searchKey_BTree(KeyType k, Node * & recNode, int & recIdx) {
    if (!head) {
        //cerr << "树为空" << endl;
        return false;
    }
    Node * p = head;
    Node * q = NULL;
    bool found = false;
    int i=0;
    while (p && !found) {
        i = this->search(p, k); //记住i返回两种情况：第一种是找到对应的关键字
        //第二次是找到了最后一个小于k的关键字下标（主要作用与插入时）
        if (i > 0 && p->key[i] == k) {
            //找到了记录结点和结点中关键字的下标
            recIdx = i;
            recNode = p;
            return true;
        }//endif
        else {
            recNode = p;         // 记录p的值，方便返回
            recIdx = i;
            p = p->ptr[recIdx]; // 查找下一个结点，
        }//endelse

    }//endw
    return false;
}
//这是在结点的关键字序列中，插入一个而关键字，私有方法
void BTree::insert(Node * & t, int i, KeyType k, Node * rhs) {
    //我们需要把关键字序列往后移动，然后插入新的关键字
    for (int j = t->keynum; j >= i + 1; --j) {
        t->key[j + 1] = t->key[j];
        t->ptr[j + 1] = t->ptr[j];
    }
    //插入新的关键字
    t->key[i + 1] = k;
    t->ptr[i + 1] = rhs;
    ++t->keynum;
}

//对对应的结点进行分裂处理,对t结点进行分裂处理，私有方法
bool BTree::split(Node * & t, int s, Node * & rhs, KeyType & midk) {
    rhs = new Node;
    //rhs为新建的结点，用于保存右半部分的。
    if (!rhs) {
        exit(0);
        return false;
    }
    //我们们把t分裂的，所以rhs是t的兄弟结点，有相同的父母
    rhs->parent = t->parent;

    //其中关键字序列的中间值为
    midk = t->key[s];
    t->key[s] = 0;
    //这个通过画图，就可以知道rhs的0号孩子的指针，就是t的s号结点指针
    rhs->ptr[0] = t->ptr[s];

    //如果原来的t的s号孩子指针，现在的rhs的0号孩子指针不为空，则需要改变孩子的的父亲结点
    if (rhs->ptr[0]) {
        rhs->ptr[0]->parent = rhs;
    }//endif
    t->ptr[s] = NULL;
    for (int i = 1; i <= m - s; ++i) {
        //现在是把右半部分全部复制到到rhs中
        rhs->key[i] = t->key[s + i]; t->key[s + i] = 0;
        rhs->ptr[i] = t->ptr[s + i]; t->ptr[s + i] = NULL;
        //理由和刚才的理由一样
        if (rhs->ptr[i]) {
            rhs->ptr[i]->parent = rhs;
        }//endif
    }//endfor
    rhs->keynum = m - s;
    t->keynum = s - 1;
    return true;
}
//新建一个新的结点，私有方法
bool BTree::newroot(Node * & t, Node * & lhs, KeyType midk, Node * & rhs) {
    Node * temp = new Node;
    if (!temp) {
        exit(0);
        return false;
    }
    temp->keynum = 1;
    temp->key[1] = midk;

    temp->ptr[0] = lhs;
    //左孩子不为空
    if (temp->ptr[0]) {
        temp->ptr[0]->parent = temp;
    }
    temp->ptr[1] = rhs;
    //右孩子不为空
    if (temp->ptr[1]) {
        temp->ptr[1]->parent = temp;
    }
    t = temp;
    return true;

}
//插入一个k（public方法）
bool BTree::insert_BTree(KeyType k) {
    Node * curNode = NULL;
    int preIdx = 0;
    if (this->searchKey_BTree(k, curNode, preIdx)) {
        cout << "关键已经存在" << endl;
        return false;
    }
    else {
        //没有找到关键字
        KeyType curk = k;
        Node * rhs = NULL;
        bool finished = false;
        while (!finished && curNode) {
            //不管是否合法，直接先插入刚才找到的那个关键字序列中
            this->insert(curNode, preIdx, curk, rhs);
            if (curNode->keynum < m) {//满足条件，直接退出
                finished = true;
            }
            else {
                int s = (m + 1) / 2;  //s为中间值的下标
                if (!this->split(curNode, s, rhs, curk)) {
                    //分裂失败，直接返回
                    return false;
                }
                if (curNode->parent == NULL) {
                    //如果curNode已经是根节点了，则可以直接退出了
                    break;
                }
                else {
                    //如果有那个父亲结点的话，此时curk指向的是原来这个结点中间值
                    //所以需要和父亲结点融合
                    curNode = curNode->parent;
                    preIdx = this->search(curNode, curk);
                }
            }
        }
        //如果head为空树，或者根结点已经分裂为结点curNode和rhs了，此时是肯定到了
        //根结点了
        if (!finished && !this->newroot(head, curNode, curk, rhs)) {
            cerr << "failed to create new root" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

//删除结点k，找到合适的结点（public方法）
bool BTree::Delete_BTree(KeyType k) {
    Node * curNode = NULL;
    int curIdx = 0;
    if (this->searchKey_BTree(k, curNode, curIdx)) {
        this->Delete(curNode, curIdx);
        return true;
    }
    else {
        return false;
    }
}

//删除对应的进入结点，去删除关键字
void BTree::Delete(Node * curNode, int curIdx) {
    //curIdx不合法法时，直接返回
    if (curIdx<0 || curIdx>curNode->keynum) {
        return;
    }
    while (true) {//这里的步骤不是很清楚，等下来讨论
        //此时说明我们是处于非叶子结点
        if (curNode->ptr[curIdx - 1] && curNode->ptr[curIdx]) {

            //使用右子树中最小的关键字替换对应当前的关键的，然后删除那个最小的关键字
            Node * p1 = curNode->ptr[curIdx];
            while (p1->ptr[0]) {
                p1 = p1->ptr[0];
            }
            int res = p1->key[1];
            this->Delete_BTree(p1->key[1]);

            curNode->key[curIdx] = res;

            break;
        }
        else if (!curNode->ptr[curIdx - 1] && !curNode->ptr[curIdx])
        {   // is leaf
            for (int i = curIdx; i <= curNode->keynum; ++i) {
                curNode->key[i] = curNode->key[i + 1];
                // all ptr are NULL , no need to move.
            }//end for.
            --curNode->keynum;
            this->DeleteBalance(curNode);
            break;
        }
        else { //debug
            cerr << "Error" << endl;
        }
    }//endw
}
//删除对应关键字后，我们需要对删除后的树进行调整
void BTree::DeleteBalance(Node * curNode) {
    int lb = (int)m / 2;  
    Node * parent = curNode->parent;
    while (parent && curNode->keynum < lb) {//说明删除了关键字后，原来的那个结点已经不
        //符合B-树的最小结点要求，这个不懂可以回去看看条件
        int idx = 0;
        //找到curNode在其父亲节点中的位置
        for (int i = 0; i <= parent->keynum; ++i) {
            if (parent->ptr[i] == curNode) {
                idx = i;
                break;
            }
        }
        Node * lsilb = NULL; Node * rsilb = NULL;
        if (idx - 1 >= 0) {//如果当前结点有左兄弟
            lsilb = parent->ptr[idx - 1];
        }
        if (idx + 1 <= parent->keynum) {//说明当前结点有右兄弟
            rsilb = parent->ptr[idx + 1];
        }
        //只要右兄弟存在，而且满足rsilb->keynum > lb，即是删除的调整的情况2
        if (rsilb && rsilb->keynum > lb) {
            this->RotateLeft(parent, idx, curNode, rsilb);
            break;
        }//如果右兄弟不满足，而左兄弟满足，同样可以
        else if (lsilb && lsilb->keynum > lb) {
            this->RotateRight(parent, idx, curNode, lsilb);
            break;
        }//如果左右兄弟都不满足，那就是情况3了，
        else {
            //合并到左兄弟，
            if (lsilb)
                this->Merge(parent, idx, lsilb, curNode);
            else//没有左兄弟，合并到右兄弟
                this->Merge(parent, idx + 1, curNode, rsilb);
            // potentially causing deficiency of parent.
            curNode = parent;
            parent = curNode->parent;
        }
    }
    if (curNode->keynum == 0) {
        // root is empty,此时树为空
        head = curNode->ptr[0];
        delete curNode;
    }//endif
}
void BTree::RotateLeft(Node * parent, int idx, Node * cur, Node * rsilb) {
    //这个是在右兄弟存在的情况下，而且满足rsilb->keynum > lb，则我们需要从把
    //右兄弟结点中的最小关键字移动到父亲结点，而父亲结点中小于该右兄弟的关键字的关键字
    //就要下移到刚刚删除的那个结点中。

    //父亲结点中某个结点下移
    cur->key[cur->keynum + 1] = parent->key[idx + 1]; 
    cur->ptr[cur->keynum + 1] = rsilb->ptr[0];  //
    if (cur->ptr[cur->keynum + 1]) {
        cur->ptr[cur->keynum + 1]->parent = cur;    
    }
    rsilb->ptr[0] = NULL;

    ++cur->keynum;

    parent->key[idx + 1] = rsilb->key[1];
    rsilb->key[idx] = 0;
    //右兄弟上移一个结点到父亲结点，
    for (int i = 0; i <= rsilb->keynum; ++i) {//删除最靠右的那个结点
        rsilb->key[i] = rsilb->key[i + 1];
        rsilb->ptr[i] = rsilb->ptr[i + 1];
    }
    rsilb->key[0] = 0;
    --rsilb->keynum;
}
void BTree::RotateRight(Node * parent, int idx, Node * cur, Node * lsilb) {

    //这个是在左兄弟存在的情况下，而且满足lsilb->keynum > lb，则我们需要从把
    //左兄弟结点中的最大关键字移动到父亲结点，而父亲结点中大于该左兄弟的关键字的关键字
    //就要下移到刚刚删除的那个结点中。

    //因为是在左边插入
    for (int i = cur->keynum; i >= 0; --i) {//因为左边的都比右边小，所以要插入第一个位置
        cur->key[i + 1] = cur->key[i];
        cur->ptr[i + 1] = cur->ptr[i];
    }
    //在第一个位置插入父亲结点下移下来的结点
    cur->key[1] = parent->key[idx];
    cur->ptr[0] = lsilb->ptr[lsilb->keynum];

    if (cur->ptr[0])
        cur->ptr[0]->parent = cur;
    lsilb->ptr[lsilb->keynum] = NULL;
    ++cur->keynum;

    // from lsilb to parent.
    parent->key[idx] = lsilb->key[lsilb->keynum];
    lsilb->key[lsilb->keynum] = 0;
    --lsilb->keynum;

}
void BTree::Merge(Node * parent, int idx, Node * lsilb, Node * cur) {

    //函数实现都是往lsilb上合并，首先是先把cur中的剩余部分，全部合到左兄弟中个，
    for (int i = 0; i <= cur->keynum; ++i) {
        lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
        lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
        if (lsilb->ptr[lsilb->keynum + 1 + i])
            lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
   }
    //然后再把父亲结点中的idx对应的内容添加到左兄弟
    lsilb->key[lsilb->keynum + 1] = parent->key[idx];
    lsilb->keynum = lsilb->keynum + cur->keynum + 1;
    delete cur;
    //然后更新我们的父亲结点内容
    for (int i = idx; i <= parent->keynum; ++i) {
        parent->key[i] = parent->key[i + 1];
        parent->ptr[i] = parent->ptr[i + 1];
    }//end for.
    --parent->keynum;
}
void BTree::Destroy(Node * & T) { //是否空间
    if (!T) { return; }
    for (int i = 0; i <= T->keynum; ++i)
        Destroy(T->ptr[i]);
    delete T;
    T = NULL;
    return;
}
void BTree::WalkThrough(Node * &T) {
    if (!T) return;
    static int depth = 0;
    ++depth;
    int index = 0;

    bool running = true;

    while (running) {
        int ans = 0;
        if (index == 0) {
            ans = 2;
        }
        else {
            cout << "树的深度：" << depth << endl;
            cout << "现在的结点: " << (void*)T << ";  "
                << "结点上值为: " << T->keynum << "; " << endl;
            cout << "序号是: " << index << ";  值为: " << T->key[index] << endl;

            do {
                cout<< "1.前值; 2.后值; 3.左孩子; 4.右孩子; 5.返回上一层 " << endl;
                cin>>ans;
                if (1 <= ans && ans <= 5)
                    break;
            } while (true);
        }


        switch (ans) {
        case 1:
            if (index == 1)
                cout << "Failed." << endl;
            else
                --index;
            break;
        case 2:
            if (index == T->keynum)
                cout << "Failed" << endl;
            else
                ++index;
            break;
        case 4:
            if (index > 0 && T->ptr[index])
                WalkThrough(T->ptr[index]);
            else
                cout << "Failed" << endl;
            break;
        case 3:
            if (index > 0 && T->ptr[index - 1])
                WalkThrough(T->ptr[index - 1]);
            else
                cout << "Failed" << endl;
            break;
        case 5:
            running = false;
            break;
        }//endsw
    }//endw

    --depth;
}
Node * BTree::gethead() {
    return this->head;
}
