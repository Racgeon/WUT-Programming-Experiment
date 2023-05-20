/*此文件用来定义卡的数据结构*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/HistoryMap.h"
#include "../../Header Files/HistoryMapList.h"
#include "../../Header Files/global.h"

struct Card{
    char id[19];//卡号
    char password[9];//密码
    double balance;//余额
    int state;//状态，1代表未注销，0代表已注销
    HistoryMapList info;//历史记录
    time_t start;//上机的时间
    time_t end;//下机的时间
};


//创建空卡，账号密码为乱码，历史列表为空，注销状态，作为头结点
Card * createEmptyCard(){
    Card* c=(Card*) malloc(sizeof (Card));
    if(c==NULL)return NULL;
    c->balance=0;
    c->info=createHisList();
    c->state=0;
    return c;
}

//创建卡，设置账号密码，历史列表为空，未注销状态
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

//创建卡，设置账号密码和余额，历史列表为空，未注销状态
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

//创建卡，设置账号密码、余额、历史列表、状态
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

//判断两个卡的账号密码是否都相等
int verifyPassword(Card* a, Card* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->password,b->password)==0&& strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}

//判断两个卡的卡号是否相等
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
