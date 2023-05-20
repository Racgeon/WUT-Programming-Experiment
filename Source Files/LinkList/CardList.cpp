/*���ļ��������忨�б�����ݽṹ*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "../../Header Files/Card.h"
#include "../../Header Files/HistoryMapList.h"
#include "../../Header Files/HistoryMap.h"


//���Ķ���
struct CardNode {
    Card data;
    CardNode *next;
};
typedef struct CardNode LNode;
typedef CardNode *CardList;


//����������
CardNode *createNode(Card data) {
    CardNode *p = (CardNode *) malloc(sizeof(CardNode));
    if (p == NULL)return NULL;
    p->data = data;
    p->next = NULL;
    return p;
}


//�����������
CardNode *createList() {
    CardNode *p = (CardNode *) malloc(sizeof(CardNode));
    if (p == NULL)return NULL;
    p->data = *createEmptyCard();
    p->next = NULL;
    return p;
}


//������ָ��λ�ò�����Ĳ���
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


//��ȡ�б�ĳ��ȣ�����������
int getLength(CardList L) {
    CardNode *temp = L;
    int len = 0;
    while (temp->next != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}


//β�忨Ԫ��
status pushback(CardList L, Card data) {
    int except = insert(L, getLength(L) + 1, data);
    if (except == NULL_POINTER_EXCEPTION || except == UNSUPPORTED_OPERATION_EXCEPTION) {
        return except;
    }
    return OK;
}


//ͨ�����ź�����Ѱ�ҿ�Ԫ�أ�����ҵ����ص�ַ
CardNode *find(CardList L, char *id, char *password) {//�ҵ��˿������Ѿ�ע��
    CardNode *node = createNode(*createNewCard(id, password));
    CardNode *temp = L;
    while (temp != NULL && !verifyPassword(&temp->data, &node->data)) {
        temp = temp->next;
    }
    if (temp == NULL)return NULL;
    return temp;
}


//ͨ��idѰ�ҿ�Ԫ��
CardNode *unsafeFind(CardList L, char *id){//�ҵ��˿������Ѿ�ע��
    CardNode *node = createNode(*createNewCard(id, NULL));
    CardNode *temp = L;
    while (temp != NULL &&!idEquals(&temp->data, &node->data)) {
        temp = temp->next;
    }
    free(node);
    if (temp == NULL)return NULL;
    return temp;
}


//�ҵ�ָ�����
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


//���ڴ���ɾ��ָ�����
status removePhysically(CardList L, char *id) {
    CardNode *prior=findPrior(L, id);
    if(prior==NULL)return NODE_NOT_FOUND_EXCEPTION;
    CardNode *temp=prior->next;
    prior->next=prior->next->next;
    free(temp);
    return OK;
}


//������״̬����Ϊע��
status removeLogically(CardList L, char *id){
    CardNode *node= unsafeFind(L,id);
    if(node==NULL)return NODE_NOT_FOUND_EXCEPTION;
    node->data.state=0;
    return OK;
}


//��������
status traverse(CardList L,char *from,char *to){
    int y1,y2,m1,m2,d1,d2;
    sscanf(from,"%d-%d-%d",&y1,&m1,&d1);
    sscanf(to,"%d-%d-%d",&y2,&m2,&d2);
    CardNode *node=L->next;
    printf("���Ѽ�¼��\n");
    printf("------------------------------\n");
    double totalIncome=0;//��¼��Ӫҵ��
    int months=(y2-y1)*12+m2-m1+1;//��¼ʱ�ε�����
    double* monIncome=(double *) calloc(months,sizeof (double));//����һ��������ÿ���µ�����

    while (node!=NULL){//����ÿһ�����б��еĿ�
        printf("���� %s �����Ѽ�¼��\n",node->data.id);
        HistoryMapList info=node->data.info;
        info=info->next;
        int y3,m3,d3;

        while (info!=NULL){//����ÿ����ʷ��¼�б�
            printf("ʱ�䣺%s ���ѣ�%.1lfԪ\n",info->data.date,info->data.cost);
            totalIncome+=info->data.cost;
            sscanf(info->data.date,"%d-%d-%d",&y3,&m3,&d3);
            //��������ڷ�Χ�ڵ���ʷ��¼
            if(y3<y2&&y3>y1||(y3==y2&&(m3<m2||(m3==m2&&d3<=d2)))||(y3==y1&&(m3>m1||(m3==m1&&d3>=d1)))){
                monIncome[(y3-y1)*12+m3-m1]+=info->data.cost;
            }
            info=info->next;
        }
        node=node->next;
        if(node!=NULL)printf("\n");
    }
    printf("------------------------------\n");
    printf("��Ӫҵ�%.1lfԪ\n", totalIncome);
    printf("------------------------------\n");
    printf("��Ӫҵ�\n");
    int flag=0;
    for(int i=0;i<months;i++){
        if((i+y1)%12==0){
            flag=1;
        } else{
            flag=0;
        }
        printf("%d��%d�� Ӫҵ�%.1lfԪ\n",flag?++y1:y1,m1++,monIncome[i]);
        printf("------------------------------\n");
    }
    return OK;
}