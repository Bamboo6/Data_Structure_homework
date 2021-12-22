//
// Created by Tou on 2021/12/22.
//
#include <iostream>

using namespace std;

#define MAX 100
#define OVERFLOW (-2)
#define OK 1

typedef int Status;
typedef struct {
    int key;
    char *otherInfo;
} ElemType;

typedef struct {
    ElemType *elem;
    int len;
} SqList;

void Create_SqList(SqList &L) {
    int i, n;
    cout << "请输入数据个数: " << endl;
    cin >> n;                                            //输入个数
    cout << "请输入待排序的数据: " << endl;
    for (i = 1; i <= n; i++) {
        cin >> L.elem[i].key;
        L.len++;
    }
}

void show(SqList L) {
    int i;
    for (i = 1; i <= L.len; i++)
        cout << L.elem[i].key << endl;
}

// 直接插入排序
void InsertSort(SqList &L) {
    int i, j;
    for (i = 2; i <= L.len; ++i) {
        if (L.elem[i].key < L.elem[i - 1].key) {
            L.elem[0] = L.elem[i];
            L.elem[i] = L.elem[i - 1];
            for (j = i - 2; L.elem[0].key < L.elem[j].key; --j) {
                L.elem[j + 1] = L.elem[j];
            }
            L.elem[j + 1] = L.elem[0];
        }
    }
}

//折半插入排序
void BInsertSort(SqList &L) {
    int i, j, low, high, m;
    for (i = 2; i <= L.len; ++i) {
        L.elem[0] = L.elem[i];
        low = 1;
        high = i - 1;
        while (low <= high) {
            m = (low + high) / 2;
            if (L.elem[0].key < L.elem[m].key) high = m - 1;
            else low = m + 1;
        }
        for (j = i - 1; j >= high + 1; --j) {
            L.elem[j + 1] = L.elem[j];
        }
        L.elem[high + 1] = L.elem[0];
    }
}

void ShellInsert(SqList &L, int dk) {
    //对顺序表L做一趟增量是dk的希尔插入排序
    int i, j;
    for (i = dk + 1; i <= L.len; ++i)
        if (L.elem[i].key < L.elem[i - dk].key) {                                        //需将L.elem[i]插入有序增量子表
            L.elem[0] = L.elem[i];                        //暂存在L.elem[0]
            for (j = i - dk; j > 0 && L.elem[0].key < L.elem[j].key; j -= dk)
                L.elem[j + dk] = L.elem[j];                //记录后移，直到找到插入位置
            L.elem[j + dk] = L.elem[0];                    //将elem[0]即原elem[i]，插入到正确位置
        }                                        //for
}

void ShellSort(SqList &L, int dt[], int t) {
    //按增量序列dt[0..t-1]对顺序表L作t趟希尔排序
    int k;
    for (k = 0; k < t; ++k)
        ShellInsert(L, dt[k]);                    //一趟增量为dt[t]的希尔插入排序
}

void Shell(SqList &L) {
    int i, t;//增量数组的长度
    int *dt = new int[MAX];//增量数组
    cout << "请输入增量个数：\n";
    cin >> t;
    for (i = 0; i < t; i++) {
        cout << "第" << i + 1 << "个增量:\n";
        cin >> dt[i];
    }
    ShellSort(L, dt, t);
}

//冒泡排序
void BubbleSort(SqList &L) {
    //对顺序表L做
    int m, j, flag;
    ElemType t;
    m = L.len - 1;
    flag = 1;                //flag用来标记某一趟排序是否发生交换
    while ((m > 0) && (flag == 1)) {
        flag = 0;
        for (j = 1; j <= m; j++) {
            if (L.elem[j].key > L.elem[j + 1].key) {
                flag = 1;
                t = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = t;
            }
        }
        --m;
    }
}

