/*此文件用来定义历史记录的数据结构*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/global.h"

struct HistoryMap{
    char date[11];//日期
    double cost;//消费记录
};


//创建空的历史记录，作为头结点
HistoryMap* emptyHistoryMap(){
    HistoryMap* historyMap=(HistoryMap*) malloc(sizeof(historyMap));
    strcpy(historyMap->date,"");
    historyMap->cost=0;
    return historyMap;
}

//用日期和花费创建历史记录
HistoryMap* createHistoryMap(char *date,double cost){
    HistoryMap* historyMap=(HistoryMap*) malloc(sizeof(historyMap));
    strcpy(historyMap->date,date);
    historyMap->cost=cost;
    return historyMap;
}

//复制历史记录
void historyMapCopy(HistoryMap dest,HistoryMap src){
    strcpy(dest.date, src.date);
    dest.cost=src.cost;
}


