//
// Created by Tou on 2021/11/28.
//

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef struct {
    unsigned int weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

HuffmanTree HT = NULL;                       /*HT为存放哈夫曼树的数组*/
void huffman(double *w, double n)/*建立哈夫曼树*/
{
    int m, i, j, k;
    int s1, s2, s3;
    if (n <= 1) return;
    m = 2 * n - 1;       /*n为叶子结点数，m为总结点数*/
    HT = new HTNode[m + 1]; //分配内存单元，0号单元未用
    for (i = 1; i <= n; i++)         /*给所有终端结点赋初值*/
    {
        HT[i].weight = w[i];
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    for (i = n + 1; i <= m; i++)      /*给所有非终端结点赋初值*/
    {
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    for (i = n + 1; i <= m; i++)        //构造后n-1个非终端结点
    {
        for (k = 1; k < i; k++)         //找到第一个双亲为0的结点，将序号给s1
        {
            if (HT[k].parent == 0)    //双亲为0的结点在F（森林）中
            {
                s1 = k;
                break;
            }
        }
        for (j = 1; j < i; j++)          //将权最小且双亲为0的结点的序号放到s1中
        {
            if (HT[j].parent != 0)continue;
            if (HT[s1].weight > HT[j].weight)s1 = j;
        }
        s2 = 0;
        for (k = 1; k < s1; k++)     /*找除s1以外的另一个双亲为0的结点，将序号给s2*/
        {
            if (HT[k].parent == 0)  /*以s1为界分两段找*/
            {
                s2 = k;
                break;
            }
        }
        if (s2 == 0) {
            for (k = s1 + 1; k < i; k++) {
                if (HT[k].parent == 0) {
                    s2 = k;
                    break;
                }
            }
        }
        for (j = 1; j < i; j++)              /*将权次小且双亲为0的结点的序号放到s2中*/
        {
            if (HT[j].parent != 0)continue;
            if (j == s1)continue;
            if (HT[s2].weight > HT[j].weight)s2 = j;
        }
        if (s1 > s2) {
            s3 = s1;
            s1 = s2;
            s2 = s3;
        }      /*小的序号放在左边*/
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    for (i = 1; i <= m; i++)   /*输出哈夫曼树*/
        cout << setw(5) << i << setw(5) << HT[i].weight << setw(5) << HT[i].parent <<
             setw(5) << HT[i].lchild << setw(5) << HT[i].rchild << endl;
}

void huffmancode1(char cd[], HuffmanCode HC, int n) //自底向上编译
{
    int start, c, i, f;
    cd[n - 1] = '\0';                        /*编码结束符*/
    cout << "对应的哈夫曼编码为:\n";
    for (i = 1; i <= n; i++)                   /*逐个字符求哈夫曼编码*/
    {
        start = n - 1;                         /*编码结束符位置*/
        for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) /*从叶子到根逆向求编码*/
        {
            if (HT[f].lchild == c)cd[--start] = '0';
            else cd[--start] = '1';
        }
        HC[i] = new char[n - start];    //为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);                      /*从cd复制编码串到HC*/
        cout << HC[i] << endl;
    }
}

void huffmancode2(char cd[], HuffmanCode HC, int n)  //自顶向下编译
{
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
                cout << p << "   " << HC[p] << endl;
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

void decode(char cha[], int n)
/*哈夫曼树译码*/
{
    char ym[99];
    int i, l, k = 2 * n - 1;          //从根结点往下走
    cout << "\n输入哈夫曼编码串长度:\n";
    cin >> l;
    cout << "输入哈夫曼编码串:\n";
    cin >> ym;
    for (i = 0; i < l; i++) {
        if (ym[i] == '0') k = HT[k].lchild;
        else k = HT[k].rchild;
        if (HT[k].lchild == 0)  //已经到了叶子结点
        {
            cout << cha[k];    //输出对应字符
            k = 2 * n - 1;         // k又指向根，2*n-1为根结点下标
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
//	double w[99];
//	int i,n=0;               // w数组用于存放各终端结点的权值
//  	char cd[99],ch,cha[99];        //cd存放编码数组，cha存放各终端结点的数据
//  	HuffmanCode HC;
    int i, n = 26;               // w数组用于存放各终端结点的权值
    char cd[99], ch;          // cd存放编码数组，cha存放各终端结点的数据
    HuffmanCode HC;          // HC用来存放编码串
    char cha[99] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    double w[27] = {0, 11.88312, 8.181818, 7.207792, 7.012987, 6.948052, 6.623377, 5.38961, 5.324675, 5.194805,
                    4.935065, 3.636364, 3.506494, 3.311688, 3.311688, 2.662338, 2.597403, 2.402597, 2.337662, 2.337662,
                    1.948052, 1.753247, 0.974026, 0.25974, 0.12987, 0.064935, 0.064935};

    while (1) {
        switch (menu()) {
            case 1: {
//  			      cout<<"请输入26个字母(以'#'结束):\n";
//		      for(i=1;;i++)
//				  {
//				  	cin>>ch;
//						    if(ch=='#') break;
//				    cha[i]=ch;n++;
//				  }
//				   cout<<"请输入26个字母对应的频率（权值）:\n";
//  				   for(i=1;i<=n;i++)
//					 cin>>w[i];
                huffman(w, n);         //调用建立哈夫曼树的函数
                break;
            }

            case 2: {
                HC = new char *[n + 1];
                huffmancode1(cd, HC, n); //调用为哈夫曼树编码的函数(自底向上)
                break;
            }

            case 3: {
                HC = new char *[n + 1];
                huffmancode2(cd, HC, n); //调用为哈夫曼树编码的函数(自顶向下)
                break;
            }
            case 4: {
                cout << "请输入一句英语:(以#结束)\n";
                for (i = 1; i <= n; i++) {
                    cin >> ch;
                    if (ch == '#') break;
                    cha[i] = ch;
                    n++;
                }
                HC = new char *[n];
                huffmancode1(cd, HC, n); //调用为哈夫曼树编码的函数(自底向上)
                break;
            }
            case 5: {
                decode(cha, n);        //调用为哈夫曼树译码的函数
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

