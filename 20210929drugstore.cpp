//
// Created by Tou Lau on 2021/9/29.
//
#include <iostream>
using namespace std;

int main(){
    int m , n, l=0 ;
//    cout << "请输入药品总量：";
    cin >> m;
//    cout << "请输入人数：";
    cin >> n;
    int q[n-1];
    if (n>0 && n<=100){
//        cout << "请输入每个病人希望取走的药品数量（按照时间先后的顺序），两数之间以空格分隔：";
        int i = 0;
        while (i<n){
            cin>>q[i];
//            cout<<q[i]<<"";
            i++;
        }
//        cout << endl;
        for (int j = 0; j < n; ++j) {
            if (q[j]<m){
                m -= q[j];
            } else {
                l++;
            }
        }

    } else {
        cout << "输入的人数不符合规范";
    }
//    cout << "这一天没有取上药品的人数为："<< l;
    cout << l << endl;

}