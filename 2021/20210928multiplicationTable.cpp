//
// Created by Tou Lau on 2021/9/28.
//
#include <iostream>
using namespace std;

int main(){
    int num;
//    cout << "��������ڵ���1С�ڵ���20��������";
    cin >> num;
    if (num>=1 && num<=20){
        for (int i = 1; i <= num ; ++i) {
            for (int j = 1; j <= i ; ++j) {
                cout << i << "x" << j <<"="<< i*j << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "��������ݲ����Ϲ淶";
    }
}