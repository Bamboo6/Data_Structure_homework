//
// Created by Tou Lau on 2021/9/29.
//
#include <iostream>
using namespace std;

int main(){
    int n , i=0 , r=0;
//    cout << "���������������";
    cin >> n;
    int sp[n-1] , dp[n-1];
    while (i<n){
        cin>>sp[i]>>dp[i];
        i++;
    }
    for (int j = 0; j < n; ++j) {
        if (sp[j]>=90 && sp[j]<=140 && dp[j]>=60 && dp[j]<=90){
            r++;
        }else{
            r=0;
        }
    }
//    cout << "Ѫѹ�����������Сʱ��Ϊ��" << r ;
    cout << r << endl ;
}