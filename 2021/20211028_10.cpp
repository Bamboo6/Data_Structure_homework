//
// Created by Tou on 2021/10/28.
//

//�Գ���Ϊn��˳���L����дһ��ʱ�临�Ӷ�ΪO(n) ���ռ临�Ӷ�ΪO(1)���㷨�����㷨ɾ�����Ա�������ֵΪx������Ԫ��
#include <iostream>

using namespace std;
#define ElemType int
#define Initsize 50

typedef struct {
    int *data;
    int length;
} SqList;

void Init(SqList &L, int n) {
    L.data = new int[Initsize];//c++�ĳ�ʼ��̬�������
    for (int i = 0; i < n; i++) {
        printf("�������%d��Ԫ�أ�\n", i + 1);
        cin >> L.data[i];
    }
    L.length = n;
}

void del_x(SqList &L, ElemType x) {
    int k = 0, i = 0;         //K��¼ֵ����x��Ԫ�ظ���
    while (i < L.length) {
        if (L.data[i] == x)
            k++;
        else
            L.data[i - k] = L.data[i];    //��ǰԪ��ǰ��k��λ��
        i++;
    }
    L.length = L.length - k;         //˳���L�ĳ��ȵݼ�
}

int main() {
    SqList L;
    ElemType x;
    int n = 0;
    cout << "����������Ԫ�صĸ�����";
    cin >> n;
    Init(L, n);
    cout << "������item��ֵ��";
    cin >> x;
    del_x(L, x);
    cout << "���Ϊ��";
    for (int i = 0; i < L.length; i++)
        cout << L.data[i] << " ";
    return 0;
}


