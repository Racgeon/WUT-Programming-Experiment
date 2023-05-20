/*此文件用来定义卡列表的数据结构*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "../../Header Files/Card.h"
#include "../../Header Files/HistoryMapList.h"
#include "../../Header Files/HistoryMap.h"


//卡的定义
struct CardNode {
    Card data;
    CardNode *next;
};
typedef struct CardNode LNode;
typedef CardNode *CardList;


//创建结点操作
CardNode *createNode(Card data) {
    CardNode *p = (CardNode *) malloc(sizeof(CardNode));
    if (p == NULL)return NULL;
    p->data = data;
    p->next = NULL;
    return p;
}


//创建链表操作
CardNode *createList() {
    CardNode *p = (CardNode *) malloc(sizeof(CardNode));
    if (p == NULL)return NULL;
    p->data = *createEmptyCard();
    p->next = NULL;
    return p;
}


//插入在指定位置插入结点的操作
status insert(CardList L, int pos, Card data) {
    int i = 0;
    CardList temp = L;
    while (temp != NULL && i < pos - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        return UNSUPPORTED_OPERATION_EXCEPTION;
    }
    CardNode *node = (CardNode *) malloc(sizeof(CardNode));
    if (node == NULL)return NULL_POINTER_EXCEPTION;
    node->data = data;
    node->next = NULL;
    node->next = temp->next;
    temp->next = node;
    return OK;
}


//获取列表的长度，即卡的数量
int getLength(CardList L) {
    CardNode *temp = L;
    int len = 0;
    while (temp->next != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}


//尾插卡元素
status pushback(CardList L, Card data) {
    int except = insert(L, getLength(L) + 1, data);
    if (except == NULL_POINTER_EXCEPTION || except == UNSUPPORTED_OPERATION_EXCEPTION) {
        return except;
    }
    return OK;
}


//通过卡号和密码寻找卡元素，如果找到返回地址
CardNode *find(CardList L, char *id, char *password) {//找到了可能是已经注销
    CardNode *node = createNode(*createNewCard(id, password));
    CardNode *temp = L;
    while (temp != NULL && !verifyPassword(&temp->data, &node->data)) {
        temp = temp->next;
    }
    if (temp == NULL)return NULL;
    return temp;
}


//通过id寻找卡元素
CardNode *unsafeFind(CardList L, char *id){//找到了可能是已经注销
    CardNode *node = createNode(*createNewCard(id, NULL));
    CardNode *temp = L;
    while (temp != NULL &&!idEquals(&temp->data, &node->data)) {
        temp = temp->next;
    }
    free(node);
    if (temp == NULL)return NULL;
    return temp;
}


//找到指定结点
CardNode *findPrior(CardList L, char *id){
    CardNode *temp = L;
    CardNode *node = createNode(*createNewCard(id, NULL));
    CardNode *prior=NULL;
    while (temp != NULL && !idEquals(&temp->data, &node->data)) {
        prior=temp;
        temp = temp->next;
    }
    if (temp == NULL)return NULL;
    return prior;
}


//在内存中删除指定结点
status removePhysically(CardList L, char *id) {
    CardNode *prior=findPrior(L, id);
    if(prior==NULL)return NODE_NOT_FOUND_EXCEPTION;
    CardNode *temp=prior->next;
    prior->next=prior->next->next;
    free(temp);
    return OK;
}


//将结点的状态设置为注销
status removeLogically(CardList L, char *id){
    CardNode *node= unsafeFind(L,id);
    if(node==NULL)return NODE_NOT_FOUND_EXCEPTION;
    node->data.state=0;
    return OK;
}


//遍历链表
status traverse(CardList L,char *from,char *to){
    int y1,y2,m1,m2,d1,d2;
    sscanf(from,"%d-%d-%d",&y1,&m1,&d1);
    sscanf(to,"%d-%d-%d",&y2,&m2,&d2);
    CardNode *node=L->next;
    printf("消费记录：\n");
    printf("------------------------------\n");
    double totalIncome=0;//记录总营业额
    int months=(y2-y1)*12+m2-m1+1;//记录时段的月数
    double* monIncome=(double *) calloc(months,sizeof (double));//开辟一个数组存放每个月的收入

    while (node!=NULL){//对于每一个在列表中的卡
        printf("卡号 %s 的消费记录：\n",node->data.id);
        HistoryMapList info=node->data.info;
        info=info->next;
        int y3,m3,d3;

        while (info!=NULL){//对于每个历史记录列表
            printf("时间：%s 消费：%.1lf元\n",info->data.date,info->data.cost);
            totalIncome+=info->data.cost;
            sscanf(info->data.date,"%d-%d-%d",&y3,&m3,&d3);
            //检查在日期范围内的历史记录
            if(y3<y2&&y3>y1||(y3==y2&&(m3<m2||(m3==m2&&d3<=d2)))||(y3==y1&&(m3>m1||(m3==m1&&d3>=d1)))){
                monIncome[(y3-y1)*12+m3-m1]+=info->data.cost;
            }
            info=info->next;
        }
        node=node->next;
        if(node!=NULL)printf("\n");
    }
    printf("------------------------------\n");
    printf("总营业额：%.1lf元\n", totalIncome);
    printf("------------------------------\n");
    printf("月营业额：\n");
    int flag=0;
    for(int i=0;i<months;i++){
        if((i+y1)%12==0){
            flag=1;
        } else{
            flag=0;
        }
        printf("%d年%d月 营业额：%.1lf元\n",flag?++y1:y1,m1++,monIncome[i]);
        printf("------------------------------\n");
    }
    return OK;
}