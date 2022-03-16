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

//ͼ�����ϵͳ�ļ�·��
const char *SystemPath = "./book_system.txt";

//ͼ�������ļ�·��
const char *BookDataPath = "./book_data.txt";

//λ����Ϣ
typedef struct LocationInfo {
    int floor;//���¥��
    int bookshelfNum;//���¥����ܺ�
    int bookshelfFloor;//���¥����ܲ��
} Location;

//�鼮��Ϣ
typedef struct BookInfo {
    int id;//�鼮id
    char isbn[20];//���
    char title[20];//����
    char author[20];//����
    int createdTime;//����ʱ��
    int updatedTime;//�޸�ʱ��
    float price;//�۸�
    int scanNum;//��������
    Location location;//λ����Ϣ
    struct BookInfo *next;//��һ����
} Book;

//ͼ��ϵͳ��Ϣ
typedef struct BookSystem {
    int createdTime;//ͼ��ϵͳ����ʱ��
    char author[20];//����
    int bookTotal;//��ǰ�鼮����
    int nextId;//����ͼ��ʱ��ȡ��id
    Book *firstBook;//��һ����
    Book *lastBook;//���һ����
} BookSystem;

Boolean readBookSystem(BookSystem *);

Boolean insertBook(BookSystem *, int);

void saveBookSystem(BookSystem *);

//��ȡΨһid
int getOnlyId(BookSystem *bs) {
    return bs->nextId++;
}

//��ȡΨһ��isbn
void getOnlyIsbn(char *target, BookSystem *bs) {
    itoa(2022 + bs->nextId, target, 10);
}

//��ȡ��ǰʱ���
int getTime() {
    time_t t;
    t = time(nullptr);
//    int now_time = int(time(&t));
    return time(&t);
}

// 1. ����ͼ�����ϵͳ
Boolean createBookSystem(BookSystem *bs) {
    FILE *pf = fopen(SystemPath, "r");
    if (pf != nullptr) {
        //1���Ѿ��������ˣ�ֱ�Ӷ�ȡ
        fscanf(pf, "createdTime: %d\nauthor: %s\nbookTotal:%d\nnextId: %d\n", &bs->createdTime, bs->author,
               &bs->bookTotal,
               &bs->nextId);
        fclose(pf);
        //��ȡͼ����Ϣ�б�
        readBookSystem(bs);
    } else {
        //2.��ȡʧ�ܣ��½�һ��
        fclose(pf);
        bs->createdTime = getTime();
        strcpy(bs->author, "vanxizzz");
        bs->nextId = 0;
        bs->bookTotal = 0;
        bs->firstBook = nullptr;
        bs->lastBook = nullptr;
        for (int i = 0; i < 5; ++i) {
            insertBook(bs, 1);//ģ��ͼ�����
        }
        saveBookSystem(bs);//���浽�ļ���
    }
    return 1;
}

//���浽���ݿ���
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

//4.����ͼ�����ϵͳ��Ϣ
void updateBookSystem(BookSystem *bs) {
    cout << "����\t����ʱ��\t��ǰ�鼮����" << endl;
    printf("\t%s\t%d\t%d\n", bs->author, bs->createdTime, bs->bookTotal);
    cout << "�޸�����(-1���޸�)��";
    char author[20];
    cin >> author;
    strcmp(author, "-1") != 0 && (strcpy(bs->author, author));
    cout << "���³ɹ�";
    cout << "����\t����ʱ��\t��ǰ�鼮����" << endl;
    printf("\t%s\t%d\t%d\n", bs->author, bs->createdTime, bs->bookTotal);
}

//��ȡͼ�����ݿ�
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

