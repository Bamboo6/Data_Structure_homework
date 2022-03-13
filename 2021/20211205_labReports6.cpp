//
// Created by Tou on 2021/12/5.
//

#include <iostream>

using namespace std;

#define MVNum 100                            //最大顶点数
#define MAXQSIZE 100                        //最大队列长度
typedef char VerTexType;                    //假设顶点的数据类型为字符型
typedef int ArcType;                        //假设边的权值类型为整型

//------------图的邻接矩阵------------------
typedef struct {
    VerTexType vexs[MVNum];                    //顶点表
    ArcType arcs[MVNum][MVNum];            //邻接矩阵
    int vexnum, arcnum;                        //图的当前点数和边数
} Graph;

bool visited[MVNum];                        //访问标志数组，其初值为"false"

int LocateVex(Graph G, VerTexType v) {
    //确定点v在G中的位置
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
}//LocateVex

//----队列的定义及操作--------
typedef struct {
    ArcType *base;                            //初始化的动态分配存储空间
    int front;                                //头指针，若队列不空，指向队头元素
    int rear;                                //尾指针，若队列不空，指向队尾元素的下一个位置
} sqQueue;

//-------------图的邻接表---------------------
typedef struct ArcNode {                        //边结点
    int adjvex;                            //该边所指向的顶点的位置
    struct ArcNode *nextarc;                //指向下一条边的指针
} ArcNode;

typedef struct VNode {
    VerTexType data;                        //顶点信息
    ArcNode *firstarc;                        //指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];                    //AdjList表示邻接表类型

typedef struct {
    AdjList vertices;                        //邻接表
    int vexnum, arcnum;                    //图的当前顶点数和边数
} ALGraph;

void InitQueue(sqQueue &Q) {
    //构造一个空队列Q
    Q.base = new ArcType[MAXQSIZE];
    if (!Q.base) exit(1);                //存储分配失败
    Q.front = Q.rear = 0;
}//InitQueue

void EnQueue(sqQueue &Q, ArcType e) {
    //插入元素e为Q的新的队尾元素
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
}//EnQueue

bool QueueEmpty(sqQueue Q) {
    //判断是否为空队
    if (Q.rear == Q.front)
        return true;
    return false;
}//QueueEmpty

void DeQueue(sqQueue &Q, ArcType &u) {
    //队头元素出队并置为u
    u = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
}//DeQueue


int LocateVex(ALGraph G, VerTexType v) {
    //确定点v在G中的位置
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vertices[i].data == v)
            return i;
    return -1;
}//LocateVex

// 创建邻接矩阵
void CreateUDN(Graph &G) {
    //采用邻接矩阵表示法，创建无向网G
    int i, j, k;
    cout << "请输入总顶点数，总边数，以空格隔开:";
    cin >> G.vexnum >> G.arcnum;                            //输入总顶点数，总边数
    cout << endl;

    cout << "输入点的名称，如a" << endl;

    for (i = 0; i < G.vexnum; ++i) {
        cout << "请输入第" << (i + 1) << "个点的名称:";
        cin >> G.vexs[i];                                    //依次输入点的信息
    }
    cout << endl;

    for (i = 0; i < G.vexnum; ++i)                            //初始化邻接矩阵，边的权值均置为极大值MaxInt
        for (j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = 0;
    cout << "输入边依附的顶点，如a b" << endl;
    for (k = 0; k < G.arcnum; ++k) {                            //构造邻接矩阵
        VerTexType v1, v2;
        cout << "请输入第" << (k + 1) << "条边依附的顶点:";
        cin >> v1 >> v2;                                    //输入一条边依附的顶点及权值
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);        //确定v1和v2在G中的位置，即顶点数组的下标
        G.arcs[j][i] = G.arcs[i][j] = 1;                    //置<v1, v2>的对称边<v2, v1>的权值为w
    }//for
}//CreateUDN

