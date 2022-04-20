//
// Created by Tou on 2021/12/22.
//

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    cout << setw(2) << setfill('0') << ltm->tm_hour << ":";
    cout << ltm->tm_min << ":";
    cout << ltm->tm_sec << endl;
}
