//
// Created by Tou on 2021/10/31.
//

#include <iostream>

using namespace std;
//定义存储
typedef struct LNode {
    int date;
    struct LNode *next;
} Lnode, *Linklist;

//链表初始化
void init(Linklist &L) {
    L = new Lnode;  // 开辟空间
    L->next = NULL; //头节点置为空
}

//输出数据
void output(Linklist &T) {
    Linklist p = T;
    p = p->next;
    while (p) {
        cout << p->date << " ";
        p = p->next;
    }
}

//后插法构建链表
void CreateLiklist(Linklist &L, int n) {
    Linklist r = L;
    for (int i = 0; i < n; i++) {
        Linklist p = new Lnode; //开辟空间，p为节点
        printf("请输入第%d个元素：", i + 1);
        cin >> p->date;
        p->next = NULL;
        r->next = p; //将新节点插入r之后
        r = p;       //r指向新的尾节点
    }
}

void del(Linklist &L, int mink, int maxk) {
    Linklist pre = L;
    Linklist p = L->next;
    while (p) {
        if (p->date > mink && p->date < maxk) {
            pre->next = p->next;
        } //pre为pa前驱，删除不符合的节点
        else {
            pre = p;
        }            //如果符合条件，执行pre=pa;使pre为pa的前驱。
        p = p->next; //指向下一个节点。
    }
}

int main() {
    Linklist La;
    //初始化
    init(La);
    int n,mink,maxk;
    cout << "请输入链表元素的个数：";
    cin >> n;
    CreateLiklist(La, n);
    cout << "请输入mink：";
    cin >> mink;
    cout << "请输入maxk：";
    cin >> maxk;
    del(La, mink, maxk);
    cout << "结果为：";
    output(La);
    cout << endl;
}


