//
// Created by Tou on 2021/10/28.
//

// from https://www.freesion.com/article/48991114883/
// 设计一个算法，通过遍历一趟，将链表中所有结点的链接方向逆转，仍利用原表的存储空间。
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
        cout << p->date;
        p = p->next;
    }
}

//后插法构建链表
void CreateLiklist(Linklist &L, int n) {
    Linklist r = L;
    for (int i = 0; i < n; i++) {
        Linklist p = new Lnode; //开辟空间，p为节点
        printf("请输入第%d个数据\n", i + 1);
        cin >> p->date;
        p->next = NULL;
        r->next = p; //将新节点插入r之后
        r = p;       //r指向新的尾节点
    }
}

void inverse(Linklist &L) {
    Linklist p = L->next;
    L->next = NULL;
    Linklist q;
    while (p) {
        q = p;
        p = p->next;//指向后继
        q->next = L->next;//前插法插入元素
        L->next = q;
    }
}

int main() {
    Linklist linklist;
    //初始化
    init(linklist);
    int n1;
    cout << "请输入链表元素的个数" << endl;
    cin >> n1;
    CreateLiklist(linklist, n1);
    inverse(linklist);
    cout << "逆转后结果：";
    output(linklist);
    cout << endl;
}

