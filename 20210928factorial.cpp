//
// Created by Tou Lau on 2021/9/28.
//
#include <iostream>
using namespace std;

int main() {
    int num;
    float f[10000] = {};
//    cout << "���������1��С��30��������";
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
        cout << num << "�Ľ׳�֮��Ϊ��" << sum;
//    } else {
//        cout << "��������ݲ����Ϲ淶";
//    }
}