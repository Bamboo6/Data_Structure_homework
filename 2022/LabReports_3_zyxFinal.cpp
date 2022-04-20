//
// Created by Tou on 2022/4/20.
//
#include <cstring>
#include "iostream"
#include "ctime"

using namespace std;
//停车场最大容量
#define MAX 3
//车位没车辆时显示的占位符
#define emptyPlaceholder "空位"
//时间结构体
typedef struct time {
    string locTime;//如02:34:11
} Time;
//车辆信息结构体
typedef struct node {
    string num;
    Time arrive;
} CarNode;
//停车场栈
typedef struct NODE {
    CarNode *stack[MAX + 1];
    int top;//栈顶指针索引
    int realStackLen;//真实车辆数
} SeqStackCar;
//便道队列中的节点
typedef struct car {
    CarNode *data;//车辆
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
    s->top = s->realStackLen = 0;
    for (i = 0; i <= MAX; i++) {
        s->stack[s->top] = nullptr;
    }
}

//队列的初始化
int InitQueue(LinkQueueCar *Q) {
    Q->head = Q->rear = nullptr;
    return 1;
}

//获取格式化时间模块，如返回08:12:44
string getFormatNowTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    string nowTime[3];
    nowTime[0] = to_string(ltm->tm_hour);
    nowTime[1] = to_string(ltm->tm_min);
    nowTime[2] = to_string(ltm->tm_sec);
    for (auto &i: nowTime) {
        if (i.length() != 2) {
            i.insert(0, "0");
        }
    }
    int i = 0;
    while (i < 3) {
        if (nowTime[i].length() != 2) {
            nowTime[i] = "0" + nowTime[i];
        }
        i++;
    }
    string finalTime = nowTime[0] + ":" + nowTime[1] + ":" + nowTime[2];
    return finalTime;
}

//车辆入场模块
void arrive(SeqStackCar *Enter, LinkQueueCar *W, SeqStackCar *Temp) {
    CarNode *p;
    QueueNode *t;
    p = new CarNode;
    cout << "请输入车牌号:";
    cin >> p->num;
    if (Enter->realStackLen < MAX) {
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
            p->arrive.locTime = getFormatNowTime();
            cout << "车辆在车场第 " << Enter->top << " 位置" << endl;
            cout << "车辆入场时间为：" << p->arrive.locTime;
        } else {
            //情况：1,空,3,4，进入2
            //1.先添加车辆
            Enter->stack[Enter->top] = p;//加入
            p->arrive.locTime = getFormatNowTime();
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
        Enter->realStackLen++;
    } else {
        cout << "停车场已满，请进入便道等待。";
        t = (QueueNode *) malloc(sizeof(QueueNode));
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

//停车场车辆列表模块
void parkingLotList(SeqStackCar *S) {
    int i;
    if (S->top > 0) {
        cout << "位置" << "\t" << "车牌号" << "\t" << "入场时间" << endl;
        for (i = 1; i <= S->top; i++) {
            cout << i << "\t";
            cout << S->stack[i]->num << "\t";
            cout << S->stack[i]->arrive.locTime << endl;
        }
    } else {
        cout << "停车场里没有车。" << endl;
    }
}

//便道车辆列表模块
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

//车辆离开登记模块
void leave(SeqStackCar *Enter, SeqStackCar *Temp, LinkQueueCar *W) {
    int room;
    CarNode *p;
    //判断停车场是否为空
    if (Enter->realStackLen > 0) {
        while (true) {
            cout << "请输入车的位置（1--" << Enter->top << "）：";
            cin >> room;
            if (room >= 1 && room <= Enter->top && Enter->stack[room]->num != emptyPlaceholder) {
                break;
            } else {
                if (Enter->stack[room]->num == emptyPlaceholder) {
                    cout << "该车位是空位，请重新输：";
                } else {
                    cout << "输入有误，请重新输: ";
                }
            }
        }
        // 把要删除的车辆的前面的车开出来，进临时栈
        while (Enter->top > room) {
            Temp->top++;
            Temp->stack[Temp->top] = Enter->stack[Enter->top];
            Enter->stack[Enter->top] = nullptr;
            Enter->top--;
        }
        p = Enter->stack[Enter->top];//需要离开的车辆
        p->num = emptyPlaceholder;
        p->arrive.locTime = "";
        Enter->realStackLen--;//真实车辆数 - 1
        if (W->head == nullptr) {
            //便道没有车辆
        } else {
            //便道有车辆
            Enter->realStackLen++;//真实车辆数 + 1
            cout << W->head->data->num << endl;
            Enter->stack[Enter->top] = W->head->data;
            W->head = W->head->next;
            Enter->stack[Enter->top]->arrive.locTime = getFormatNowTime();
            cout << "车牌号为 " << Enter->stack[Enter->top]->num << " 的车辆进入停车场的 " << Enter->top << " 号车位。" << endl;
            cout << "车辆入场时间为：" << Enter->stack[Enter->top]->arrive.locTime << endl;
        }
        //再把临时栈里德车辆进停车场
        while (Temp->top >= 1) {
            Enter->top++;
            Enter->stack[Enter->top] = Temp->stack[Temp->top];
            Temp->stack[Temp->top] = nullptr;
            Temp->top--;
        }
    }
}

//菜单模块
int menu() {
    int c;
    cout << endl;
    cout << endl;
    cout << "                   *停车场系统菜单*                   " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "0.退出 1.车辆入场登记 2.停车场车辆列表 " << endl;
    cout << "3.便道车辆列表 4.车辆离开登记" << endl;
    cout << "请输入菜单操作码(0-4)：";
    cin >> c;
    return c;
}

//操作
enum operationCode {
    o_exit,//退出
    o_arrive,//车辆到达
    o_parkingLotList,//显示当前停车场车辆列表
    o_temporaryDrivewayList,//显示当前便道车辆列表
    o_leave,//车辆离开
};

int main() {
    int operationCode;//操作码
    int isExist = 0;//是否退出
    SeqStackCar Enter;//停车场栈
    SeqStackCar Temp;//临时栈
    LinkQueueCar Wait;//便道队列
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
                leave(&Enter, &Temp, &Wait);
                break;
            default:
                cout << "输入有误！" << endl;
        }
    }
}
