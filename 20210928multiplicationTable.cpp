//
// Created by Tou Lau on 2021/9/28.
//
#include <iostream>
using namespace std;

int main(){
    int num;
//    cout << "请输入大于等于1小于等于20的整数：";
    cin >> num;
    if (num>=1 && num<=20){
        for (int i = 1; i <= num ; ++i) {
            for (int j = 1; j <= i ; ++j) {
                cout << i << "x" << j <<"="<< i*j << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "输入的内容不符合规范";
    }
}