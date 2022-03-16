//
// Created by Tou on 2022/3/15.
//

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#define Boolean int

//图书管理系统文件路径
const char *SystemPath = "./book_system.txt";

//图书数据文件路径
const char *BookDataPath = "./book_data.txt";

//位置信息
typedef struct LocationInfo {
    int floor;//存放楼层
    int bookshelfNum;//存放楼层书架号
    int bookshelfFloor;//存放楼层书架层号
} Location;

//书籍信息
typedef struct BookInfo {
    int id;//书籍id
    char isbn[20];//编号
    char title[20];//书名
    char author[20];//作者
    int createdTime;//创建时间
    int updatedTime;//修改时间
    float price;//价格
    int scanNum;//查阅人数
    Location location;//位置信息
    struct BookInfo *next;//下一本书
} Book;

//图书系统信息
typedef struct BookSystem {
    int createdTime;//图书系统创建时间
    char author[20];//作者
    int bookTotal;//当前书籍总数
    int nextId;//创建图书时获取新id
    Book *firstBook;//第一本书
    Book *lastBook;//最后一本书
} BookSystem;

Boolean readBookSystem(BookSystem *);

Boolean insertBook(BookSystem *, int);

void saveBookSystem(BookSystem *);

//获取唯一id
int getOnlyId(BookSystem *bs) {
    return bs->nextId++;
}

//获取唯一的isbn
void getOnlyIsbn(char *target, BookSystem *bs) {
    itoa(2022 + bs->nextId, target, 10);
}

//获取当前时间戳
int getTime() {
    time_t t;
    t = time(nullptr);
//    int now_time = int(time(&t));
    return time(&t);
}

// 1. 创建图书管理系统
Boolean createBookSystem(BookSystem *bs) {
    FILE *pf = fopen(SystemPath, "r");
    if (pf != nullptr) {
        //1，已经创建过了，直接读取
        fscanf(pf, "createdTime: %d\nauthor: %s\nbookTotal:%d\nnextId: %d\n", &bs->createdTime, bs->author,
               &bs->bookTotal,
               &bs->nextId);
        fclose(pf);
        //读取图书信息列表
        readBookSystem(bs);
    } else {
        //2.读取失败，新建一个
        fclose(pf);
        bs->createdTime = getTime();
        strcpy(bs->author, "vanxizzz");
        bs->nextId = 0;
        bs->bookTotal = 0;
        bs->firstBook = nullptr;
        bs->lastBook = nullptr;
        for (int i = 0; i < 5; ++i) {
            insertBook(bs, 1);//模拟图书入库
        }
        saveBookSystem(bs);//保存到文件中
    }
    return 1;
}

//保存到数据库里
void saveBookSystem(BookSystem *bs) {
    FILE *pf = fopen(SystemPath, "w");
    fprintf(pf, "createdTime: %d\nauthor: %s\nbookTotal: %d\nnextId: %d\n", bs->createdTime, bs->author, bs->bookTotal,
            bs->nextId);
    fclose(pf);
    pf = fopen(BookDataPath, "w");
    Book *curBook = bs->firstBook;
    while (curBook) {
        fprintf(pf, "%d\t%s\t%s\t%s\t%d\t%d\t%f\t%d\t%d\t%d\t%d\n",
                curBook->id, curBook->isbn, curBook->title, curBook->author,
                curBook->createdTime, curBook->updatedTime, curBook->price,
                curBook->scanNum, curBook->location.floor, curBook->location.bookshelfNum,
                curBook->location.bookshelfFloor
        );
        curBook = curBook->next;
    }
    fclose(pf);
}

