#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../Header Files/CardList.h"
#include "../../Header Files/Administrator.h"
#include "../../Header Files/administratorList.h"
#include "../../Header Files/global.h"
void writeCardToFile(CardList L, FILE *fp);
CardList readCardFromFile(CardList L, FILE *fp);
void writeAdminToFile(AdministratorList L, FILE *fp);
AdministratorList readAdminFromFile(AdministratorList L, FILE *fp);


//把卡的信息从文件中加载到内存
CardList loadCard(CardList L, const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "r")) != NULL) {
        CardList temp = readCardFromFile(L, fp);
        fclose(fp);
        return temp;
    } else {
        printf("信息文件读取失败\n");
        fclose(fp);
        return NULL;
    }
}

//将卡信息从内存保存到文件
status storeCard(CardList L, const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "w")) != NULL) {
        writeCardToFile(L, fp);
        fclose(fp);
    } else {
        printf("信息文件保存失败\n");
        fclose(fp);
        return IO_EXCEPTION;
    }
    return OK;
}


//把管理员的信息从文件中加载到内存
AdministratorList loadAdmin(AdministratorList L, const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "r")) != NULL) {
        AdministratorList temp = readAdminFromFile(L, fp);
        fclose(fp);
        return temp;
    } else {
        printf("信息文件读取失败");
        fclose(fp);
        return NULL;
    }
}

//将管理员信息从内存保存到文件
status storeAdmin(AdministratorList L, const char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "w")) != NULL) {
        writeAdminToFile(L, fp);
        fclose(fp);
    } else {
        printf("信息文件保存失败");
        fclose(fp);
        return IO_EXCEPTION;
    }
    return OK;
}








//将卡对象从文件中读取出来，返回一个卡列表对象
void writeCardToFile(CardList L, FILE *fp) {
    CardNode *temp = L->next;
    while (temp != NULL) {
        Card c = temp->data;
        fputs(c.id, fp);
        fputc(' ', fp);
        fputs(c.password, fp);
        fputc(' ', fp);
        fprintf(fp, "%lf ", c.balance);
        fprintf(fp,"%d ",c.state);
        //historyMap的序列化
        HistoryMapList info=c.info;
        HistoryMapNode* node=info->next;
        while (node!=NULL){
            fprintf(fp,"%s ",node->data.date);
            fprintf(fp,"%lf",node->data.cost);
            HistoryMapNode* t=node->next;
            if(t != NULL){
                fputc(' ',fp);
            } else{
                fputc('\n',fp);
            }
            node=t;
        }
        temp = temp->next;
    }
}

//将卡对象从文件中读取出来，返回一个卡列表对象
CardList readCardFromFile(CardList L, FILE *fp) {
    CardNode *node = L;
    char ch;
    char buf[19];
    int count = 0;
    char id[19], password[9],date[11];
    double balance,cost;
    int state;
    int sign = 0,flag=0,odd=1;
    HistoryMapList info=createHisList();
    while ((ch = fgetc(fp)) != EOF) {
        if (ch != ' ' && ch != '\n') {
            buf[count++] = ch;
            continue;
        }
        if (ch == '\n') {
            flag=1;//如果遇到换行符那么就进入最终状态
        }
        buf[count] = '\0';
        count = 0;
        sign++;
        if (sign == 1) {
            strcpy(id, buf);
        } else if (sign == 2) {
            strcpy(password, buf);
        }
        else if (sign == 3) {
            balance = atof(buf);
        }
        else if(sign==4){
            state= atoi(buf);
        }
        else if(sign>4){
            if(odd){
                strcpy(date,buf);
                odd=0;
            } else{
                cost= atof(buf);
                pushbackHis(info, *createHistoryMap(date,cost));
                odd=1;
            }
        }
        if(flag){//最终状态
            node->next = createNode(*createCardWithHistoryAndState(id, password, balance, info, state));
            info=createHisList();
            node = node->next;
            sign = 0;
            flag=0;//清除状态
        }
        //historyMap的反序列化
    }
    return L;
}



//把管理员对象写入文件中
void writeAdminToFile(AdministratorList L, FILE *fp) {
    AdminNode *temp = L->next;
    while (temp != NULL) {
        Administrator a = temp->data;
        fputs(a.id, fp);
        fputc(' ', fp);
        fputs(a.password, fp);
        fputc(' ', fp);
        fprintf(fp, "%d\n", a.authority);
        temp = temp->next;
    }
}

//将管理员对象从文件中读取出来，返回一个管理员列表对象
AdministratorList readAdminFromFile(AdministratorList L, FILE *fp) {
    AdminNode *node = L;
    char ch;
    char buf[19];
    int count = 0;
    char id[19], password[9];
    int auth;
    int sign = 0,flag=0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch != ' ' && ch != '\n') {
            buf[count++] = ch;
            continue;
        }
        if (ch == '\n') {
            flag=1;//如果遇到换行符那么就进入最终状态
        }
        buf[count] = '\0';
        count = 0;
        sign++;
        if (sign == 1) {
            strcpy(id, buf);
        } else if (sign == 2) {
            strcpy(password, buf);
        }
        else if(sign==3){
            auth= atoi(buf);
        }
        if(flag){//最终状态
            node->next = createAdminNode(*createAdministratorWithAuth(id,password,auth));
            node = node->next;
            sign = 0;
            flag=0;//清除状态
        }
        //historyMap的反序列化
    }
    return L;
}