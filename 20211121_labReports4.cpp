//
// Created by Tou on 2021/11/21.
//

// 5-10(b)
// ABC##DE#G##F###
// 5.10(a)
// ABCD#####

//EBC##DA#G##F###

//ABD###CE#G##F##

//算法5.1 中序遍历的递归算法
#include<iostream>

using namespace std;
typedef struct BiNode {
    char data;
    struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

//用算法5.3 先序遍历的顺序建立二叉链表
void CreateBiTree(BiTree &T) {
    //按先序次序输入二叉树中结点的值（一个字符），创建二叉链表表示的二叉树T
    char ch;
    cin >> ch;
    if (ch == '#') T = NULL;            //递归结束，建空树
    else {
        T = new BiTNode;
        T->data = ch;                    //生成根结点
        CreateBiTree(T->lchild);    //递归创建左子树
        CreateBiTree(T->rchild);    //递归创建右子树
    }
}

void PreOrderTraverse(BiTree T) {
    //先序遍历二叉树T的递归算法
    if (T) {
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse(BiTree T) {
    //中序遍历二叉树T的递归算法
    if (T) {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}

void PostOrderTraverse(BiTree T) {
    //后序遍历二叉树T的递归算法
    if (T) {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}

int Depth(BiTree T) {
    int m, n;
    if (T) {
        m = Depth(T->lchild);
        n = Depth(T->rchild);
        if (m > n) {
            return (m + 1);
        } else {
            return (n + 1);
        }
    } else {
        return 0;
    }
}

int NodeNumber(BiTree T) {
    if (T) {
        return NodeNumber(T->lchild) + NodeNumber(T->rchild) + 1;
    } else {
        return 0;
    }
}


int LeafNodeNumber(BiTree T) {
    if (T) {
        if (T->lchild == NULL && T->rchild == NULL) {
            return 1;
        } else {
            return LeafNodeNumber(T->lchild) + LeafNodeNumber(T->rchild);
        }
    } else {
        return 0;
    }
}

int DepthIs1(BiTree T) {
    if (T) {
        if ((T->lchild == NULL && T->rchild != NULL) || (T->lchild != NULL && T->rchild == NULL)) {
            return 1 + DepthIs1(T->lchild) + DepthIs1(T->rchild);
        } else {
            return DepthIs1(T->lchild) + DepthIs1(T->rchild);
        }
    } else {
        return 0;
    }
}

int path[100] = {0};
int len = 0;

void Route(BiTree T, int *path, int len) {
    if (T) {
        if (T->lchild == NULL && T->rchild == NULL) {
            cout << T->data << "->";
            for (int i = len - 1; i > 0; i--) {
                cout << (char) path[i] << "->";
            }
            cout << (char) path[0] << endl;

        } else {
            path[len++] = (unsigned char) T->data;
            Route(T->lchild, path, len);
            Route(T->rchild, path, len);
        }

    }
}

void Exchange(BiTree &T) {
    BiTree temp;
    if (T) {
        Exchange(T->lchild);
        Exchange(T->rchild);
        temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
    }
}

void DblOrderTraverse(BiTree T) {
    if (T) {
        if (T->lchild == NULL && T->rchild == NULL) {
            cout << T->data;
        } else {
            cout << T->data;
            DblOrderTraverse(T->lchild);
            cout << T->data;
            DblOrderTraverse(T->rchild);
        }
    }
}


int main() {
    BiTree tree;
    cout << "请输入建立二叉链表的序列：";
    CreateBiTree(tree);
    cout << "先序遍历的结果为：";
    PreOrderTraverse(tree);
    cout << endl;
    cout << "中序遍历的结果为：";
    InOrderTraverse(tree);
    cout << endl;
    cout << "后序遍历的结果为：";
    PostOrderTraverse(tree);
    cout << endl;
    cout << "树的深度为：" << Depth(tree) << endl;
    cout << "结点个数为：" << NodeNumber(tree) << endl;
    cout << "叶结点个数为：" << LeafNodeNumber(tree) << endl;
    cout << "度为1结点个数为：" << DepthIs1(tree) << endl;
    cout << "从每个叶子结点到根结点的路径为：" << endl;
    Route(tree, path, len);
    Exchange(tree);
    cout << "交换左右子树后，从每个叶子结点到根结点的路径为：" << endl;
    Route(tree, path, len);
    cout << "交换左右子树后，双序遍历的结果为：";
    DblOrderTraverse(tree);
    cout << endl;
}
