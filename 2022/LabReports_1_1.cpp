//
// Created by Tou on 2022/3/15.
//

#include <iomanip>
#include "iostream"

using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW (-2)

typedef int Status;

struct Book {
    int id;//ISBN
    string name;//书名
    double price;//定价
};//此处的Book就是教材中Book的一个特例

//------顺序表的存储结构通用格式------
#define MAXSIZE 100            //顺序表可能达到的最大长度
typedef struct {
    Book *elem;            //存储空间的基地址
    int length;            //当前长度
} SqList;

Status InitList_Sq(SqList &L) { //算法2.1 顺序表的初始化
    //构造一个空的顺序表L
    L.elem = new Book[MAXSIZE]; //为顺序表分配一个大小为MAXSIZE的数组空间
    if (!L.elem)
        exit(OVERFLOW); //存储分配失败退出
    L.length = 0; //空表长度为0
    return OK;
}

void InputList_Sq(SqList &L) {
    //在构造好的空表L中录入元素
    for (int i = 0;; ++i) {
        cin >> L.elem[i].id >> L.elem[i].name >> L.elem[i].price;
        if (L.elem[i].price == 0) {
            break;
        } else {
            L.length = i + 1;//注意表长与下标的关系
        }
    }
}


void OutputList_Sq(SqList L) {
    //原样输出
    cout << L.length << endl;
    for (int i = 0; i < L.length; ++i) {
        cout << L.elem[i].id << ' ' << L.elem[i].name << ' ' << fixed << setprecision(2) << L.elem[i].price << endl;
        // fixed << setprecision(2)  控制2位小数输出
    }

//    cout << L.elem[i] << endl;
}


//-----以下为主函数-----
int main() {
    //1.定义变量
    SqList L; //定义顺序表L
    //2.调用函数
    InitList_Sq(L);

    InputList_Sq(L);
    OutputList_Sq(L);


    return 0;
}
