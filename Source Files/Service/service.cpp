/*���ļ�����д�˵����ܵ�ʵ��*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../Header Files/CardList.h"
#include "../../Header Files/IO.h"
#include "../../Header Files/Time.h"
#include "../../Header Files/global.h"

extern CardList L;
extern CardList allAliveUsers;

void addCard() {
    printf("----------��ӿ�----------\n");
    char id[19], password[9];
    again:
    printf("�����뿨�ţ�����Ϊ1-18����\n");
    scanf("%s", id);
    CardNode *node= unsafeFind(L,id);
    if(node!=NULL&&node->data.state==1){//�б����������㣬����������û�б�ע��
        printf("�˿����Ѿ���ע�ᣬ�뻻һ����������\n");
        goto again;
    }

    printf("���������룺������Ϊ0-8����\n");
    scanf("%s", password);

    if(node!=NULL&&node->data.state==0){//�б����������㣬���ǽ���Ѿ���ע��
        node->data.state=1;
        strcpy(node->data.password,password);
        node->data.info = createHisList();
        storeCard(node,CARD_DATA_FILENAME);
        printf("��ӳɹ�\n");
        return;
    }

    //�б���û��������
    if (pushback(L, *createNewCard(id, password)) == OK && storeCard(L, CARD_DATA_FILENAME) == OK) {
        printf("��ӳɹ�\n");
    } else {
        printf("���ʧ��\n");
    }
}


void findCard() {
    printf("----------��ѯ��----------\n");
    char id[19];
    printf("������Ҫ��ѯ�Ŀ��ţ�\n");
    scanf("%s", id);
    CardNode *temp= unsafeFind(L, id);

    if (temp != NULL&&temp->data.state==1) {//�ҵ���㲢��״̬��δע��

        printf("��ѯ������Ϣ��\n");

        printf(" ����  ״̬ ��� �ۼ�ʹ�� ʹ�ô��� �ϴ�ʹ��ʱ��\n");
        HistoryMapList info=temp->data.info;
        char *ID=temp->data.id;
        int state=temp->data.state;
        double balance=temp->data.balance;
        double total=calculateTotalCost(info);
        int times=getHisLength(info);
        const char *lastUseTime=getLastUseTime(info);
        printf("%s %d %.1lf %.1lf   %d%s\n",ID,state,balance,total,times,lastUseTime);
    } else {
        printf("δ��ѯ������Ϣ\n");
    }
}


void login() {
    printf("----------�ϻ�----------\n");
    char id[19], password[9];
    printf("�����뿨�ţ�\n");
    scanf("%s", id);
    printf("���������룺\n");
    scanf("%s", password);
    CardNode *node = find(L, id, password);
    if (node != NULL && node->data.state==1 &&unsafeFind(allAliveUsers,id)==NULL&& pushback(allAliveUsers, node->data) == OK) {
        printf("�ɹ��ϻ�\n");

        node->data.start = time(NULL);//��ʼ���ѵ�ʱ��
        //�޸ĵ����û��б��е���Ϣ�����������û��б��е�
    } else {
        printf("�ϻ�ʧ��\n");
    }
}

void deposit();

void logout() {
    printf("----------�»�----------\n");
    printf("������Ҫ�»��Ŀ��ţ�\n");
    char id[19];
    scanf("%s", id);

    CardNode *LNode = unsafeFind(L, id);//�û��б��в��ҵ��Ľ��
    CardNode *AAUNode = unsafeFind(allAliveUsers, id);//�����û��б��в��ҵ��Ľ��

    if (LNode == NULL || LNode->data.state==0) {
        printf("����δע�ᣬ���������뿨��\n");
        return;
    } else if (AAUNode == NULL) {
        printf("�˿�δ�ϻ��������ϻ�\n");
        return;
    }

    removePhysically(allAliveUsers, id);//���Ȱ�������������û��б���ɾ��

    Card c=LNode->data;//��ȡ�û��б��еĿ�����

    c.end= time(NULL);//ֹͣ���ѵ�ʱ��

    long duration=calculateOnlineDuration(c);//�����û��ϻ��ĺ���ֵ

    HistoryMap info;//������ʷ��¼

    strcpy(info.date, nowDate);//�����ϻ��Ŀ�ʼ����

    double cost=calculateCost(duration);//�����εĻ���

    info.cost=cost;//������εĻ���

    pushbackHis(c.info, info);//�������ʷ��¼�������������ʷ��¼�б���

    //�ۿ����
    if (c.balance >= cost) {
        c.balance -= cost;
        printf("�ۿ�ɹ������Ϊ%lfԪ\n", c.balance);
        storeCard(L, CARD_DATA_FILENAME);
    } else {
        //��������½��г�ֵ

        printf("���㣬���ֵ\n");
        //�����ֵ����
        printf("----------��ֵ��----------\n");
        redeposit:
        double money;
        printf("������Ҫ��ֵ�Ľ�\n");
        scanf("%lf", &money);
        c.balance += money;
        printf("��ֵ�ɹ����ۿ�ǰ���Ϊ%lfԪ\n", c.balance);
        if(c.balance>=cost) {
            c.balance-=cost;
            printf("��ֵ�ɹ����ۿ�����Ϊ%lfԪ\n", c.balance);
        } else{

            //��ֵ������Բ���ľͷ��ؼ�����ֵ

            printf("����Բ��㣬���ٳ�ֵһ���Ľ��\n");
            goto redeposit;
        }
        storeCard(L, CARD_DATA_FILENAME);
    }

    storeCard(L, CARD_DATA_FILENAME);//�����ļ���Ϣ

    printf("�»��ɹ����˴ε�����Ϊ��%.2lfԪ\n", cost);
}


void deposit() {
    printf("----------��ֵ��----------\n");
    while (1) {
        printf("������Ҫ��ֵ�Ŀ��ţ�\n");
        char id[19];
        scanf("%s", id);
        CardNode *node = unsafeFind(L, id);
        if (node == NULL) {
            printf("�Ҳ����û������������뿨��\n");
        } else {
            double money;
            printf("������Ҫ��ֵ�Ľ�\n");
            scanf("%lf", &money);
            node->data.balance += money;
            printf("��ֵ�ɹ������Ϊ%lfԪ\n", node->data.balance);
            storeCard(L, CARD_DATA_FILENAME);
            break;
        }
    }
}

void refund() {
    printf("----------�˷ѿ�----------\n");
    while (1) {
        printf("������Ҫ�˷ѵĿ��ţ�\n");
        char id[19];
        scanf("%s", id);
        CardNode *node = unsafeFind(L, id);
        if (node == NULL) {
            printf("�Ҳ����û������������뿨��\n");
        } else {
            double money;
            printf("������Ҫ�˷ѵĽ�\n");
            scanf("%lf", &money);
            if (node->data.balance >= money) {
                node->data.balance -= money;
                printf("��ֵ�ɹ������Ϊ%lfԪ\n", node->data.balance);
                storeCard(L, "../Data/cardData");
            } else {
                printf("���㣬�˷�ʧ��\n");
            }
            break;
        }
    }
}

void count() {
    printf("----------ͳ��----------\n");
    char from[11], to[11];
    printf("����ʱ��Σ�\n�ӣ�\n");
    scanf("%s", from);
    printf("����\n");
    scanf("%s", to);

    printf("��ѯ������£�\n");
    traverse(L,from,to);
}

void cancel() {
    printf("----------ע����----------\n");
    char id[19];
    printf("������Ҫע���Ŀ��ţ�\n");
    scanf("%s", id);
    if (removeLogically(L, id) == OK) {
        storeCard(L, CARD_DATA_FILENAME);
        printf("��ע��\n");
    } else {
        printf("ע��ʧ��\n");
    }
}

void Exit() {
    printf("�ɹ��˳�\n");
    exit(0);
}

