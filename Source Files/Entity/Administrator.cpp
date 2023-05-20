/*���ļ������������Ա�����ݽṹ*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/global.h"

struct Administrator{
    char id[19];
    char password[9];
    int authority;
};

//�����չ���Ա��������Ȩ��Ϊ�ޣ���Ϊͷ���
Administrator * createEmptyAdministrator(){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    c->authority=NO_AUTHORITY;
    return c;
}

//���˺����봴������Ա��������Ȩ��Ϊ��
Administrator * createNewAdministrator(char *id, char *password){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    if(password!=NULL)strcpy(c->password,password);
    c->authority=NO_AUTHORITY;
    return c;
}


//���˺������Ȩ�޴�������Ա��������Ȩ��Ϊ��
Administrator * createAdministratorWithAuth(char *id, char *password,int auth){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    strcpy(c->password,password);
    c->authority=auth;
    return c;
}


//�ж���������Ա���˺������Ƿ���ͬ
int verifyPassword(Administrator* a, Administrator* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->password,b->password)==0&& strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}


//�ж���������Ա�Ŀ����Ƿ���ͬ
int idEquals(Administrator *a, Administrator* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}
