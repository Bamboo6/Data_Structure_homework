//
// Created by Tou on 2021/12/1.
//

//
// Created by Tou on 2021/11/28.
//

#include <iostream>
#include <cstring>

using namespace std;


typedef struct {
    unsigned int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

HuffmanTree HT = NULL;                       /*HT为存放哈夫曼树的数组*/

//返回两个双亲域为0且权值最小的点的下标
void Select(HuffmanTree HT, int n, int &s1, int &s2) {
    /*n代表HT数组的长度
    */

    //前两个for循环找所有结点中权值最小的点（字符）
    for (int i = 1; i <= n; i++) {//利用for循环找出一个双亲为0的结点
        if (HT[i].parent == 0) {
            s1 = i;//s1初始化为i
            break;//找到一个后立即退出循环
        }
    }
    for (int i = 1; i <= n; i++) {/*利用for循环找到所有结点（字符）权值最小的一个
     并且保证该结点的双亲为0*/
        if (HT[i].weight < HT[s1].weight && HT[i].parent == 0)
            s1 = i;
    }
    //后两个for循环所有结点中权值第二小的点（字符）
    for (int i = 1; i <= n; i++) {//利用for循环找出一个双亲为0的结点，并且不能是s1
        if (HT[i].parent == 0 && i != s1) {
            s2 = i;//s2初始化为i
            break;//找到一个后立即退出循环
        }
    }

    for (int i = 1; i <= n; i++) {/*利用for循环找到所有结点（字符）权值第二小的一个，
     该结点满足不能是s1且双亲是0*/
        if (HT[i].weight < HT[s2].weight && HT[i].parent == 0 && i != s1)
            s2 = i;
    }

    int s3;
    if (s1 > s2) {
        s3 = s1;
        s1 = s2;
        s2 = s3;
    }      /*小的序号放在左边*/

}

//构造哈夫曼树
void CreateHuffmanTree(double *w, int n, char cha[]) {
/*-----------初始化工作-------------------------*/
    if (n <= 1)
        return;
    int m = 2 * n - 1;
    HT = new HTNode[m + 1];
    for (int i = 1; i <= m; ++i) {//将1~m号单元中的双亲，左孩子，右孩子的下标都初始化为0
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (int i = 1; i <= n; i++)         /*给所有终端结点赋初值*/
    {
        HT[i].weight = w[i];
    }
//    for (int i = 1; i <= n; ++i) {
//        cin >> HT[i].weight;//输入前n个单元中叶子结点的权值
//    }
/*-----------创建工作---------------------------*/
    int s1, s2;

    for (int i = n + 1; i <= m; ++i) {//通过n-1次的选择，删除，合并来构造哈夫曼树
        Select(HT, i - 1, s1, s2);
        /*cout << HT[s1].weight << " , " << HT[s2].weight << endl;*/
        /*将s1,s2的双亲域由0改为i
        (相当于把这两个结点删除了，这两个结点不再参与Select()函数)*/
        HT[s1].parent = i;
        HT[s2].parent = i;
        //s1,与s2分别作为i的左右孩子
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        //结点i的权值为s1,s2权值之和
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    for (int i = 1; i <= n * 2 - 1; i++) {
        cout << i << "\t" << cha[i] << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t"
             << HT[i].rchild << endl;
    }
    cout << endl;
}

//从叶子到根逆向求每个字符的哈夫曼编码，储存在编码表HC中
void CreatHuffmanCode(HuffmanCode &HC, int n, char cha[]) {
    HC = new char *[n + 1];//分配储存n个字符编码的编码表空间
    char *cd = new char[n];//分配临时存储字符编码的动态空间
    cd[n - 1] = '\0';//编码结束符
    for (int i = 1; i <= n; i++)//逐个求字符编码
    {
        int start = n - 1;//start 开始指向最后，即编码结束符位置
        int c = i;
        int f = HT[c].parent;//f指向结点c的双亲
        while (f != 0)//从叶子结点开始回溯，直到根结点
        {
            --start;//回溯一次，start向前指向一个位置
            if (HT[f].lchild == c) cd[start] = '0';//结点c是f的左孩子，则cd[start] = 0;
            else cd[start] = '1';//否则c是f的右孩子，cd[start] = 1
            c = f;
            f = HT[f].parent;//继续向上回溯
        }
        HC[i] = new char[n - start];//为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);//把求得编码的首地址从cd[start]复制到HC的当前行中
    }
    delete cd;


    for (int i = 1; i <= n; i++) {
        cout << i << "\t" << cha[i] << "\t" << HT[i].weight << "\t" << HC[i] << endl;
    }

    cout << endl;
}

//哈夫曼译码
void TranCode(HuffmanTree HT, int n, char cha[]) {
    /*
    HT是已经创建好的哈夫曼树
    a[]用来传入二进制编码
    b[]用来记录译出的字符
    zf[]是与哈夫曼树的叶子对应的字符（叶子下标与字符下标对应）
    n是字符个数，相当于zf[]数组得长度
    */
    char a[1000];
    char b[1000];
    cout << "输入二进制哈夫曼编码串:\n";
    cin >> a;

    int q = 2 * n - 1;//q初始化为根结点的下标
    int k = 0;//记录存储译出字符数组的下标
    int i = 0;
    for (i = 0; a[i] != '\0'; i++) {//for循环结束条件是读入的字符是结束符（二进制编码）
        //此代码块用来判断读入的二进制字符是0还是1
        if (a[i] == '0') {/*读入0，把根结点(HT[q])的左孩子的下标值赋给q
         下次循环的时候把HT[q]的左孩子作为新的根结点*/
            q = HT[q].lchild;
        } else if (a[i] == '1') {
            q = HT[q].rchild;
        }
        //此代码块用来判断HT[q]是否为叶子结点
        if (HT[q].lchild == 0 && HT[q].rchild == 0) {/*是叶子结点，说明已经译出一个字符
        该字符的下标就是找到的叶子结点的下标*/
            b[k++] = cha[q];//把下标为q的字符赋给字符数组b[]
            q = 2 * n - 1;//初始化q为根结点的下标
            //继续译下一个字符的时候从哈夫曼树的根结点开始
        }
    }
    /*译码完成之后，用来记录译出字符的数组由于没有结束符输出的
    时候回报错，故紧接着把一个结束符加到数组最后*/
    b[k] = '\0';
    cout << b << endl;
}

void HCode(HuffmanCode HC, int n, char ch[], int l, char cha[]) {
    string s = "";
    for (int i = 0; i < l; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ch[i] == cha[j]) {
                s += HC[j];
                break;
            }
        }
    }
    cout << "编码为：" << s << endl;
}

void huffmancode2(char cd[], HuffmanCode HC, int n, char cha[])  //自顶向下编译
{
    HC = new char *[n + 1];
    int i, p, cdlen = 0;
    p = 2 * n - 1;   //p指向根
    for (i = 1; i <= p; ++i) HT[i].weight = 0;  /*遍历哈夫曼树时用作结点状态标志*/
    while (p) {
        if (HT[p].weight == 0)               /*向左*/
        {
            HT[p].weight = 1;
            if (HT[p].lchild != 0) {
                p = HT[p].lchild;
                cd[cdlen++] = '0';
            } else if (HT[p].lchild == 0)   /*登记叶子结点的字符编码*/
            {
                HC[p] = new char[cdlen + 1];
                /*为第i个字符编码分配空间*/
                cd[cdlen] = '\0';
                strcpy(HC[p], cd);            /*从cd复制编码串到HC*/
                cout << p << "\t" << cha[p] << "\t" << HT[p].weight << "\t" << HC[p] << endl;
            }
        } else if (HT[p].weight == 1)            /*向右*/
        {
            HT[p].weight = 2;
            if (HT[p].rchild != 0) {
                p = HT[p].rchild;
                cd[cdlen++] = '1';
            }
        } else                       /*HT[p].weight==2，退回*/
        { //HT[p].weight=0;
            p = HT[p].parent;
            --cdlen;                 /*退到父结点，编码长度减1*/
        }
    }
}

int menu() {
    int c;
    cout << "1.以26个英文字母的频率为权构造一棵哈夫曼树;" << endl;
    cout << "2.自底向上进行编码;" << endl;
    cout << "3.自顶向下进行编码;" << endl;
    cout << "4.对输入的文字（自己任意选择一句英语）编码;" << endl;
    cout << "5.对输入的二进制串译码;" << endl;
    cout << "6.退出程序\n" << endl;
    cout << "选择：";
    cin >> c;
    return c;
}

int main() {
    int i, n = 26;               // w数组用于存放各终端结点的权值
    char cd[99];          // cd存放编码数组，cha存放各终端结点的数据
    char ch[1000];
    HuffmanCode HC;          // HC用来存放编码串
    char cha[99] = "0ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    double w[27] = {0, 11.88312, 8.181818, 7.207792, 7.012987, 6.948052, 6.623377, 5.38961, 5.324675, 5.194805,
                    4.935065, 3.636364, 3.506494, 3.311688, 3.311688, 2.662338, 2.597403, 2.402597, 2.337662, 2.337662,
                    1.948052, 1.753247, 0.974026, 0.25974, 0.12987, 0.064935, 0.064935};

    while (1) {
        switch (menu()) {
            case 1: {
                CreateHuffmanTree(w, n, cha);
                break;
            }

            case 2: {
                CreatHuffmanCode(HC, n, cha);
                break;
            }

            case 3: {
                huffmancode2(cd, HC, n, cha);
                break;
            }
            case 4: {
                cout << "请输入一句英语: \n";
                cin >> ch;
                int l = strlen(ch);
                HCode(HC, n, ch, l, cha);
                break;
            }
            case 5: {
                TranCode(HT, n, cha);        //调用为哈夫曼树译码的函数
                break;
            }
            case 6:
                cout << "退出成功\n" << endl;
                exit(0);
            default:
                break;
        }
    }
}

