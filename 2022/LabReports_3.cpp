//
// Created by Tou on 2022/4/2.
//

#include <cstring>
#include "iostream"

using namespace std;

//停车场最大容量
#define MAX 5
//车位没车辆时显示的占位符
#define emptyPlaceholder "空"

//时间结构体
typedef struct time {
    string locTime;
} Time;

//车辆信息结构体
typedef struct node {
    string num;
    Time arrive;
//    Time leave;
} CarNode;

typedef struct NODE {
    CarNode *stack[MAX + 1];
//    栈顶指针索引
    int top;
//    真实车辆数
    int realStackCount;
} SeqStackCar;

typedef struct car {
    CarNode *data;
    struct car *next;
} QueueNode;

//便道队列
typedef struct Node {
    QueueNode *head;
    QueueNode *rear;
} LinkQueueCar;

//栈的初始化
void InitStack(SeqStackCar *s) {
    int i;
    s->top = s->realStackCount = 0;
    for (i = 0; i <= MAX; i++) {
        s->stack[s->top] = nullptr;
    }
}

//队列的初始化
int InitQueue(LinkQueueCar *Q) {
//    Q->head = (QueueNode *) malloc(sizeof(QueueNode));
//    if (Q->head != nullptr) {
//        Q->head->next = nullptr;
//        Q->rear = Q->head;
//        return (1);
//    } else {
//        return (-1);
//    }
    Q->head = Q->rear = nullptr;
    return 1;
}

string nowTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    string nowTime[3];
    nowTime[0] = to_string(ltm->tm_hour);
    nowTime[1] = to_string(ltm->tm_min);
    nowTime[2] = to_string(ltm->tm_sec);
    for (auto &i: nowTime) {
        if (i.length() != 2) {
//            i = "0" + i;
            i.insert(0, "0");
        }
    }
    int i = 0;
    while (i < 3) {
//        cout << nowTime[i] << "------" << nowTime[i].length() << endl;
        if (nowTime[i].length() != 2) {
            nowTime[i] = "0" + nowTime[i];
        }
//        cout << nowTime[i] << endl;
        i++;
    }
    string finalTime = nowTime[0] + ":" + nowTime[1] + ":" + nowTime[2];
//    cout << "++++++" << finalTime << endl;
    return finalTime;
//    SYSTEMTIME sys;
//    GetLocalTime(&sys);
//    for (auto & i : nowTime) {
//        if (i.length()!=2){
//            i += "0";
//        }
//    }
//    static string nowTime[3] = {sys.wHour, sys.wMinute, sys.wSecond};
    //输出结构中的内容
//    cout<<"Year:"<<1900+ltm->tm_year<<endl;
//    cout<<"Month:"<<1+ltm->tm_mon<<endl;
//    cout<<"Day: "<<ltm->tm_mday << endl;
//    cout<<"Time: "<< ltm->tm_hour << ":";
//    cout << ltm->tm_min << ":";
//    cout << ltm->tm_sec << endl;
}

void arrive(SeqStackCar *Enter, LinkQueueCar *W, SeqStackCar *Temp) {
    CarNode *p;
    QueueNode *t;
//    p = (CarNode *) malloc(sizeof(CarNode));
//    https://blog.51cto.com/liuzhangheng/1436164
    p = new CarNode;
    cout << "请输入车牌号:";
    cin >> p->num;
    if (Enter->realStackCount < MAX) {
        //把要删除的车辆的前面的车开出来，进临时栈
        while (Enter->stack[Enter->top] != nullptr && Enter->stack[Enter->top]->num != emptyPlaceholder) {
            Temp->top++;
            Temp->stack[Temp->top] = Enter->stack[Enter->top];
            Enter->stack[Enter->top] = nullptr;
            Enter->top--;
        }
        if (Enter->top == 0) {
            //直接入栈，1，2，3满了，接下来入4
            //1.先把临时栈里德车辆进停车场
            while (Temp->top >= 1) {
                Enter->top++;
                Enter->stack[Enter->top] = Temp->stack[Temp->top];
                Temp->stack[Temp->top] = nullptr;
                Temp->top--;
            }
            //2.添加车辆
            Enter->top++;
            Enter->stack[Enter->top] = p;//加入
            p->arrive.locTime = nowTime();
            cout << "车辆在车场第 " << Enter->top << " 位置" << endl;
            cout << "车辆入场时间为：" << p->arrive.locTime;
        } else {
            //情况：1,空,3,4，进入2
            //1.先添加车辆
            Enter->stack[Enter->top] = p;//加入
            p->arrive.locTime = nowTime();
            cout << "车辆在车场第 " << Enter->top << " 位置" << endl;
            cout << "车辆入场时间为：" << p->arrive.locTime;
            //2.先把临时栈里德车辆进停车场
            while (Temp->top >= 1) {
                Enter->top++;
                Enter->stack[Enter->top] = Temp->stack[Temp->top];
                Temp->stack[Temp->top] = nullptr;
                Temp->top--;
            }
        }
        Enter->realStackCount++;
    } else {
        cout << "停车场已满，请进入便道等待。";
        t = new QueueNode;
        t->data = p;
        t->next = nullptr;
        if (W->head == nullptr) {
            W->head = W->rear = t;
        } else {
            W->rear->next = t;
            W->rear = t;
        }
    }
}

