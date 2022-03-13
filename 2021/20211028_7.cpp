//
// Created by Tou on 2021/10/28.
//

// from https://www.freesion.com/article/48991114883/
// ���һ���㷨��ͨ������һ�ˣ������������н������ӷ�����ת��������ԭ��Ĵ洢�ռ䡣
#include <iostream>

using namespace std;

//����洢
typedef struct LNode {
    int date;
    struct LNode *next;
} Lnode, *Linklist;

//�����ʼ��
void init(Linklist &L) {
    L = new Lnode;  // ���ٿռ�
    L->next = NULL; //ͷ�ڵ���Ϊ��
}

//�������
void output(Linklist &T) {
    Linklist p = T;
    p = p->next;
    while (p) {
        cout << p->date;
        p = p->next;
    }
}

//��巨��������
void CreateLiklist(Linklist &L, int n) {
    Linklist r = L;
    for (int i = 0; i < n; i++) {
        Linklist p = new Lnode; //���ٿռ䣬pΪ�ڵ�
        printf("�������%d������\n", i + 1);
        cin >> p->date;
        p->next = NULL;
        r->next = p; //���½ڵ����r֮��
        r = p;       //rָ���µ�β�ڵ�
    }
}

void inverse(Linklist &L) {
    Linklist p = L->next;
    L->next = NULL;
    Linklist q;
    while (p) {
        q = p;
        p = p->next;//ָ����
        q->next = L->next;//ǰ�巨����Ԫ��
        L->next = q;
    }
}

int main() {
    Linklist linklist;
    //��ʼ��
    init(linklist);
    int n1;
    cout << "����������Ԫ�صĸ���" << endl;
    cin >> n1;
    CreateLiklist(linklist, n1);
    inverse(linklist);
    cout << "��ת������";
    output(linklist);
    cout << endl;
}

