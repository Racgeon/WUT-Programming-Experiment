/*���ļ�����������ʷ��¼�����ݽṹ*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/global.h"

struct HistoryMap{
    char date[11];//����
    double cost;//���Ѽ�¼
};


//�����յ���ʷ��¼����Ϊͷ���
HistoryMap* emptyHistoryMap(){
    HistoryMap* historyMap=(HistoryMap*) malloc(sizeof(historyMap));
    strcpy(historyMap->date,"");
    historyMap->cost=0;
    return historyMap;
}

//�����ںͻ��Ѵ�����ʷ��¼
HistoryMap* createHistoryMap(char *date,double cost){
    HistoryMap* historyMap=(HistoryMap*) malloc(sizeof(historyMap));
    strcpy(historyMap->date,date);
    historyMap->cost=cost;
    return historyMap;
}

//������ʷ��¼
void historyMapCopy(HistoryMap dest,HistoryMap src){
    strcpy(dest.date, src.date);
    dest.cost=src.cost;
}