// 10.�������
int dropBook(BookSystem *bs) {
    int targetId = -1;//���µ�id
    cout << "��������Ҫ�����ͼ��id��";
    cin >> targetId;
    Book *targetBook = bs->firstBook;
    Book *targetBookPrevBook = bs->firstBook;
    while (targetBook && targetBook->id != targetId) {
        targetBookPrevBook = targetBook;
        targetBook = targetBook->next;
    }
    if (!targetBook) {
        printf("������");
        return 0;
    } else {
        targetBookPrevBook->next = targetBookPrevBook->next->next;
        bs->bookTotal--;
    }
    return 1;
}

//�����ͼ��(�����浽���ݿ�) , mock�Ƿ�ģ������
//9.�������
Boolean insertBook(BookSystem *bs, Boolean mock) {
    if (mock) {
        Book *newBook = (Book *) malloc(sizeof(Book));
        newBook->id = getOnlyId(bs);
        getOnlyIsbn(&(newBook->isbn)[0], bs);
        strcpy(newBook->title, "����");
        strcpy(newBook->author, "����");
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
        printf("========�����ͼ��========\n");
        printf("����\t����\t�۸�\t���¥��\t���¥����ܺ�\t���¥����ܲ��\n");
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

//5.����洢
void reverseBookList(BookSystem *bs) {
    bs->firstBook = getReverseBookHead(bs->firstBook);
}

//12.�����ʾ
Boolean printBookList(BookSystem *bs, int id) {
    if (id != -1) {
        //��ӡĳ����
        Book *curBook = bs->firstBook;
        while (curBook && curBook->id != id) {
            curBook = curBook->next;
        }
        if (!curBook) {
            cout << "idΪ" << id << "���鱾������";
        } else {
            cout << "id\t���\t����\t����\t�۸�\t��������\t���¥��\t���¥����ܺ�\t���¥����ܲ��\t����ʱ��\t����ʱ��" << endl;
            printf("%d\t%s\t%s\t%s\t%f\t%d\t%d\t%d\t%d\t%d\t%d\n", curBook->id, curBook->isbn, curBook->title,
                   curBook->author, curBook->price, curBook->scanNum,
                   curBook->location.floor, curBook->location.bookshelfNum, curBook->location.bookshelfFloor,
                   curBook->createdTime, curBook->updatedTime
            );
        }
    } else {
        Book *curBook = bs->firstBook;
        printf("id\t���\t����\t����\t�۸�\t��������\t���¥��\t���¥����ܺ�\t���¥����ܲ��\t����ʱ��\t����ʱ��\n");
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

// 3.�޸�ͼ����Ϣ��
Boolean updateBook(BookSystem *bs) {
    int updateId = -1;//���µ�id
    cout << "��������Ҫ���µ�id��";
    cin >> updateId;
    Book *targetBook = bs->firstBook;
    while (targetBook && targetBook->id != updateId) {
        targetBook = targetBook->next;
    }
    if (!targetBook) {
        //���µĲ�����
        printf("������");
        return 0;
    } else {
        cout << "���޸�������-1" << endl;
        cout << "����\t����\t�۸�\t���¥��\t���¥����ܺ�\t���¥����ܲ��" << endl;
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
        targetBook->updatedTime = getTime();//����ʱ��
    }
    return 1;
}

/*
 * sortType: id,price,scanNum,createdTime,updatedTime
 * asc: 1����0����
 * */
//2.����
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
            printf("sortKey������");
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
            //˵��һ������������bs����Ԫ��
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


//��ѯ��xx��ͼ��
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
        cout << "sortKey������";
        return nullptr;
    }

    return mostBook;

}
//ȥ�أ�ȥ���ظ�������
//11.ͼ��ȥ��
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


//6.���ͼ��
Book *getTheMostExpensiveBook(BookSystem *bs) {
    return getMostKeyBook(bs, "price");
}

//��ȡ���λ��ͼ�飬���λ�� = ¥����� + ��ܺ����� + ��ܺ������²�
//8.���λ��ͼ��
Book *getTheMostLocationBook(BookSystem *bs) {
    Book *curBook = bs->firstBook;
    Book *targetBook = nullptr;
    int floor = bs->firstBook->location.floor;
    int bookshelfNum = bs->firstBook->location.bookshelfNum;
    int bookshelfFloor = bs->firstBook->location.bookshelfFloor;
    //��ȡ��С��floor
    while (curBook) {
        if (curBook->location.floor < floor) {
            floor = curBook->location.floor;
        }
        curBook = curBook->next;
    }
    //������С��floor����ȡ��С��bookshelfNum
    curBook = bs->firstBook;
    while (curBook) {
        if (curBook->location.floor == floor && curBook->location.bookshelfNum < bookshelfNum) {
            bookshelfNum = curBook->location.bookshelfNum;
        }
        curBook = curBook->next;
    }
    //������С��floor��bookshelfNum����ȡ��С��bookshelfFloor
    curBook = bs->firstBook;
    while (curBook) {
        if (curBook->location.floor == floor && curBook->location.bookshelfNum == bookshelfNum &&
            curBook->location.bookshelfFloor < bookshelfFloor) {
            bookshelfFloor = curBook->location.bookshelfFloor;
        }
        curBook = curBook->next;
    }
    //��ʼ����
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

//7.��ȡ�ͼ��
Book *getFavoriteBook(BookSystem *bs) {
    return getMostKeyBook(bs, "scanNum");
}

int menu() {
    int c;
    cout << endl;
    cout << "                    *ͼ�����ϵͳ*                      " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "                 1.ͼ����Ϣ���������                   " << endl;
    cout << "                 2.����                                " << endl;
    cout << "                 3.�޸�ͼ����Ϣ��                        " << endl;
    cout << "                 4.�޸��鼮��Ϣ                         " << endl;
    cout << "                 5.����洢                            " << endl;
    cout << "                 6.���ͼ��                            " << endl;
    cout << "                 7.�ͼ��                            " << endl;
    cout << "                 8.���λ��ͼ��                         " << endl;
    cout << "                 9.�������                            " << endl;
    cout << "                 10.�������                           " << endl;
    cout << "                 11.ͼ��ȥ��                           " << endl;
    cout << "                 12.�鿴�鼮�б�                        " << endl;
    cout << "                 0.�˳�                                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << " ������ѡ��";
    cin >> c;
    return c;
}

//�˵�
//0.ͼ����Ϣ��������� 1.���� 2.�޸�ͼ����Ϣ�� 3.�޸��鼮��Ϣ 4.����洢
//5.���ͼ����� 6.�ͼ����� 7.���ͼ��λ�ò��� 8.��ͼ�����
//9.��ͼ����� 10.ͼ��ȥ�� 11.��ӡ�鼮�б� -1.�˳�
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

//�˵�
void menu(BookSystem *bs) {
    int operationCode;
    int isExsit = 0;
    int isInitSystem = 0;//�Ƿ񴴽�ͼ����Ϣ��
    while (!isExsit) {
        operationCode = menu();
        if (operationCode != o_createBookSystem && operationCode != o_exit && !isInitSystem) {
            cout << "ע��: ��δ����ͼ����Ϣ��" << endl;
            continue;
        }
        switch (operationCode) {
            case o_createBookSystem:
                cout << "ͼ���б����С���" << endl;
                createBookSystem(bs);
                isInitSystem = 1;
                printBookList(bs, -1);
                break;
            case o_sortBook:
                cout << "�������(���:id ,�۸�:price,��������:scanNum,���ʱ��:createdTime,ͼ�����ʱ��:updatedTime ): ";
                char sortType[15];
                int asc;
                scanf("%s", sortType);
                printf("\n1������0�ǽ���");
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
                cout << "����������" << endl;
        }
        if (isInitSystem) {
            saveBookSystem(bs);//��������
        }

    }
}

int main() {
    BookSystem *bs;
    bs = (BookSystem *) malloc(1 * sizeof(BookSystem));
    menu(bs);
}

