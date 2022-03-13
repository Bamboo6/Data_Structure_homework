//
// Created by Tou on 2022/3/12.
//

#include <iostream>

using namespace std;

#define MaxSize 30
#define OK 1
#define ERROR 0
#define OVERFLOW (-1)
#define LIST_INIT_SIZE 50
#define LISTINCREMENT 10

typedef struct BookInfo {
    int isbn;
    char title[30];
    char author[30];
    int createTime;
    float price;
    int scanNum;
} Book;

typedef struct LocationInfo {
    int floor;
    int bookshelfNum;
    int bookshelfFloor;
} Loc;

typedef struct BorrowInfo {
    int stuId;
    char stuName[30];
    int borrowTimes;
} Bor;

typedef struct {
    Book *data;                                 //数据存储域
    int length;                                 //长度域
} linklist;

typedef struct {
    Book *book;
    int length;
    int listSize;
} SqList;

int InitList_Sq(SqList &L) {   //构造一个空的线性表L。
    L.book = (Book *) malloc(LIST_INIT_SIZE * sizeof(Book));
    //申请初始化长度的内存
    if (!L.book) {
        //如果L的序列非空
        exit(OVERFLOW);
        //说明L被重定义了，抛出溢出
    }
    L.length = 0;
    //默认L内有0个元素
    L.listSize = LIST_INIT_SIZE;
    //默认L的容量为初始化长度
    return OK;
}

void menuList() {
    cout << "                    *图书管理系统*                   \n";
    cout << "-----------------------------------------------------\n";
    cout << "                    1.创建记录表格                   \n";
    cout << "                     -2.插入数据-                    \n";
    cout << "                     -3.删除数据-                    \n";
    cout << "                   -4.删除所有记录-                  \n";
    cout << "                     -5.读取文件-                    \n";
    cout << "                   -6.查看记录列表-                  \n";
    cout << "                     -7.价格调整-                    \n";
    cout << "                    -8.按书名查找-                   \n";
    cout << "                   -9.按作者查找-                    \n";
    cout << "                     -10.逆转排序-                    \n";
    cout << "                   -11.按价格排序-                   \n";
    cout << "                    -12.输入数据-                    \n";
    cout << "                       -0.退出-                      \n";
    cout << "                  |请输入选择：";
}