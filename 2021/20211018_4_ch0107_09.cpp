//
// Created by Tou Lau on 2021/10/18.
//
#include <cstring>
#include <iostream>

using namespace std;

int main() {
    char s[1000];
    cin.getline(s, 1000);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if ('a' <= s[i] && s[i] <= 'y') {
            s[i]++;
        } else if ('A' <= s[i] && s[i] <= 'Y') {
            s[i]++;
        } else if (s[i] == 'z') {
            s[i] = 'a';
        } else if (s[i] == 'Z') {
            s[i] = 'A';
        }
    }
    cout << s ;
    return 0;
}
