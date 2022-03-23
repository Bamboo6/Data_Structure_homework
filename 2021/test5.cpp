//
// Created by Tou on 2021/12/22.
//

#include <iostream>

using namespace std;

int main() {
    string str;
    cout << "请输入：";
    getline(cin, str);
    cout << "输入内容为：" << str;
    int num = int(str.length());
}
