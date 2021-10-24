//
// Created by Tou on 2021/10/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct Node {
    char name[10];
    int num;
    int score;
    struct Node *next;
};

//创建一个学生链表
struct Node *createlist() {
    auto *list = (struct Node *) malloc(sizeof(struct Node));//给 list 分配一个内存空间
    list->next = NULL;
    return list;
}

//创建一个学生的结点
struct Node *createnode(char *newname, int newnum, int newscore) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node)); //给结点分配一个内存空间
    strcpy(node->name, newname); //把信息放到结点中
    node->score = newscore;
    node->num = newnum;
    node->next = NULL;
    return node;
}

//在尾部插入一个学生的信息
void insertback(struct Node *list, char *newname, int newnum, int newscore) {
    struct Node *newnode = createnode(newname, newnum, newscore);
//找到尾结点
    struct Node *temp = list;//移动的结点用来找到尾结点
    while (temp->next != NULL) //一直移动到最后一个结点
    {
        temp = temp->next;
    }
    newnode->next = NULL;
    temp->next = newnode;
}

//删除学生信息
//删除信息的时候我们需要定义两个移动结点，用来找到需要删除的结点和它前面一个结点
void deleteinfo(struct Node *list, int num) {
    struct Node *temp = list; //用来找到要删除的前面一个结点
    struct Node *p = list->next;//指向需要删除的结点
    while (p->num != num) {
        temp = temp->next;
        p = p->next;
    }
    temp->next = p->next;
    free(p);
}

//查找学生的信息
//和删除学生差不多
void searchinfo(struct Node *list, char *name) {
    struct Node *temp = list->next;
    while (strcmp(temp->name, name) != 0) {
        if (temp->next == NULL) {
            printf("没有此学生的信息\n");
            return;
        }
        temp = temp->next;
    }
    printf("姓名：%s\n 编号：%d\n 得分 ：%d\n\n", temp->name, temp->num, temp->score);
}

void print(struct Node *list)//打印所有的信息
{
    struct Node *temp = list->next;
    if (temp == NULL) {
        printf("没有学生信息\n");
    }
    while (temp) {
        printf("姓名：%s\n 编号：%d\n 得分 ：%d\n\n", temp->name, temp->num,
               temp->score);
        temp = temp->next;
    }
}

//struct Node* student = createlist();
void menu()//菜单界面
{
    printf("****************************************\n");
    printf("* 1、插入学生信息 *\n");
    printf("* 2、查找学生信息 *\n");
    printf("* 3、打印所有信息 *\n");
    printf("* 4、删除学生信息 *\n");
    printf("* 5、退出管理系统 *\n");
    printf("****************************************\n");
}

int choice()//选择需要的操作
{
    int choice;
    printf("请选择您要执行的操作\n");
    scanf("%d", &choice);
    while (choice < 1 || choice > 5) {
        printf("您的输入有误，请重新输入\n");
        scanf("%d", &choice);
    }
    return choice;
}

void work(struct Node *student) {
    menu();
    int a = choice();
    switch (a) {
        case 1: {
            char name[10] = "0";
            int num = 0;
            int score = 0;
            printf("输入信息姓名，编号，总分\n");
            scanf("%s", name);
            scanf("%d", &num);
            scanf("%d", &score);
            insertback(student, name, num, score);
        }
            break;
        case 2: {
            char searchname[10] = "0";
            printf("请输入你要查找的学生的名字\n");
            scanf("%s", searchname);
            searchinfo(student, searchname);
        }
            break;
        case 3: {
            print(student);
        }
            break;
        case 4: {
            int deletenum = 0;
            printf("请输入你要删除的学生的编号\n");
            scanf("%d", &deletenum);
            deleteinfo(student, deletenum);
        }
            break;
        case 5: {
            exit(0);
        }
            break;
        default:
            printf("输入错误\n");
            break;
    }
}

int main() {
    struct Node *student = createlist();
    while (1) {
        work(student);
    }
    system("pause");
    return 0;
}
