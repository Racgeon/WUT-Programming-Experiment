#pragma once
#include <time.h>
#include "global.h"
#include "HistoryMapList.h"

struct Card{
    char id[19];//����
    char password[9];//����
    double balance;//���
    int state;//״̬
    HistoryMapList info;//��ʷ��¼
    time_t start;//�ϻ���ʱ��
    time_t end;//�»���ʱ��
};

Card * createEmptyCard();

Card * createNewCard(char *id, char *password);

int verifyPassword(Card* a, Card* b);

int idEquals(Card*a , Card*b);

Card * createCard(char *id, char *password, double balance);

long calculateOnlineDuration(Card c);

Card * createCardWithHistoryAndState(char *id, char *password, double balance, HistoryMapList info,int state);