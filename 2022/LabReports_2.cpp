//
// Created by Tou on 2022/3/17.
//

#include "iostream"

using namespace std;

string str;

void output() {
    cout << "输入内容为：" << str;
}

void countNum() {
    int index = 0;
    string noSpaceStr = str;
//    去除空格再计数
    while ((index = int(noSpaceStr.find(' ', index))) != string::npos) {
        noSpaceStr.erase(index, 1);
    }
    int num = int(noSpaceStr.length());
    cout << "字符个数为：" << num;
}

void firstAppear() {
    string appear;
    cout << "请输入需要查找的字符：";
    cin >> appear;
    if (str.find(appear) != string::npos) {
        cout << "字符 " << appear << " 在字符串 " << str << " 中首次出现的位置为："
             << str.find(appear);
    } else {
        cout << "未找到，请检查输入的内容是否存在";
    }
}

void insertStr() {
    string insertS, inputIndex;
    int index = 0;
    cout << "请输入需要添加的字符：";
    cin >> insertS;
    cin.ignore();
    cout << "请输入需要添加的位置（默认为0）：";
    getline(cin, inputIndex);
    index = strtol(inputIndex.c_str(), nullptr, 0);
    str = str.insert(index, insertS);
    cout << str;
}

void delStr() {
    int index = 0;
    string delS;
    cout << "请输入需要删除的字符：";
    cin >> delS;
    while ((index = int(str.find(delS, index))) != string::npos) {
        str.erase(index, delS.length());
    }
    cout << str;
}

void replaceStr() {
    int index = 0;
    string replaceS,appear;
    cout << "请输入需要查找的字符：";
    cin >> appear;
    cout << "请输入需要替换的字符：";
    cin >> replaceS;
    while ((index = int(str.find(appear, index))) != string::npos) {
        str.replace(index,appear.length(),replaceS);
    }
    cout << str;
}

void BF(){
//    TODO
}

int menu() {
    int c;
    cout << endl;
    cout << endl;
    cout << "                      *主菜单*                         " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "                 1.输出字符                             " << endl;
    cout << "                 2.统计字符个数                          " << endl;
    cout << "                 3.字符第一次出现位置                     " << endl;
    cout << "                 4.插入字符                             " << endl;
    cout << "                 5.删除字符                             " << endl;
    cout << "                 6.替换字符                             " << endl;
    cout << "                 7.BF算法                              " << endl;
    cout << "                 0.退出                                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "请输入选择：";
    cin >> c;
    return c;
}

enum operationCode {
    o_exit,
    o_output,
    o_count,
    o_firstAppear,
    o_insert,
    o_del,
    o_replace,
    o_BF
};

int main() {
    int operationCode;
    int isExsit = 0;
    while (!isExsit) {
        if (str.empty()) {
            cout << "请输入字符串：";
            getline(cin, str);
        }
        operationCode = menu();
        switch (operationCode) {
            case o_exit:
                isExsit = -1;
                break;
            case o_output:
                output();
                break;
            case o_count:
                countNum();
                break;
            case o_firstAppear:
                firstAppear();
                break;
            case o_insert:
                insertStr();
                break;
            case o_del:
                delStr();
                break;
            case o_replace:
                replaceStr();
                break;
            case o_BF:
                BF();
                break;
            default:
                cout << "输入有误！" << endl;
        }
    }
}