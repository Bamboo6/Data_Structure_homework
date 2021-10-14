//
// Created by Tou Lau on 2021/10/14.
//
#include <bits/stdc++.h>

using namespace std;

#define A (200+5)
struct info {
    char name[8];
    float temperature;
    int cough;
} info[A];
//bool judge(info);

int main() {
    int n,c;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> info[i].name >> info[i].temperature >> info[i].cough;
    }
    for (int i = 0; i < n; ++i) {
        if (info[i].temperature>=37.5 && info[i].cough == 1){
            cout << info[i].name << endl;
            c++;
        }
    }
    cout << c <<endl;
}