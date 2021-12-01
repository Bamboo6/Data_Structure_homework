//
// Created by Tou on 2021/12/1.
//
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

struct Node {
    int lchild, rchild, parent;
    int weight;//权值
    string ch;//存储结点表示的字符(对于叶子结点）
    string code;//存储结点的编码(对于叶子结点）
};

class HuffmanTree {
public:
    void Select(Node huffTree[], int& min1, int& min2, int k);//找权值最小的两个字符合成“子树”
    void Huff_Tree(Node huffTree[], string str2, int n);//建树
    void Huff_Code(Node huffTree[], int n);//编码
    string Huff_Decode(Node huffTree[], int n, string s);//对字符串s解码
    string unique(string str);//对输入的str去重
};

void HuffmanTree::Select(Node huffTree[], int& min1, int& min2, int k) {//找权值最小的两个字符，min1和min2
    int weight = 0;
    for (int i = 0; i < k; i++) {//找最小的数min1
        if (huffTree[i].parent != -1)//判断节点是否已经选过
            continue;
        else {
            if (weight == 0) {
                weight = huffTree[i].weight;//先让weight有一个初始值
                min1 = i;
            }
            else {
                if (huffTree[i].weight < weight) {
                    weight = huffTree[i].weight;//比较求较小
                    min1 = i;
                }
            }
        }
    }
    weight = 0;
    for (int i = 0; i < k; i++) { //找“第二小”的数min2
        if (huffTree[i].parent != -1 || (i == min1))//排除已选过的数
            continue;
        else {
            if (weight == 0) {
                weight = huffTree[i].weight;
                min2 = i;
            }
            else {
                if (huffTree[i].weight < weight) {
                    weight = huffTree[i].weight;
                    min2 = i;
                }
            }
        }
    }
}

void HuffmanTree::Huff_Tree(Node huffTree[], string str2, int n) {//建树
    for (int i = 0; i < 2 * n - 1; i++) { //初始化（对于二叉哈夫曼树，若有n个叶子结点，则总共有2n-1个结点）
        huffTree[i].parent = -1;
        huffTree[i].lchild = -1;
        huffTree[i].rchild = -1;
        huffTree[i].code = "";
    }
    for (int i = 0; i < n; i++) {
        huffTree[i].ch = str2[i];
    }
    for (int k = n; k < 2 * n - 1; k++) {
        int i1 = 0, i2 = 0;
        Select(huffTree, i1, i2, k); //将i1，i2节点合成节点k
        huffTree[i1].parent = k;
        huffTree[i2].parent = k;
        huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
        huffTree[k].lchild = i1;
        huffTree[k].rchild = i2;
    }
}

void HuffmanTree::Huff_Code(Node huffTree[], int n) {//编码
    int i, j, k;
    string s = "";//初始化
    for (i = 0; i < n; i++) {
        s = "";
        j = i;
        while (huffTree[j].parent != -1) {//从叶子往上找到根节点
            k = huffTree[j].parent;
            if (j == huffTree[k].lchild) {
                s = s + "0";//如果是根的左孩子，则记为0
            }
            else {
                s = s + "1";//如果是根的右孩子，则记为1
            }
            j = huffTree[j].parent;
        }
        cout << huffTree[i].ch << ":";
        for (int len = s.size() - 1; len >= 0; len--) { //s“从后往前”（反序）输出，即为编码
            cout << s[len];
            huffTree[i].code += s[len]; //保存编码
        }
        cout << endl;
    }
}

string HuffmanTree::Huff_Decode(Node huffTree[], int n, string s) {
    string temp = "", str = "";//str用来保存解码后的字符串
    for (int i = 0; i < s.size(); i++) {
        temp = temp + s[i];
        for (int j = 0; j < n; j++) {
            if (temp == huffTree[j].code) {
                str = str + huffTree[j].ch;
                temp = "";//赋为“空”
                break;
            }
        }
    }
    return str;
}

string HuffmanTree::unique(string str) {//去重
    string temp;
    temp.append(str, 0, 1);//初始
    for (int i = 1, j = 0; i < str.length(); i++) {
        for (j = 0; j < temp.length(); j++) {
            if (temp[j] == str[i])//判断在temp中是否已有元素与str[i]相同
                break;
        }
        if (j == temp.length())//若无重复，在temp尾处添加str[i]
            temp.append(str, i, 1);
    }
    return temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string str, str2;
    cin >> str;
    HuffmanTree T;
    str2 = T.unique(str);
    sort(str2.begin(), str2.end());//对str2中的字符排序
    if (str2.size() == 1) { //如果str2只有一个元素（即str中所有元素都相同），则无法通过Select函数建树，单独考虑
        cout << str2 << ":" << 0 << endl;//编码为 0 ( 或 1)
        for (int i = 0; i < str.size(); ++i)  cout << 0;
        cout << endl;
        cout << str;//默认此时解码一定为本身,这里不经过 Huff_Decode解码函数，直接输出
    }
    else {
        int n = str2.size();
        Node* huffTree = new Node[2 * n - 1];
        for (int i = 0; i < str2.size(); ++i) {//计算权值（字符出现的频次）
            huffTree[i].weight = count(str.begin(), str.end(), str2[i]);
        }
        T.Huff_Tree(huffTree, str2, n);
        T.Huff_Code(huffTree, n);
        string s;
        for (int i = 0; i < str.size(); ++i) {
            for (int j = 0; j < str2.size(); ++j) {
                if (str2[j] == str[i]) {
                    cout << huffTree[j].code;//输出编码出来的密文
                    s += huffTree[j].code;//s用来储存密文
                }
            }
        }
        cout << endl;
        cout << T.Huff_Decode(huffTree, n, s);
    }
    return 0;
}

