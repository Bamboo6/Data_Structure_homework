//
// Created by Tou Lau on 2021/9/28.
//
#include <iostream>
using namespace std;

int main( )
{
    int month;

    cout << "�������·ݣ�";
    cin >> month;
    switch (month) {
        case 12:
        case 1:
        case 2:
            cout << "����" << endl;
            break;
        case 3:
        case 4:
        case 5:
            cout << "����" << endl;
            break;
        case 6:
        case 7:
        case 8:
            cout << "�ļ�" << endl;
            break;
        case 9:
        case 10:
        case 11:
            cout << "�＾" << endl;
            break;
        default:
            cout << "�·���Ч" << endl;
    }


}

