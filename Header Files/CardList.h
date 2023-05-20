#pragma once
#include "Card.h"
#include "global.h"

struct CardNode{
    Card data;
    CardNode *next;
};
typedef struct CardNode LNode;
typedef CardNode* CardList;
status insert(CardList L, int pos, Card data);
int getLength(CardList L);
status pushback(CardList L, Card data);
CardNode* createNode(Card data);
CardNode* createList();
CardNode *find(CardList L, char *id, char *password);
status removePhysically(CardList L, char *id);
status removeLogically(CardList L, char *id);
CardNode *unsafeFind(CardList L, char *id);
Card * createCardWithHistoryAndState(char *id, char *password, double balance, HistoryMapList info);
status traverse(CardList L,char *from,char *to);
