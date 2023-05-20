#pragma once
#include "Administrator.h"
#include "global.h"


struct AdministratorNode {
    Administrator data;
    AdministratorNode *next;
};
typedef struct AdministratorNode AdminNode;
typedef AdministratorNode *AdministratorList;

AdministratorNode *createAdminNode(Administrator data);

AdministratorNode *createAdminList();

status insertAdmin(AdministratorList L, int pos, Administrator data);

int getAdminLength(AdministratorList L);

status pushbackAdmin(AdministratorList L, Administrator data);

AdministratorNode *findAdmin(AdministratorList L, char *id, char *password);

AdministratorNode *unsafeFindAdmin(AdministratorList L, char *id);

status removeAdminPhysically(AdministratorList L, char *id);