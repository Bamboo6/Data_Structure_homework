//
// Created by Tou on 2021/10/28.
//

//对长度为n的顺序表L，编写一个时间复杂度为O(n) 、空间复杂度为O(1)的算法，该算法删除线性表中所有值为x的数据元素
#include <iostream>

using namespace std;
#define ElemType int
#define Initsize 50

typedef struct {
    int *data;
    int length;
} SqList;

void Init(SqList &L, int n) {
    L.data = new int[Initsize];//c++的初始动态分配语句
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个元素：\n", i + 1);
        cin >> L.data[i];
    }
    L.length = n;
}

void del_x(SqList &L, ElemType x) {
    int k = 0, i = 0;         //K记录值等于x的元素个数
    while (i < L.length) {
        if (L.data[i] == x)
            k++;
        else
            L.data[i - k] = L.data[i];    //当前元素前移k个位置
        i++;
    }
    L.length = L.length - k;         //顺序表L的长度递减
}

int main() {
    SqList L;
    ElemType x;
    int n = 0;
    cout << "请输入链表元素的个数：";
    cin >> n;
    Init(L, n);
    cout << "请输入item的值：";
    cin >> x;
    del_x(L, x);
    cout << "结果为：";
    for (int i = 0; i < L.length; i++)
        cout << L.data[i] << " ";
    return 0;
}