//4.更新图书管理系统信息
void updateBookSystem(BookSystem *bs) {
    cout << "作者\t创建时间\t当前书籍数量" << endl;
    printf("\t%s\t%d\t%d\n", bs->author, bs->createdTime, bs->bookTotal);
    cout << "修改作者(-1不修改)：";
    char author[20];
    cin >> author;
    strcmp(author, "-1") != 0 && (strcpy(bs->author, author));
    cout << "更新成功";
    cout << "作者\t创建时间\t当前书籍数量" << endl;
    printf("\t%s\t%d\t%d\n", bs->author, bs->createdTime, bs->bookTotal);
}

//读取图书数据库
Boolean readBookSystem(BookSystem *bs) {
    FILE *pf = fopen(BookDataPath, "r");
    if (pf == nullptr) return 0;
    int i = 0;
    Book *curBook = (Book *) malloc(1 * sizeof(Book));
    while (true) {
        fscanf(pf, "%d\t%s\t%s\t%s\t%d\t%d\t%f\t%d\t%d\t%d\t%d\n",
               &curBook->id, curBook->isbn, curBook->title, curBook->author,
               &curBook->createdTime, &curBook->updatedTime, &curBook->price,
               &curBook->scanNum, &curBook->location.floor, &curBook->location.bookshelfNum,
               &curBook->location.bookshelfFloor
        );
        if (i == 0) {
            bs->firstBook = curBook;
            i = -1;
        }
        if (feof(pf)) {
            bs->lastBook = curBook;
            curBook->next = nullptr;
            break;
        } else {
            curBook->next = (Book *) malloc(1 * sizeof(Book));
            curBook = curBook->next;
        }
    }
    fclose(pf);
    return 1;
}

// 10.旧书出库
int dropBook(BookSystem *bs) {
    int targetId = -1;//更新的id
    cout << "请输入需要出库的图书id：";
    cin >> targetId;
    Book *targetBook = bs->firstBook;
    Book *targetBookPrevBook = bs->firstBook;
    while (targetBook && targetBook->id != targetId) {
        targetBookPrevBook = targetBook;
        targetBook = targetBook->next;
    }
    if (!targetBook) {
        printf("不存在");
        return 0;
    } else {
        targetBookPrevBook->next = targetBookPrevBook->next->next;
        bs->bookTotal--;
    }
    return 1;
}

//添加新图书(不保存到数据库) , mock是否模拟数据
//9.新书入库
Boolean insertBook(BookSystem *bs, Boolean mock) {
    if (mock) {
        Book *newBook = (Book *) malloc(sizeof(Book));
        newBook->id = getOnlyId(bs);
        getOnlyIsbn(&(newBook->isbn)[0], bs);
        strcpy(newBook->title, "书名");
        strcpy(newBook->author, "作者");
        int curTime = getTime();
        newBook->createdTime = curTime;
        newBook->updatedTime = curTime;
        newBook->price = 12.3 + bs->nextId;
        newBook->scanNum = newBook->id;
        newBook->location.floor = 1 + bs->nextId;
        newBook->location.bookshelfNum = 2 + bs->nextId;
        newBook->location.bookshelfFloor = 3 + bs->nextId;
        if (bs->firstBook) {
            bs->lastBook->next = newBook;
            bs->lastBook = newBook;
            bs->lastBook->next = nullptr;
        } else {
            bs->firstBook = newBook;
            bs->lastBook = newBook;
        }
    } else {
        printf("========添加新图书========\n");
        printf("书名\t作者\t价格\t存放楼层\t存放楼层书架号\t存放楼层书架层号\n");
        Book *newBook = (Book *) malloc(sizeof(Book));
        cin >> newBook->title >> newBook->author >> newBook->price >> newBook->location.floor >>
            newBook->location.bookshelfNum >> newBook->location.bookshelfFloor;
        int curTime = getTime();
        newBook->id = getOnlyId(bs);
        getOnlyIsbn(&(newBook->isbn)[0], bs);
        newBook->updatedTime = curTime;
        newBook->createdTime = curTime;
        newBook->scanNum = 0;
        newBook->next = nullptr;
        bs->lastBook->next = newBook;
        bs->lastBook = newBook;
    }
    bs->bookTotal++;

    return 1;
}