// 创建邻接表
void CreateUDG(ALGraph &G) {
    //采用邻接表表示法，创建无向图G
    int i, k;

    cout << "请输入总顶点数，总边数，以空格隔开:";
    cin >> G.vexnum >> G.arcnum;                //输入总顶点数，总边数
    cout << endl;

    cout << "输入点的名称，如a" << endl;

    for (i = 0; i < G.vexnum; ++i) {            //输入各点，构造表头结点表
        cout << "请输入第" << (i + 1) << "个点的名称:";
        cin >> G.vertices[i].data;            //输入顶点值
        G.vertices[i].firstarc = NULL;            //初始化表头结点的指针域为NULL
    }//for
    cout << endl;

    cout << "输入边依附的顶点，如a b" << endl;

    for (k = 0; k < G.arcnum; ++k) {                //输入各边，构造邻接表
        VerTexType v1, v2;
        int i, j;
        cout << "请输入第" << (k + 1) << "条边依附的顶点:";
        cin >> v1 >> v2;                        //输入一条边依附的两个顶点
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        //确定v1和v2在G中位置，即顶点在G.vertices中的序号

        ArcNode *p1 = new ArcNode;                //生成一个新的边结点*p1
        p1->adjvex = j;                        //邻接点序号为j
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        //将新结点*p1插入顶点vi的边表头部

        ArcNode *p2 = new ArcNode;                //生成另一个对称的新的边结点*p2
        p2->adjvex = i;                        //邻接点序号为i
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
        //将新结点*p2插入顶点vj的边表头部
    }//for
}//CreateUDG

void DFS_AL(ALGraph G, int v) {                        //图G为邻接表类型
    cout << G.vertices[v].data << "   ";
    visited[v] = true;                            //访问第v个顶点，并置访问标志数组相应分量值为true
    ArcNode *p = G.vertices[v].firstarc;        //p指向v的边链表的第一个边结点
    while (p != NULL) {                            //边结点非空
        int w = p->adjvex;                    //表示w是v的邻接点
        if (!visited[w]) DFS_AL(G, w);            //如果w未访问，则递归调用DFS
        p = p->nextarc;                            //p指向下一个边结点
    }
}//DFS

void DFS_AM(Graph G, int v) {
    //图G为邻接矩阵类型
    int w;
    cout << G.vexs[v] << "    ";
    visited[v] = true;        //访问第v个顶点，并置访问标志数组相应分量值为true
    for (w = 0; w < G.vexnum; w++)                            //依次检查邻接矩阵v所在的行
        if ((G.arcs[v][w] != 0) && (!visited[w])) DFS_AM(G, w); //G.arcs[v][w]!=0表示w是v的邻接点，如果w未访问，则递归调用DFS
}//DFS

int FirstAdjVex(Graph G, int v) {
    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if (G.arcs[v][i] == 1 && !visited[i])
            return i;
    }
    return -1;
}//FirstAdjVex

int NextAdjVex(Graph G, int v, int w) {
    int i;
    for (i = w; i < G.vexnum; ++i) {
        if (G.arcs[v][i] == 1 && !visited[i])
            return i;
    }
    return -1;
}//NextAdjVex

void BFS(Graph G, int v) {
    //按广度优先非递归遍历连通图G
    sqQueue Q;
    ArcType u;
    ArcType w;

    cout << G.vexs[v] << "  ";
    visited[v] = true;                            //访问第v个顶点，并置访问标志数组相应分量值为true
    InitQueue(Q);                                                                //辅助队列Q初始化，置空
    EnQueue(Q, v);                                                                //v进队
    while (!QueueEmpty(Q)) {                                                    //队列非空
        DeQueue(Q, u);                                                        //队头元素出队并置为u
        for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {
            //依次检查u的所有邻接点w ，FirstAdjVex(G, u)表示u的第一个邻接点
            //NextAdjVex(G, u, w)表示u相对于w的下一个邻接点，w≥0表示存在邻接点
            if (!visited[w]) {                                                    //w为u的尚未访问的邻接顶点
                cout << G.vexs[w] << "  ";
                visited[w] = true;                    //访问w，并置访问标志数组相应分量值为true
                EnQueue(Q, w);                                                    //w进队
            }//if
        }//for
    }//while
}//BFS

