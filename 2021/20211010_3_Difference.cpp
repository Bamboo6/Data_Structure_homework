//
// Created by Tou Lau on 2021/10/10.
//

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << *max_element(a, a+n) - *min_element(a, a+n) << endl;
}