/*此文件用来定义管理员的数据结构*/
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

//创建空管理员对象，设置权限为无，作为头结点
Administrator * createEmptyAdministrator(){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    c->authority=NO_AUTHORITY;
    return c;
}

//用账号密码创建管理员对象，设置权限为无
Administrator * createNewAdministrator(char *id, char *password){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    if(password!=NULL)strcpy(c->password,password);
    c->authority=NO_AUTHORITY;
    return c;
}


//用账号密码和权限创建管理员对象，设置权限为无
Administrator * createAdministratorWithAuth(char *id, char *password,int auth){
    Administrator* c=(Administrator*) malloc(sizeof (Administrator));
    if(c==NULL)return NULL;
    strcpy(c->id,id);
    strcpy(c->password,password);
    c->authority=auth;
    return c;
}


//判断两个管理员的账号密码是否相同
int verifyPassword(Administrator* a, Administrator* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->password,b->password)==0&& strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}


//判断两个管理员的卡号是否相同
int idEquals(Administrator *a, Administrator* b){
    if(a==NULL||b==NULL){
        return 0;
    }
    if(strcmp(a->id,b->id)==0){
        return 1;
    }
    return 0;
}
