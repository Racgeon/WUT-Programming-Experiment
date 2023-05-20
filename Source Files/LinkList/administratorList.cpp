/*此文件用来定义管理员列表的数据结构*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "../../Header Files/Administrator.h"

struct AdministratorNode {
    Administrator data;
    AdministratorNode *next;
};

typedef struct AdministratorNode LNode;
typedef AdministratorNode *AdministratorList;

AdministratorNode *createAdminNode(Administrator data) {
    AdministratorNode *p = (AdministratorNode *) malloc(sizeof(AdministratorNode));
    if (p == NULL)return NULL;
    p->data = data;
    p->next = NULL;
    return p;
}

AdministratorNode *createAdminList() {
    AdministratorNode *p = (AdministratorNode *) malloc(sizeof(AdministratorNode));
    if (p == NULL)return NULL;
    p->data = *createEmptyAdministrator();
    p->next = NULL;
    return p;
}

status insertAdmin(AdministratorList L, int pos, Administrator data) {
    int i = 0;
    AdministratorList temp = L;
    while (temp != NULL && i < pos - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        return UNSUPPORTED_OPERATION_EXCEPTION;
    }
    AdministratorNode *node = (AdministratorNode *) malloc(sizeof(AdministratorNode));
    if (node == NULL)return NULL_POINTER_EXCEPTION;
    node->data = data;
    node->next = NULL;
    node->next = temp->next;
    temp->next = node;
    return OK;
}

int getAdminLength(AdministratorList L) {
    AdministratorNode *temp = L;
    int len = 0;
    while (temp->next != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}

status pushbackAdmin(AdministratorList L, Administrator data) {
    int except = insertAdmin(L, getAdminLength(L) + 1, data);
    if (except == NULL_POINTER_EXCEPTION || except == UNSUPPORTED_OPERATION_EXCEPTION) {
        return except;
    }
    return OK;
}

AdministratorNode *findAdmin(AdministratorList L, char *id, char *password) {
    AdministratorNode *node = createAdminNode(*createNewAdministrator(id, password));
    AdministratorNode *temp = L;
    while (temp != NULL && !verifyPassword(&temp->data, &node->data)) {
        temp = temp->next;
    }
    if (temp == NULL)return NULL;
    return temp;
}


AdministratorNode *unsafeFindAdmin(AdministratorList L, char *id){
    AdministratorNode *node = createAdminNode(*createNewAdministrator(id, NULL));
    AdministratorNode *temp = L;
    while (temp != NULL &&!idEquals(&temp->data, &node->data)) {
        temp = temp->next;
    }
    free(node);
    if (temp == NULL)return NULL;
    return temp;
}

AdministratorNode *findPrior(AdministratorList L, char *id){
    AdministratorNode *temp = L;
    AdministratorNode *node = createAdminNode(*createNewAdministrator(id, NULL));
    AdministratorNode *prior=NULL;
    while (temp != NULL && !idEquals(&temp->data, &node->data)) {
        prior=temp;
        temp = temp->next;
    }
    if (temp == NULL)return NULL;
    return prior;
}


status removeAdminPhysically(AdministratorList L, char *id) {
    AdministratorNode *prior=findPrior(L, id);
    if(prior==NULL)return NODE_NOT_FOUND_EXCEPTION;
    AdministratorNode *temp=prior->next;
    prior->next=prior->next->next;
    free(temp);
    return OK;
}