// 采用邻接表表示图的深度优先搜索遍历
void UDG(ALGraph G) {
    CreateUDG(G);
    cout << endl;
    cout << "无向连通图G创建完成！" << endl << endl;

    cout << "请输入遍历连通图的起始点：";
    VerTexType c;
    cin >> c;

    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if (c == G.vertices[i].data)
            break;
    }
    cout << endl;
    while (i >= G.vexnum) {
        cout << "该点不存在，请重新输入！" << endl;
        cout << "请输入遍历连通图的起始点：";
        cin >> c;
        for (i = 0; i < G.vexnum; ++i) {
            if (c == G.vertices[i].data)
                break;
        }
    }
}

// 采用邻接矩阵表示图的深度优先搜索遍历
void UDN(Graph G) {
    CreateUDN(G);
    cout << endl;
    cout << "无向图G创建完成！" << endl << endl;

    cout << "请输入遍历无向图G的起始点：";
    VerTexType c;
    cin >> c;

    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if (c == G.vexs[i])
            break;
    }
    cout << endl;
    while (i >= G.vexnum) {
        cout << "该点不存在，请重新输入！" << endl;
        cout << "请输入遍历连通图的起始点：";
        cin >> c;
        for (i = 0; i < G.vexnum; ++i) {
            if (c == G.vexs[i])
                break;
        }
    }
}

void UDGDFSTraverse(ALGraph G) {
    int i;
    for (i=0; i<G.vexnum; ++i){
        visited[i] = 0;  //初始化访问数组visited的元素值为false
    }
    for (i=0; i<G.vexnum; ++i){
        if(!visited[i]){ //节点尚未访问
            DFS_AL(G,i);
        }
    }
}

void UDNDFSTraverse(Graph G) {
    int i;
    for (i = 0; i < G.vexnum; ++i)
        visited[i] = 0;

    for (i = 0; i < G.vexnum; ++i) {
        if (!visited[i])
            DFS_AM(G, i);
    }
}

int menu() {
    int c;
    cout << "1.创建邻接表；" << endl;
    cout << "2.创建邻接矩阵；" << endl;
    cout << "3.以邻接表形式存储的图的深度优先遍历；" << endl;
    cout << "4.以邻接表形式存储的图的广度优先遍历；" << endl;
    cout << "5.以邻接矩阵形式存储的图的深度优先遍历；" << endl;
    cout << "6.以邻接矩阵形式存储的图的广度优先遍历；" << endl;
    cout << "7.退出程序\n" << endl;
    cout << "选择：";
    cin >> c;
    return c;
}

int main() {
    Graph G;
    ALGraph AG;
    while (true) {
        switch (menu()) {
            case 1: {
                UDG(AG);
                break;
            }
            case 2: {
                UDN(G);
                break;
            }

            case 3: {
                cout << "以邻接表形式存储的图的深度优先遍历无向图G结果：" << endl;
                UDGDFSTraverse(AG);
                cout << endl;
                break;
            }
            case 4: {
                cout << "以邻接表形式存储的图的广度优先遍历无向图G结果：" << endl;
//                UDGBFSTraverse(AG);
                cout << endl;
                break;
            }
            case 5: {
                cout << "以邻接矩阵形式存储的图的深度优先遍历无向图G结果：" << endl;
                UDNDFSTraverse(G);
                cout << endl;
                break;
            }
            case 6: {
                cout << "以邻接矩阵形式存储的图的深度优先遍历无向图G结果：" << endl;
//                UDNBFSTraverse(G);
                cout << endl;
                break;
            }
            case 7: {
                cout << "退出成功\n" << endl;
                exit(0);
            }
            default: {
                break;
            }
        }
    }
}