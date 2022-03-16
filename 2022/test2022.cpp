//
// Created by Tou on 2022/3/15.
//

#include "ctime"
#include "iostream"

using namespace std;

int main() {
    time_t now_time;
    now_time = time(nullptr);
    cout << ctime(&now_time);
    return 0;
}