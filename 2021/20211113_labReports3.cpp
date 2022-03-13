//
// Created by Tou on 2021/11/13.
//
#include<cstdio>
#include<cstdlib>
#include <iostream>
using namespace std;

#define MaxSize 200

typedef int QElemType;
typedef struct {
    QElemType *base;    //指向动态分配的数组中的元素
    int front;  //记录队列头
    int rear;   //记录队列尾
} SqQueue;

void InitQueue(SqQueue *Q) {
    //构造一个空队列Q
    Q->base = (QElemType *) malloc(sizeof(QElemType) * MaxSize); //申请一段长度为MaxSize*sizeof(int)的连续空间，用Q->base存放
    if (!Q->base) exit(1);   //验证，Q不为空，返回1
    Q->front = Q->rear = 0;
}

//int QueueLength(SqQueue *Q) {
//    //返回Q的元素个数，即队列的长度
//    int e;
//    e = (Q->rear - Q->front + MaxSize) % MaxSize;
//    return e;
//}

void EnQueue(SqQueue *Q, QElemType e) {
    //插入的元素e为Q的新的队尾元素
    if ((Q->rear + 1) % MaxSize == Q->front) exit(1);

    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MaxSize;
}

void DeQueue(SqQueue *Q) {
    //若队列不空，则删除Q的队头元素，可以用e返回其值
    if (Q->front == Q->rear)
        exit(1);    //返回1，exit为C++的退出函数，声明于stdlib.h中，对于C++其标准的头文件为cstdlib
    //e=Q.base[Q.front];
    Q->front = (Q->front + 1) % MaxSize;
}

int GetHead(SqQueue *Q) {
    //返回队头元素
    return Q->base[Q->front];
}

int main() {
    int N, n, c;
    QElemType t, x;
    SqQueue f, *Q;   //用Q接收f的地址
    Q = &f;
    InitQueue(Q);   //初始化，构造一个空队列
    cout << "请输入杨辉三角行数：";
    cin >> N;
    EnQueue(Q, 1);   //插入元素1到队尾
    for (n = 2; n <= N; n++) {
        for (int i = 0; i <= N - n; i++) {
            printf("  ");
        }
        EnQueue(Q, 1);   //杨辉三角每一行的第一个元素都是1
        for (c = 1; c <= n - 2; c++) {//当n=2时，即杨辉三角第二行，不执行本段代码,从第三行开始
            t = GetHead(Q);
            DeQueue(Q);
            printf("%4d", t);
            x = GetHead(Q); //用x获取删除后队列的头元素，即原来的第二个元素
            t = t + x;    //原来的头元素和后来的头元素相加，得到杨辉三角下一行的第2，3，4...个元素
            EnQueue(Q, t);
        }
        EnQueue(Q, 1);   //队尾的元素永远是1
        printf("%4d", GetHead(Q));   //输出队尾的1并删除
        DeQueue(Q);
        printf("\n");
    }
    while (Q->front != Q->rear) {//输出最后一行
        printf("%4d", GetHead(Q));
        DeQueue(Q);
    }
}

