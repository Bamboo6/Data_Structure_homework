//
// Created by Tou Lau on 2021/9/29.
//
#include <iostream>
using namespace std;

int main(){
    int m , n, l=0 ;
//    cout << "������ҩƷ������";
    cin >> m;
//    cout << "������������";
    cin >> n;
    int q[n-1];
    if (n>0 && n<=100){
//        cout << "������ÿ������ϣ��ȡ�ߵ�ҩƷ����������ʱ���Ⱥ��˳�򣩣�����֮���Կո�ָ���";
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
        cout << "��������������Ϲ淶";
    }
//    cout << "��һ��û��ȡ��ҩƷ������Ϊ��"<< l;
    cout << l << endl;

}