//
// Created by Tou Lau on 2021/10/10.
//

#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, s = 0, c = 0;
    cin >> n;
    int a[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] <= 50) {
                s++;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] <= 50) {
                if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                    c++;
                } else if (a[i - 1][j] > 50) {
                    c++;
                } else if (a[i + 1][j] > 50) {
                    c++;
                } else if (a[i][j - 1] > 50) {
                    c++;
                } else if (a[i][j + 1] > 50) {
                    c++;
                }
            }
        }
    }

    cout << s << " " << c << endl;
}
