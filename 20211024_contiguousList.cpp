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

//����һ��ѧ������
struct Node *createlist() {
    auto *list = (struct Node *) malloc(sizeof(struct Node));//�� list ����һ���ڴ�ռ�
    list->next = NULL;
    return list;
}

//����һ��ѧ���Ľ��
struct Node *createnode(char *newname, int newnum, int newscore) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node)); //��������һ���ڴ�ռ�
    strcpy(node->name, newname); //����Ϣ�ŵ������
    node->score = newscore;
    node->num = newnum;
    node->next = NULL;
    return node;
}

//��β������һ��ѧ������Ϣ
void insertback(struct Node *list, char *newname, int newnum, int newscore) {
    struct Node *newnode = createnode(newname, newnum, newscore);
//�ҵ�β���
    struct Node *temp = list;//�ƶ��Ľ�������ҵ�β���
    while (temp->next != NULL) //һֱ�ƶ������һ�����
    {
        temp = temp->next;
    }
    newnode->next = NULL;
    temp->next = newnode;
}

//ɾ��ѧ����Ϣ
//ɾ����Ϣ��ʱ��������Ҫ���������ƶ���㣬�����ҵ���Ҫɾ���Ľ�����ǰ��һ�����
void deleteinfo(struct Node *list, int num) {
    struct Node *temp = list; //�����ҵ�Ҫɾ����ǰ��һ�����
    struct Node *p = list->next;//ָ����Ҫɾ���Ľ��
    while (p->num != num) {
        temp = temp->next;
        p = p->next;
    }
    temp->next = p->next;
    free(p);
}

//����ѧ������Ϣ
//��ɾ��ѧ�����
void searchinfo(struct Node *list, char *name) {
    struct Node *temp = list->next;
    while (strcmp(temp->name, name) != 0) {
        if (temp->next == NULL) {
            printf("û�д�ѧ������Ϣ\n");
            return;
        }
        temp = temp->next;
    }
    printf("������%s\n ��ţ�%d\n �÷� ��%d\n\n", temp->name, temp->num, temp->score);
}

void print(struct Node *list)//��ӡ���е���Ϣ
{
    struct Node *temp = list->next;
    if (temp == NULL) {
        printf("û��ѧ����Ϣ\n");
    }
    while (temp) {
        printf("������%s\n ��ţ�%d\n �÷� ��%d\n\n", temp->name, temp->num,
               temp->score);
        temp = temp->next;
    }
}

//struct Node* student = createlist();
void menu()//�˵�����
{
    printf("****************************************\n");
    printf("* 1������ѧ����Ϣ *\n");
    printf("* 2������ѧ����Ϣ *\n");
    printf("* 3����ӡ������Ϣ *\n");
    printf("* 4��ɾ��ѧ����Ϣ *\n");
    printf("* 5���˳�����ϵͳ *\n");
    printf("****************************************\n");
}

int choice()//ѡ����Ҫ�Ĳ���
{
    int choice;
    printf("��ѡ����Ҫִ�еĲ���\n");
    scanf("%d", &choice);
    while (choice < 1 || choice > 5) {
        printf("����������������������\n");
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
            printf("������Ϣ��������ţ��ܷ�\n");
            scanf("%s", name);
            scanf("%d", &num);
            scanf("%d", &score);
            insertback(student, name, num, score);
        }
            break;
        case 2: {
            char searchname[10] = "0";
            printf("��������Ҫ���ҵ�ѧ��������\n");
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
            printf("��������Ҫɾ����ѧ���ı��\n");
            scanf("%d", &deletenum);
            deleteinfo(student, deletenum);
        }
            break;
        case 5: {
            exit(0);
        }
            break;
        default:
            printf("�������\n");
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