Book *getReverseBookHead(Book *curBook) {
    if (curBook == nullptr || curBook->next == nullptr) {
        return curBook;
    }

    Book *newHead = getReverseBookHead(curBook->next);
    curBook->next->next = curBook;
    curBook->next = nullptr;
    return newHead;
}

//5.逆序存储
void reverseBookList(BookSystem *bs) {
    bs->firstBook = getReverseBookHead(bs->firstBook);
}

//12.输出显示
Boolean printBookList(BookSystem *bs, int id) {
    if (id != -1) {
        //打印某本书
        Book *curBook = bs->firstBook;
        while (curBook && curBook->id != id) {
            curBook = curBook->next;
        }
        if (!curBook) {
            cout << "id为" << id << "的书本不存在";
        } else {
            cout << "id\t编号\t书名\t作者\t价格\t查阅人数\t存放楼层\t存放楼层书架号\t存放楼层书架层号\t创建时间\t更新时间" << endl;
            printf("%d\t%s\t%s\t%s\t%f\t%d\t%d\t%d\t%d\t%d\t%d\n", curBook->id, curBook->isbn, curBook->title,
                   curBook->author, curBook->price, curBook->scanNum,
                   curBook->location.floor, curBook->location.bookshelfNum, curBook->location.bookshelfFloor,
                   curBook->createdTime, curBook->updatedTime
            );
        }
    } else {
        Book *curBook = bs->firstBook;
        printf("id\t编号\t书名\t作者\t价格\t查阅人数\t存放楼层\t存放楼层书架号\t存放楼层书架层号\t创建时间\t更新时间\n");
        while (curBook) {
            printf("%d\t%s\t%s\t%s\t%f\t%d\t%d\t%d\t%d\t%d\t%d\n", curBook->id, curBook->isbn, curBook->title,
                   curBook->author, curBook->price, curBook->scanNum,
                   curBook->location.floor, curBook->location.bookshelfNum, curBook->location.bookshelfFloor,
                   curBook->createdTime, curBook->updatedTime
            );
            curBook = curBook->next;
        }
    }
    return 1;
}

// 3.修改图书信息表
Boolean updateBook(BookSystem *bs) {
    int updateId = -1;//更新的id
    cout << "请输入需要更新的id：";
    cin >> updateId;
    Book *targetBook = bs->firstBook;
    while (targetBook && targetBook->id != updateId) {
        targetBook = targetBook->next;
    }
    if (!targetBook) {
        //更新的不存在
        printf("不存在");
        return 0;
    } else {
        cout << "不修改则输入-1" << endl;
        cout << "书名\t作者\t价格\t存放楼层\t存放楼层书架号\t存放楼层书架层号" << endl;
        char title[20], author[20];
        float price;
        int floor, bookshelfNum, bookshelfFloor;
        scanf("%s %s %f %d %d %d", title, author, &price, &floor, &bookshelfNum, &bookshelfFloor);
        strcmp(title, "-1") != 0 && (strcpy(targetBook->title, title));
        strcmp(author, "-1") != 0 && (strcpy(targetBook->author, author));
        price != -1 && (targetBook->price = price);
        floor != -1 && (targetBook->location.floor = floor);
        bookshelfNum != -1 && (targetBook->location.bookshelfNum = bookshelfNum);
        bookshelfFloor != -1 && (targetBook->location.bookshelfFloor = bookshelfFloor);
        targetBook->updatedTime = getTime();//更新时间
    }
    return 1;
}

/*
 * sortType: id,price,scanNum,createdTime,updatedTime
 * asc: 1升序，0降序
 * */
