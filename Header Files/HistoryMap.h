#pragma once

struct HistoryMap{
    char date[11];
    double cost;//Ïû·Ñ¼ÇÂ¼
};

HistoryMap* emptyHistoryMap();
HistoryMap* createHistoryMap(char *date,double cost);