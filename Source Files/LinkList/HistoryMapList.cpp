/*此文件用来定义卡的历史记录列表的数据结构*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "../../Header Files/HistoryMap.h"
#include "../../Header Files/global.h"

struct HistoryMapNode{
    HistoryMap data;
    HistoryMapNode *next;
};

typedef struct HistoryMapNode HistoryMapNode;
typedef HistoryMapNode *HistoryMapList;

HistoryMapNode *createHisNode(HistoryMap data) {
    HistoryMapNode *p = (HistoryMapNode *) malloc(sizeof(HistoryMapNode));
    if (p == NULL)return NULL;
    p->data = data;
    p->next = NULL;
    return p;
}

HistoryMapNode *createHisList() {
    HistoryMapNode *p = (HistoryMapNode *) malloc(sizeof(HistoryMapNode));
    if (p == NULL)return NULL;
    p->data = *emptyHistoryMap();
    p->next = NULL;
    return p;
}

status insertHis(HistoryMapList L, int pos, HistoryMap data) {
    int i = 0;
    HistoryMapList temp = L;
    while (temp != NULL && i < pos - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        return UNSUPPORTED_OPERATION_EXCEPTION;
    }
    HistoryMapNode *node = (HistoryMapNode *) malloc(sizeof(HistoryMapNode));
    if (node == NULL)return NULL_POINTER_EXCEPTION;
    node->data = data;
    node->next = NULL;
    node->next = temp->next;
    temp->next = node;
    return OK;
}

int getHisLength(HistoryMapList L) {
    HistoryMapNode *temp = L;
    int len = 0;
    while (temp->next != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}

status pushbackHis(HistoryMapList L, HistoryMap data) {
    int except = insertHis(L, getHisLength(L) + 1, data);
    if (except == NULL_POINTER_EXCEPTION || except == UNSUPPORTED_OPERATION_EXCEPTION) {
        return except;
    }
    return OK;
}


void traverseHis(HistoryMapList L){
    HistoryMapNode *node=L->next;
    while (node!=NULL){
        printf("时间：%s 消费：%lf\n",node->data.date,node->data.cost);
        node=node->next;
    }
}


double calculateTotalCost(HistoryMapList L){
    HistoryMapNode *node=L->next;
    double result=0;
    while (node!=NULL){
        result+=node->data.cost;
        node=node->next;
    }
    return result;
}

const char * getLastUseTime(HistoryMapList L){
    HistoryMapNode *node=L->next;
    if(node==NULL){
        return "无";
    }
    while (node->next!=NULL){
        node=node->next;
    }
    return node->data.date;
}