//2.排序
Boolean sortBook(BookSystem *bs, char *sortKey, Boolean asc) {
    int totalBooks = bs->bookTotal;
    if (totalBooks == 0) return 1;
    Book *tmpPrev = nullptr;
    Book *tmpCurBook = nullptr;
    Book *tmptmpPrev = nullptr;
    Book *curBook = nullptr;
    Book *newBookListFirst = nullptr;
    Book *newBookListLast = nullptr;
    int templateValue = 0;
    while (bs->firstBook) {
        tmpPrev = bs->firstBook;
        tmpCurBook = tmpPrev;
        curBook = tmpPrev;

//        templateValue = curBook->[sortKey];

        if (strcmp(sortKey, "id") == 0) {
            templateValue = curBook->id;
        } else if (strcmp(sortKey, "price") == 0) {
            templateValue = curBook->price;
        } else if (strcmp(sortKey, "scanNum") == 0) {
            templateValue = curBook->scanNum;
        } else if (strcmp(sortKey, "createdTime") == 0) {
            templateValue = curBook->createdTime;
        } else if (strcmp(sortKey, "updatedTime") == 0) {
            templateValue = curBook->updatedTime;
        } else {
            printf("sortKey有问题");
            return 0;
        }
        while (true) {
            if (strcmp(sortKey, "id") == 0) {
                if ((asc && curBook->id < templateValue) || (!asc && curBook->id > templateValue)) {
                    tmpPrev = tmptmpPrev;
                    templateValue = curBook->id;
                    tmpCurBook = curBook;
                }
            } else if (strcmp(sortKey, "price") == 0) {
                if ((asc && curBook->price < templateValue) || (!asc && curBook->price > templateValue)) {
                    tmpPrev = tmptmpPrev;
                    templateValue = curBook->price;
                    tmpCurBook = curBook;
                }
            } else if (strcmp(sortKey, "scanNum") == 0) {
                if ((asc && curBook->scanNum < templateValue) || (!asc && curBook->scanNum > templateValue)) {
                    tmpPrev = tmptmpPrev;
                    templateValue = curBook->scanNum;
                    tmpCurBook = curBook;
                }
            } else if (strcmp(sortKey, "createdTime") == 0) {
                if ((asc && curBook->createdTime < templateValue) || (!asc && curBook->createdTime > templateValue)) {
                    tmpPrev = tmptmpPrev;
                    templateValue = curBook->createdTime;
                    tmpCurBook = curBook;
                }
            } else if (strcmp(sortKey, "updatedTime") == 0) {
                if ((asc && curBook->updatedTime < templateValue) || (!asc && curBook->updatedTime > templateValue)) {
                    tmpPrev = tmptmpPrev;
                    templateValue = curBook->updatedTime;
                    tmpCurBook = curBook;
                }
            }
            tmptmpPrev = curBook;
            curBook = curBook->next;
            if (!curBook) break;
        }
        if (tmpPrev == tmpCurBook) {
            //说明一轮下来最大的是bs的首元素
            bs->firstBook = bs->firstBook->next;
        } else {
            tmpPrev->next = tmpPrev->next->next;
        }
        tmpCurBook->next = nullptr;
        if (!newBookListFirst) {
            newBookListFirst = tmpCurBook;
            newBookListLast = tmpCurBook;
        } else {
            newBookListLast->next = tmpCurBook;
            newBookListLast = tmpCurBook;
        }
    }

    bs->firstBook = newBookListFirst;
    bs->lastBook = newBookListLast;
    return 1;
}


