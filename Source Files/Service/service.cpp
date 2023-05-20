/*此文件用来写菜单功能的实现*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../../Header Files/CardList.h"
#include "../../Header Files/IO.h"
#include "../../Header Files/Time.h"
#include "../../Header Files/global.h"

extern CardList L;
extern CardList allAliveUsers;

void addCard() {
    printf("----------添加卡----------\n");
    char id[19], password[9];
    again:
    printf("请输入卡号（长度为1-18）：\n");
    scanf("%s", id);
    CardNode *node= unsafeFind(L,id);
    if(node!=NULL&&node->data.state==1){//列表中有这个结点，而且这个结点没有被注销
        printf("此卡号已经被注册，请换一个卡号重试\n");
        goto again;
    }

    printf("请输入密码：（长度为0-8）：\n");
    scanf("%s", password);

    if(node!=NULL&&node->data.state==0){//列表中有这个结点，但是结点已经被注销
        node->data.state=1;
        strcpy(node->data.password,password);
        node->data.info = createHisList();
        storeCard(node,CARD_DATA_FILENAME);
        printf("添加成功\n");
        return;
    }

    //列表中没有这个结点
    if (pushback(L, *createNewCard(id, password)) == OK && storeCard(L, CARD_DATA_FILENAME) == OK) {
        printf("添加成功\n");
    } else {
        printf("添加失败\n");
    }
}


void findCard() {
    printf("----------查询卡----------\n");
    char id[19];
    printf("请输入要查询的卡号：\n");
    scanf("%s", id);
    CardNode *temp= unsafeFind(L, id);

    if (temp != NULL&&temp->data.state==1) {//找到结点并且状态是未注销

        printf("查询到卡信息：\n");

        printf(" 卡号  状态 余额 累计使用 使用次数 上次使用时间\n");
        HistoryMapList info=temp->data.info;
        char *ID=temp->data.id;
        int state=temp->data.state;
        double balance=temp->data.balance;
        double total=calculateTotalCost(info);
        int times=getHisLength(info);
        const char *lastUseTime=getLastUseTime(info);
        printf("%s %d %.1lf %.1lf   %d%s\n",ID,state,balance,total,times,lastUseTime);
    } else {
        printf("未查询到卡信息\n");
    }
}


void login() {
    printf("----------上机----------\n");
    char id[19], password[9];
    printf("请输入卡号：\n");
    scanf("%s", id);
    printf("请输入密码：\n");
    scanf("%s", password);
    CardNode *node = find(L, id, password);
    if (node != NULL && node->data.state==1 &&unsafeFind(allAliveUsers,id)==NULL&& pushback(allAliveUsers, node->data) == OK) {
        printf("成功上机\n");

        node->data.start = time(NULL);//开始消费的时间
        //修改的是用户列表中的信息，不是在线用户列表中的
    } else {
        printf("上机失败\n");
    }
}

void deposit();

void logout() {
    printf("----------下机----------\n");
    printf("请输入要下机的卡号：\n");
    char id[19];
    scanf("%s", id);

    CardNode *LNode = unsafeFind(L, id);//用户列表中查找到的结点
    CardNode *AAUNode = unsafeFind(allAliveUsers, id);//在线用户列表中查找到的结点

    if (LNode == NULL || LNode->data.state==0) {
        printf("卡号未注册，请重新输入卡号\n");
        return;
    } else if (AAUNode == NULL) {
        printf("此卡未上机，请先上机\n");
        return;
    }

    removePhysically(allAliveUsers, id);//首先把这个卡从在线用户列表中删除

    Card c=LNode->data;//获取用户列表中的卡对象

    c.end= time(NULL);//停止消费的时间

    long duration=calculateOnlineDuration(c);//计算用户上机的毫秒值

    HistoryMap info;//创建历史记录

    strcpy(info.date, nowDate);//填入上机的开始日期

    double cost=calculateCost(duration);//算出这次的花费

    info.cost=cost;//更新这次的花费

    pushbackHis(c.info, info);//将这个历史记录放入这个卡的历史记录列表中

    //扣款操作
    if (c.balance >= cost) {
        c.balance -= cost;
        printf("扣款成功，余额为%lf元\n", c.balance);
        storeCard(L, CARD_DATA_FILENAME);
    } else {
        //余额不足情况下进行充值

        printf("余额不足，请充值\n");
        //进入充值界面
        printf("----------充值卡----------\n");
        redeposit:
        double money;
        printf("请输入要充值的金额：\n");
        scanf("%lf", &money);
        c.balance += money;
        printf("充值成功，扣款前余额为%lf元\n", c.balance);
        if(c.balance>=cost) {
            c.balance-=cost;
            printf("充值成功，扣款后余额为%lf元\n", c.balance);
        } else{

            //充值后余额仍不足的就返回继续充值

            printf("余额仍不足，请再充值一定的金额\n");
            goto redeposit;
        }
        storeCard(L, CARD_DATA_FILENAME);
    }

    storeCard(L, CARD_DATA_FILENAME);//更新文件信息

    printf("下机成功，此次的消费为：%.2lf元\n", cost);
}


void deposit() {
    printf("----------充值卡----------\n");
    while (1) {
        printf("请输入要充值的卡号：\n");
        char id[19];
        scanf("%s", id);
        CardNode *node = unsafeFind(L, id);
        if (node == NULL) {
            printf("找不到用户，请重新输入卡号\n");
        } else {
            double money;
            printf("请输入要充值的金额：\n");
            scanf("%lf", &money);
            node->data.balance += money;
            printf("充值成功，余额为%lf元\n", node->data.balance);
            storeCard(L, CARD_DATA_FILENAME);
            break;
        }
    }
}

void refund() {
    printf("----------退费卡----------\n");
    while (1) {
        printf("请输入要退费的卡号：\n");
        char id[19];
        scanf("%s", id);
        CardNode *node = unsafeFind(L, id);
        if (node == NULL) {
            printf("找不到用户，请重新输入卡号\n");
        } else {
            double money;
            printf("请输入要退费的金额：\n");
            scanf("%lf", &money);
            if (node->data.balance >= money) {
                node->data.balance -= money;
                printf("充值成功，余额为%lf元\n", node->data.balance);
                storeCard(L, "../Data/cardData");
            } else {
                printf("余额不足，退费失败\n");
            }
            break;
        }
    }
}

void count() {
    printf("----------统计----------\n");
    char from[11], to[11];
    printf("输入时间段：\n从：\n");
    scanf("%s", from);
    printf("到：\n");
    scanf("%s", to);

    printf("查询结果如下：\n");
    traverse(L,from,to);
}

void cancel() {
    printf("----------注销卡----------\n");
    char id[19];
    printf("请输入要注销的卡号：\n");
    scanf("%s", id);
    if (removeLogically(L, id) == OK) {
        storeCard(L, CARD_DATA_FILENAME);
        printf("已注销\n");
    } else {
        printf("注销失败\n");
    }
}

void Exit() {
    printf("成功退出\n");
    exit(0);
}

