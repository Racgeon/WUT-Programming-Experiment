#pragma once

struct HistoryMap{
    char date[11];
    double cost;//���Ѽ�¼
};

HistoryMap* emptyHistoryMap();
HistoryMap* createHistoryMap(char *date,double cost);