//
// Created by Tou Lau on 2021/10/18.
//
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int k;
    char s[2500];
    cin >> k >> s;
    int temp = 1;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == s[i + 1]) {
            temp++;
            if (temp >= k){
                cout << s[i];
                return 0;
            }
        } else{
            temp = 1;
        }
    }
    cout << "No";
    return 0;
}

