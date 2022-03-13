//
// Created by Tou on 2021/11/4.
//

/***顺序栈的实现***/
#include<iostream>
#include<fstream>

using namespace std;
//顺序栈定义
#define OK 1
#define ERROR 0
#define OVERFLOW (-2)
#define MAXSIZE 100//顺序栈存储空间的初始分配量
typedef int Status;
typedef char SElemType;
typedef struct {
    SElemType *base;//栈底指针
    SElemType *top;//栈顶指针
    int stackSize;//栈可用的最大容量
} SqStack;

//算法 3.1 顺序栈的初始化
Status InitStack(SqStack &S) {
//构造一个空栈 S
    S.base = new SElemType[MAXSIZE];//为顺序栈动态分配一个最大容量为 MAXSIZE的数组空间
    if (!S.base)
        exit(OVERFLOW); //存储分配失败
    S.top = S.base; //top 初始为 base，空栈
    S.stackSize = MAXSIZE; //stackSize 置为栈的最大容量 MAXSIZE
    return OK;
}

//算法 3.2 顺序栈的入栈
Status Push(SqStack &S, SElemType e) {
// 插入元素 e 为新的栈顶元素
    if (S.top - S.base == S.stackSize)
        return ERROR; //栈满
    *(S.top++) = e; //元素 e 压入栈顶，栈顶指针加 1
    return OK;
}

//算法 3.3 顺序栈的出栈
Status Pop(SqStack &S, SElemType &e) {
//删除 S 的栈顶元素，用 e 返回其值
    if (S.base == S.top)
        return ERROR;//栈空
    e = *(--S.top); //栈顶指针减 1，将栈顶元素赋给 e
    return OK;
}

//算法 3.4 取顺序栈的栈顶元素
char GetTop(SqStack S) {//返回 S 的栈顶元素，不修改栈顶指针
    if (S.top != S.base) //栈非空
        return *(S.top - 1); //返回栈顶元素的值，栈顶指针不变
}

int main() {
    SqStack s;
    int choose, flag = 0;
    SElemType j, t;
    cout << "1.初始化" << endl;
    cout << "2.入栈" << endl;
    cout << "3.读栈顶元素" << endl;
    cout << "4.出栈" << endl;
    cout << "0.退出" << endl;
    cout << endl;
    choose = -1;
    while (choose != 0) {
        cout << "请选择：";
        cin >> choose;
        switch (choose) {
            //算法 3.1 顺序栈的初始化
            case 1:
                if (InitStack(s)) {
                    flag = 1;
                    cout << "成功对栈进行初始化\n\n";
                } else {
                    cout << "初始化栈失败\n\n";
                }
                break;

            //算法 3.2 顺序栈的入栈
            case 2: {
                fstream file;
                file.open("D:/Develop/CLionProjects/Data_Structure/SqStack.txt");
                if (!file) {
                    cout << "错误！未找到文件！" << endl;
                    exit(ERROR);
                }
                if (flag) {
                    flag = 1;
                    cout << "进栈元素依次为：" << endl;
                    while (!file.eof()) {
                        file >> j;
                        if (file.fail())
                            break;
                        else {
                            Push(s, j);
                            cout << j << " ";
                        }
                    }
                    cout << endl << endl;
                } else
                    cout << "栈未建立，请重新选择" << endl;
                file.close();
            }
                break;

            //算法 3.3 顺序栈的出栈
            case 3:
                if (flag != -1 && flag != 0)
                    cout << "栈顶元素为：" << endl << GetTop(s) << endl << endl;
                else
                    cout << "栈中无元素，请重新选择" << endl;
                break;

            //算法 3.4 取顺序栈的栈顶元素
            case 4:
                cout << "依次弹出的栈顶元素为：" << endl;
                while (Pop(s, t)) {
                    flag = -1;
                    cout << t << " ";
                }
                cout << endl;
                break;
        }
    }
    return 0;
}