//查询最xx的图书
Book *getMostKeyBook(BookSystem *bs, const char *sortKey) {
    Book *curBook = bs->firstBook;
    Book *mostBook = curBook;
    int mostValue;
    if (strcmp(sortKey, "id") == 0) {
        mostValue = curBook->id;
        while (curBook) {
            if (curBook->id > mostValue) {
                mostValue = curBook->id;
                mostBook = curBook;
            }
            curBook = curBook->next;
        }
    } else if (strcmp(sortKey, "price") == 0) {
        mostValue = curBook->price;
        while (curBook) {
            if (curBook->price > mostValue) {
                mostValue = curBook->price;
                mostBook = curBook;
            }
            curBook = curBook->next;
        }
    } else if (strcmp(sortKey, "scanNum") == 0) {
        mostValue = curBook->scanNum;
        while (curBook) {
            if (curBook->scanNum > mostValue) {
                mostValue = curBook->scanNum;
                mostBook = curBook;
            }
            curBook = curBook->next;
        }
    } else if (strcmp(sortKey, "createdTime") == 0) {
        mostValue = curBook->createdTime;
        while (curBook) {
            if (curBook->createdTime > mostValue) {
                mostValue = curBook->createdTime;
                mostBook = curBook;
            }
            curBook = curBook->next;
        }
    } else if (strcmp(sortKey, "updatedTime") == 0) {
        mostValue = curBook->updatedTime;
        while (curBook) {
            if (curBook->updatedTime > mostValue) {
                mostValue = curBook->updatedTime;
                mostBook = curBook;
            }
            curBook = curBook->next;
        }
    } else {
        cout << "sortKey有问题";
        return nullptr;
    }

    return mostBook;

}
//去重，去除重复的书名
//11.图书去重
Boolean removeDuplicate(BookSystem *bs) {
    Book *curBook = bs->firstBook;
    Book *curcurBook;
    Book *tmpPrevBook;
    while (curBook) {
        tmpPrevBook = curBook;
        curcurBook = curBook->next;
        while (curcurBook) {
            if (strcmp(curBook->title, curcurBook->title) == 0) {
                tmpPrevBook->next = tmpPrevBook->next->next;
                bs->bookTotal--;
            } else {
                tmpPrevBook = curcurBook;
            }
            curcurBook = curcurBook->next;
        }
        curBook = curBook->next;
    }
    return 1;
}


//6.最贵图书
Book *getTheMostExpensiveBook(BookSystem *bs) {
    return getMostKeyBook(bs, "price");
}

//获取最佳位置图书，最佳位置 = 楼层最低 + 书架号最先 + 书架号中最下层
//8.最佳位置图书
Book *getTheMostLocationBook(BookSystem *bs) {
    Book *curBook = bs->firstBook;
    Book *targetBook = nullptr;
    int floor = bs->firstBook->location.floor;
    int bookshelfNum = bs->firstBook->location.bookshelfNum;
    int bookshelfFloor = bs->firstBook->location.bookshelfFloor;
    //获取最小的floor
    while (curBook) {
        if (curBook->location.floor < floor) {
            floor = curBook->location.floor;
        }
        curBook = curBook->next;
    }
    //基于最小的floor，获取最小的bookshelfNum
    curBook = bs->firstBook;
    while (curBook) {
        if (curBook->location.floor == floor && curBook->location.bookshelfNum < bookshelfNum) {
            bookshelfNum = curBook->location.bookshelfNum;
        }
        curBook = curBook->next;
    }
    //基于最小的floor和bookshelfNum，获取最小的bookshelfFloor
    curBook = bs->firstBook;
    while (curBook) {
        if (curBook->location.floor == floor && curBook->location.bookshelfNum == bookshelfNum &&
            curBook->location.bookshelfFloor < bookshelfFloor) {
            bookshelfFloor = curBook->location.bookshelfFloor;
        }
        curBook = curBook->next;
    }
    //开始查找
    curBook = bs->firstBook;
    while (curBook) {
        if (curBook->location.floor == floor && curBook->location.bookshelfNum == bookshelfNum &&
            curBook->location.bookshelfFloor == bookshelfFloor) {
            targetBook = curBook;
        }
        curBook = curBook->next;
    }
    return targetBook;
}

//7.获取最爱图书
Book *getFavoriteBook(BookSystem *bs) {
    return getMostKeyBook(bs, "scanNum");
}

