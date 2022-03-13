//
// Created by Tou Lau on 2021/9/28.
//
#include <iostream>
using namespace std;

int main() {
    int num;
    float f[10000] = {};
//    cout << "请输入大于1且小于30的整数：";
    cin >> num;
    float factorial = 1;
//    if (num > 1 && num < 30) {
        for (int i = 1; i <= num; ++i) {
            factorial *= i;
            f[i-1] = factorial;
        }
        float sum = 0;
        int j=0;
        while(f[j]!= '\0' ){
            sum += f[j];
            j++;
        }
        cout << num << "的阶乘之和为：" << sum;
//    } else {
//        cout << "输入的内容不符合规范";
//    }
}