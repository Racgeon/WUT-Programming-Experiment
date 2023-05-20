/*���ļ��������忨�����ݽṹ*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/HistoryMap.h"
#include "../../Header Files/HistoryMapList.h"
#include "../../Header Files/global.h"

struct Card{
    char id[19];//����
    char password[9];//����
    double balance;//���
    int state;//״̬��1����δע����0������ע��
    HistoryMapList info;//��ʷ��¼
    time_t start;//�ϻ���ʱ��
    time_t end;//�»���ʱ��
};


//�����տ����˺�����Ϊ���룬��ʷ�б�Ϊ�գ�ע��״̬����Ϊͷ���
Card * createEmptyCard(){
    Card* c=(Card*) malloc(sizeof (Card));
    if(c==NULL)return NULL;
    c->balance=0;
    c->info=createHisList();
    c->state=0;
    return c;
}

//�������������˺����룬��ʷ�б�Ϊ�գ�δע��״̬
Card * createNewCard(char *id, char *password){
    Card* c=(Card*) malloc(sizeof (Card));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    if(password!=NULL)strcpy(c->password,password);
    c->balance=0;
    c->info=createHisList();
    c->state=1;
    return c;
}

//�������������˺����������ʷ�б�Ϊ�գ�δע��״̬
Card * createCard(char *id, char *password, double balance){
    Card* c=(Card*) malloc(sizeof (Card));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    strcpy(c->password,password);
    c->balance=balance;
    c->info=createHisList();
    c->state=1;
    return c;
}

//�������������˺����롢����ʷ�б�״̬
Card * createCardWithHistoryAndState(char *id, char *password, double balance, HistoryMapList info,int state){
    Card* c=(Card*) malloc(sizeof (Card));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    strcpy(c->password,password);
    c->balance=balance;
    c->info=info;
    c->state=state;
    return c;
}

//�ж����������˺������Ƿ����
int verifyPassword(Card* a, Card* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->password,b->password)==0&& strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}

//�ж��������Ŀ����Ƿ����
int idEquals(Card *a, Card* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}

long calculateOnlineDuration(Card c){
    return c.end-c.start;
}