int menu() {
    int c;
    cout << endl;
    cout << "                    *图书管理系统*                      " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "                 1.图书信息表创建与输出                   " << endl;
    cout << "                 2.排序                                " << endl;
    cout << "                 3.修改图书信息表                        " << endl;
    cout << "                 4.修改书籍信息                         " << endl;
    cout << "                 5.逆序存储                            " << endl;
    cout << "                 6.最贵图书                            " << endl;
    cout << "                 7.最爱图书                            " << endl;
    cout << "                 8.最佳位置图书                         " << endl;
    cout << "                 9.新书入库                            " << endl;
    cout << "                 10.旧书出库                           " << endl;
    cout << "                 11.图书去重                           " << endl;
    cout << "                 12.查看书籍列表                        " << endl;
    cout << "                 0.退出                                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << " 请输入选择：";
    cin >> c;
    return c;
}

//菜单
//0.图书信息表创建与输出 1.排序 2.修改图书信息表 3.修改书籍信息 4.逆序存储
//5.最贵图书查找 6.最爱图书查找 7.最佳图书位置查找 8.新图书入库
//9.旧图书出库 10.图书去重 11.打印书籍列表 -1.退出
enum TheOperationCode {
    o_exit,
    o_createBookSystem,
    o_sortBook,
    o_updateBookSystem,
    o_updateBook,
    o_reverseBookList,
    o_getTheMostExpensiveBook,
    o_getFavoriteBook,
    o_getTheMostLocationBook,
    o_insertBook,
    o_dropBook,
    o_removeDuplicate,
    o_printfBookList,

};

//菜单
void menu(BookSystem *bs) {
    int operationCode;
    int isExsit = 0;
    int isInitSystem = 0;//是否创建图书信息表
    while (!isExsit) {
        operationCode = menu();
        if (operationCode != o_createBookSystem && operationCode != o_exit && !isInitSystem) {
            cout << "注意: 还未创建图书信息表" << endl;
            continue;
        }
        switch (operationCode) {
            case o_createBookSystem:
                cout << "图书列表创建中……" << endl;
                createBookSystem(bs);
                isInitSystem = 1;
                printBookList(bs, -1);
                break;
            case o_sortBook:
                cout << "排序参数(序号:id ,价格:price,查阅人数:scanNum,入库时间:createdTime,图书更新时间:updatedTime ): ";
                char sortType[15];
                int asc;
                scanf("%s", sortType);
                printf("\n1是升序，0是降序：");
                cin >> asc;
                sortBook(bs, sortType, asc);
                printBookList(bs, -1);
                break;
            case o_updateBookSystem:
                updateBookSystem(bs);
                break;
            case o_updateBook:
                updateBook(bs);
                printBookList(bs, -1);
                break;
            case o_reverseBookList:
                reverseBookList(bs);
                printBookList(bs, -1);
                break;
            case o_getTheMostExpensiveBook:
                printBookList(bs, getTheMostExpensiveBook(bs)->id);
                break;
            case o_getFavoriteBook:
                printBookList(bs, getFavoriteBook(bs)->id);
                break;
            case o_getTheMostLocationBook:
                printBookList(bs, getTheMostLocationBook(bs)->id);
                break;
            case o_insertBook:
                insertBook(bs, 0);
                printBookList(bs, -1);
                break;
            case o_dropBook:
                dropBook(bs);
                printBookList(bs, -1);
                break;
            case o_removeDuplicate:
                removeDuplicate(bs);
                printBookList(bs, -1);
                break;
            case o_printfBookList:
                printBookList(bs, -1);
                break;
            case o_exit:
                isExsit = 1;
                break;
            default:
                cout << "操作码有误" << endl;
        }
        if (isInitSystem) {
            saveBookSystem(bs);//保存数据
        }

    }
}

int main() {
    BookSystem *bs;
    bs = (BookSystem *) malloc(1 * sizeof(BookSystem));
    menu(bs);
}

