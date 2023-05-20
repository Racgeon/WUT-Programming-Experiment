#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "HistoryMap.h"
#include "global.h"

struct HistoryMapNode{
    HistoryMap data;
    HistoryMapNode *next;
};
typedef struct HistoryMapNode HistoryMapNode;
typedef HistoryMapNode *HistoryMapList;

HistoryMapNode *createHisNode(HistoryMap data);

HistoryMapNode *createHisList();

status insertHis(HistoryMapList L, int pos, HistoryMap data);

int getHisLength(HistoryMapList L);

status pushbackHis(HistoryMapList L, HistoryMap data);

void traverseHis(HistoryMapList L);

double calculateTotalCost(HistoryMapList L);

const char * getLastUseTime(HistoryMapList L);