int Partition(SqList &L, int low, int high) {
    //对顺序表L中的子表elem[low..high]进行一趟排序，返回枢轴位置
    int pivotKey;
    L.elem[0] = L.elem[low];
    pivotKey = L.elem[low].key;
    while (low < high) {
        while (low < high && L.elem[high].key >= pivotKey) --high;
        L.elem[low] = L.elem[high];
        while (low < high && L.elem[low].key <= pivotKey) ++low;
        L.elem[high] = L.elem[low];
    }
    L.elem[low] = L.elem[0];
    return low;
}

void QSort(SqList &L, int low, int high) {
    int pivotLoc;
    if (low < high) {
        pivotLoc = Partition(L, low, high);
        QSort(L, low, pivotLoc - 1);
        QSort(L, pivotLoc + 1, high);
    }
}

void QuickSort(SqList &L) {
    QSort(L, 1, L.len);
}

void SelectSort(SqList &L) {
    //对顺序表L做简单选择排序
    int i, j, k;
    ElemType t;
    for (i = 1; i < L.len; ++i) {
        k = i;
        for (j = i + 1; j <= L.len; ++j) {
            if (L.elem[j].key < L.elem[k].key) k = j;
        }
        if (k != i) {
            t = L.elem[i];
            L.elem[i] = L.elem[k];
            L.elem[k] = t;
        }
    }
}

void MergeArray(SqList &L,int head1,int tail1,int head2,int tail2) {
    int i=head1,j=head2,k=0;
    int *p=(int *)malloc(sizeof(int)*(tail2-head1+1));
    int *point=p;
    while(i<=tail1&&j<=tail2) {
        if(L.elem[i].key<=L.elem[j].key)p[k++]=L.elem[i++].key;
        else p[k++]=L.elem[j++].key;
    }
    while(i<=tail1)p[k++]=L.elem[i++].key;
    while(j<=tail2)p[k++]=L.elem[j++].key;
    for(k=0; k<=tail2-head1; k++)L.elem[head1+k].key=p[k];
    free(point);
}

void MergeSort(SqList &L,int head,int tail) {
    if(head<tail) {
        MergeSort(L,head,(head+tail)/2);
        MergeSort(L,(head+tail)/2+1,tail);
        MergeArray(L,head,(head+tail)/2,(head+tail)/2+1,tail);

    }
}

int menu() {
    int c;
    cout << "------排序算法------" << endl;
    cout << "1.创建顺序表" << endl;
    cout << "0.退出" << endl;
    cout << "选择：";
    cin >> c;
    return c;
}

int menu2() {
    int c;
    cout << "------排序算法------" << endl;
    cout << "1.直接插入排序" << endl;
    cout << "2.折半插入排序" << endl;
    cout << "3.希尔排序" << endl;
    cout << "4.冒泡排序" << endl;
    cout << "5.快速排序" << endl;
    cout << "6.选择排序" << endl;
    cout << "7.二路归并排序" << endl;
    cout << "0.退出" << endl;
    cout << "选择：";
    cin >> c;
    return c;
}


int main() {
    while (true) {
        switch (menu()) {
            case 1: {
                SqList L;
                L.elem = new ElemType[MAX + 1];
                L.len = 0;
                Create_SqList(L);
                show(L);
                while (true) {
                    bool flag = true;
                    switch (menu2()) {
                        case 0:
                            flag = false;
                            break;
                        case 1:
                            InsertSort(L);
                            show(L);
                            break;
                        case 2:
                            BInsertSort(L);
                            show(L);
                            break;
                        case 3:
                            Shell(L);
                            show(L);
                            break;
                        case 4:
                            BubbleSort(L);
                            show(L);
                            break;
                        case 5:
                            QuickSort(L);
                            show(L);
                            break;
                        case 6:
                            SelectSort(L);
                            show(L);
                            break;
                        case 7:
                            MergeSort(L,0,L.len);
                            show(L);
                            break;
                        default:
                            break;

                    }
                    if (!flag) {
                        break;
                    }
                }
                break;
            }
            case 0:
                cout << "退出成功\n" << endl;
                exit(0);
            default:
                break;
        }
    }
}