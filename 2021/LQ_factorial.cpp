//
// Created by Tou Lau on 2021/9/29.
//
#include<bits/stdc++.h>
using namespace std;

int a[1000000] = {0, 1};       //初始化a[1] = 1
int b[1000000] = {0, 1};

int main() {
    int n, digit_1 = 1;    //digit为当前的最多位数，初始化为1位（即阶乘的结果初始化为1）
    cin >> n;       //读入n
    for (int i = 2; i <= n; i++) {     //从2开始乘数组每一个元素
        int carrying_1 = 0;         //carrying1表示进位，初始化为0
        int carrying_2 = 0,digit_2 = 1;
        for (int j = 1; j <= digit_1; j++) {
            carrying_1 = a[j] * i + carrying_1;       //数组每一位与i相乘的结果 + 上次留下的进位
            a[j] = carrying_1 % 10;            //carrying1 % 10是乘i之后a[j]的值
            carrying_1 /= 10;                 //新进位是carrying1 / 10
        }
        while (carrying_1) {           //最后统一进位
            a[++digit_1] = carrying_1 % 10;
            carrying_1 /= 10;
        }

        for (int y = 1; y <= digit_1; ++y) {
            carrying_2 = a[y] + b[y] + carrying_2;
            b[y] = carrying_2 % 10;
            carrying_2 /= 10;
        }
        while (carrying_2){
            b[++digit_2] = carrying_2 % 10;
            carrying_2 /= 10;
        }
    }

//    for (int i = digit; i >= 1; i--){
//        cout << a[i];
//    }
//    cout << endl;
    for (int j = digit_1; j >= 1; j--){
        cout << b[j];
    }
    cout << endl;
//    cout << digit_1;
//    return 0;
}