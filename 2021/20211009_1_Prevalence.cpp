//
// Created by Tou Lau on 2021/10/9.
//

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, a = 0, b = 0, c = 0, d = 0;
    double A, B, C, D;
    cin >> n;
    int temp = n;

    while (temp--) {
        int t;
        cin >> t;
        if (t >= 1 && t <= 18) {
            a++;
        }else if (19 <= t && t <= 35) {
            b++;
        }
        else if (36 <= t && t <= 60) {
            c++;
        }
        else {
            d++;
        }
    }

    A = 100.0 * a / n;
    B = 100.0 * b / n;
    C = 100.0 * c / n;
    D = 100.0 * d / n;

    cout << fixed << setprecision(2)
        << A << "%" << endl
        << B << "%" << endl
        << C << "%" << endl
        << D << "%" << endl;
}

