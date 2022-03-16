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

typedef struct LocationInfo {
    int floor;
    int bookshelfNum;
    int bookshelfFloor;
} Loc;

typedef struct BorrowInfo {
    int stuId;
    string stuName;
    int borrowTimes;
} Bor;

typedef struct BookInfo {
    int id;
    int isbn;
    string title[30];
    string author[30];
    int createTime;
    float price;
    int scanNum;
    Loc loc;
    Bor bor;
} Book;

typedef struct {
    Book *data;
    int length;
} linklist;

int getTime() {
    time_t now_timestamp;
    now_timestamp = time(nullptr);
    string now_time = ctime(&now_timestamp);
    return 0;
}

Boolean createBookSystem(BookSystem *bs) {
    FILE *pf = fopen(SystemPath, "r");
    if (pf != NULL) {
        //1，已经创建过了，直接读取
        fscanf(pf, "createdAt: %d\nauthor: %s\nbookTotal:%d\nnextId: %d\n", &bs->createdAt,bs->author,&bs->bookTotal,&bs->nextId);
        fclose(pf);
        //读取图书信息列表
        readBookSystem(bs);
    } else {
        //2.读取失败，新建一个
        fclose(pf);
        bs->createdAt = getTime();
        strcpy(bs->author,"vanxizzz");
        bs->nextId = 0;
        bs->bookTotal = 0;
        bs->firstBook = NULL;
        bs->lastBook = NULL;
        for (int i = 0; i < 5; ++i) {
            insertBook(bs,1);//模拟图书入库
        }
        saveBookSystem(bs);//保存到文件中
    }
    return 1;
}

int menu() {
    int c;
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