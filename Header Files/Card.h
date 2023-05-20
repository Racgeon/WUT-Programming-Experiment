#pragma once
#include <time.h>
#include "global.h"
#include "HistoryMapList.h"

struct Card{
    char id[19];//卡号
    char password[9];//密码
    double balance;//余额
    int state;//状态
    HistoryMapList info;//历史记录
    time_t start;//上机的时间
    time_t end;//下机的时间
};

Card * createEmptyCard();

Card * createNewCard(char *id, char *password);

int verifyPassword(Card* a, Card* b);

int idEquals(Card*a , Card*b);

Card * createCard(char *id, char *password, double balance);

long calculateOnlineDuration(Card c);

Card * createCardWithHistoryAndState(char *id, char *password, double balance, HistoryMapList info,int state);