//显示车场里的车辆情况
void parkingLotList(SeqStackCar *S) {
    int i;
    if (S->top > 0) {
//        cout << "停车场：" << endl;
        cout << "位置" << "\t" << "车牌号" << "\t" << "入场时间" << endl;
        for (i = 1; i <= S->top; i++) {
            cout << i << "\t";
            cout << S->stack[i]->num << "\t";
            cout << S->stack[i]->arrive.locTime << endl;
//            cout << S->stack[i]->arrive.hour << ":"
//                 << S->stack[i]->arrive.min << ":"
//                 << S->stack[i]->arrive.sec << endl;
        }
    } else {
        cout << "停车场里没有车。" << endl;
    }
}

//显示便道上的车辆情况
void temporaryDrivewayList(LinkQueueCar *W) {
    QueueNode *p;
    int i;
    p = W->head;
    if (p == nullptr) {
        cout << "便道没有车。" << endl;
    } else {
        cout << "等待车辆的车牌号：" << endl;
        for (i = 1; (p != nullptr); i++) {
            cout << "第 " << i << " 辆车：";
            cout << p->data->num << endl;
            p = p->next;
        }
    }
}

//车辆离开登记
void leave(SeqStackCar *Enter, LinkQueueCar *W, SeqStackCar *Temp) {
//    车辆的离开
    int room;
    CarNode *p;
//    判断停车场是否为空
    if (Enter->realStackCount > 0) {
        while (true) {
            cout << "请输入车的位置（1--" << Enter->top << "）：";
            cin >> room;
            if (room >= 1 && room <= Enter->top && Enter->stack[room]->num != emptyPlaceholder) {
                cout << "车牌号为 " << Enter->stack[room]->num << " 的车辆已开出停车场。" << endl;
                break;
            } else {
                if (Enter->stack[room]->num == emptyPlaceholder) {
                    cout << "该车位没有车，请重新输入：";
                } else {
                    cout << "输入有误，请重新输入: ";
                }
            }
        }
//        把要删除的车辆的前面的车开出来，进临时栈
        while (Enter->top > room) {
            Temp->top++;
            Temp->stack[Temp->top] = Enter->stack[Enter->top];
            Enter->stack[Enter->top] = nullptr;
            Enter->top--;
        }
        p = Enter->stack[Enter->top];//需要离开的车辆
        p->num = emptyPlaceholder;
        p->arrive.locTime = "";
        Enter->realStackCount--;//真实车辆数 - 1
        if (W->head == nullptr) {
//            便道没有车辆
        } else {
//            便道有车辆
//            真实车辆数 + 1
            Enter->realStackCount++;
//            cout << W->head->data->num << endl;
            Enter->stack[Enter->top] = W->head->data;
            W->head = W->head->next;
            Enter->stack[Enter->top]->arrive.locTime = nowTime();
            cout << "车牌号为 " << Enter->stack[Enter->top]->num << " 的车辆进入停车场的 " << Enter->top << " 号车位。" << endl;
            cout << "车辆入场时间为：" << Enter->stack[Enter->top]->arrive.locTime << endl;
        }
//        再把临时栈里德车辆进停车场
        while (Temp->top >= 1) {
            Enter->top++;
            Enter->stack[Enter->top] = Temp->stack[Temp->top];
            Temp->stack[Temp->top] = nullptr;
            Temp->top--;
        }
    }
}

int menu() {
    int c;
    cout << endl;
    cout << endl;
    cout << "                   *欢迎使用停车场系统*                   " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "                  1.车辆入场登记                         " << endl;
    cout << "                  2.停车场车辆列表                       " << endl;
    cout << "                  3.便道车辆列表                         " << endl;
    cout << "                  4.车辆离开登记                         " << endl;
    cout << "                  0.退出                                " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "请输入选择：";
    cin >> c;
    return c;
}

enum operationCode {
    o_exit,
    o_arrive,
    o_parkingLotList,
    o_temporaryDrivewayList,
    o_leave,
};

int main() {
    int operationCode;
    int isExist = 0;
//    停车场栈、临时栈
    SeqStackCar Enter, Temp;
//    便道队列
    LinkQueueCar Wait;
    InitStack(&Enter);
    InitStack(&Temp);
    InitQueue(&Wait);
    while (!isExist) {
        operationCode = menu();
        switch (operationCode) {
            case o_exit:
                isExist = -1;
                break;
            case o_arrive:
                arrive(&Enter, &Wait, &Temp);
                break;
            case o_parkingLotList:
                parkingLotList(&Enter);
                break;
            case o_temporaryDrivewayList:
                temporaryDrivewayList(&Wait);
                break;
            case o_leave:
                leave(&Enter, &Wait, &Temp);
                break;
            default:
                cout << "输入有误！" << endl;
        }
    }
}