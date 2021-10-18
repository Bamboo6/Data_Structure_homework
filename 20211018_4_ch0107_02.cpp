//
// Created by Tou Lau on 2021/10/18.
//
#include<iostream>
#include<string>
#include <map>

using namespace std;

int main() {
    string str;
    cin >> str;
    map<int, int> m;
    for (int i = 0; i < str.size(); i++) {//用map记录每个字符的出现次数
        m[str[i]]++;
    }
    for (int i = 0; i < str.size(); i++) {//发现第一次出现次数为一的字符则直接返回
        if (m[str[i]] == 1) {
            cout << str[i];
            return 0;
        }
    }
    cout << "no";
    return 0;
}