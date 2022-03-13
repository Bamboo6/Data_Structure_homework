//
// Created by Tou on 2021/11/7.
//
#include <iostream>
#include <sstream>

using namespace std;

void Move(int n, char A, char C) {
    cout << "将" << n << "号盘从" << A << "杆移动到" << C << "杆" << endl;
}

void Hanoi(int n, char A, char B, char C) {
    if (n == 1)
        Move(1, A, C);      /* 将1号盘从A杆移到C杆 */
    else {
        Hanoi(n - 1, A, C, B);   /* 将A杆上n-1个盘借助C杆移动到B杆 */
        Move(n, A, C);             /* 将n号盘从A杆移到C杆 */
        Hanoi(n - 1, B, A, C);   /* 将B杆上n-1个盘借助A杆移动到C杆 */
    }
}

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
