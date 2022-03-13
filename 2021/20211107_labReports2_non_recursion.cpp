//
// Created by Tou on 2021/11/7.
//

#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

//结构体，表示汉诺塔的信息
struct Hanoi_stack {
    Hanoi_stack(int n, char a, char b, char c) : _n(n), _x(a), _y(b), _z(c) {}

    int _n;
    char _x, _y, _z;
};

bool isNum(string str);

bool isNum(string str) {
    stringstream sin(str);
    double d;
    char c;
    if (!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

void Hanoi(int n, char x, char y, char z) {
    int nn = n;
    //声明一个汉诺塔类型的栈，即其元素都具有汉诺塔结构体信息
    stack<Hanoi_stack> s;
    //将一个汉诺塔入栈
    s.push(Hanoi_stack(n, x, y, z));
    //栈不空则执行
    while (!s.empty()) {
        //取栈顶元素为q
        Hanoi_stack q = s.top();
        //把栈顶弹出
        s.pop();
        //分别将当前处理汉诺塔信息赋给函数参数
        n = q._n;
        x = q._x;
        y = q._y;
        z = q._z;
        //如果只剩一个盘了，则移动并输出操作
        if (n == 1) {
            cout << "从" << q._x << "杆移动到" << q._z << "杆" << endl;
        } else { //还剩多个盘，则将新的汉诺塔元素入栈，返回while循环开始操作
            s.push(Hanoi_stack(n - 1, y, x, z));
            s.push(Hanoi_stack(1, x, y, z));
            s.push(Hanoi_stack(n - 1, x, z, y));
        }
    }
}

int main() {
    int k = -1;
    string N;
    cout << "请输入汉诺塔的阶数：";
    while (k != 0) {
        cin >> N;
        if (isNum(N)) {//判断是否是数字
            int n = stoi(N);
            if (n > 0) {
                Hanoi(n, 'A', 'B', 'C');
                k = 0;
            } else {
                cout << "您输入的不是符合要求的数字,请重新输入：";
            }
        } else {
            cout << "您输入的不是符合要求的数字,请重新输入：";
        }
    }
    return 0;
}
