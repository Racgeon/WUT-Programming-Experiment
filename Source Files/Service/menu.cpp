/*���ļ���������menu�������в˵�����*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "../../Header Files/service.h"
#include "../../Header Files/CardList.h"
#include "../../Header Files/IO.h"

CardList L=createList();
CardList allAliveUsers=createList();

void menu() {
    L=loadCard(L,CARD_DATA_FILENAME);
    printf("��ӭ����Ʒѹ���ϵͳ\n\n");
    printf("----------�˵�----------\n");
    printf("1.��ӿ�\n");
    printf("2.��ѯ��\n");
    printf("3.�ϻ�\n");
    printf("4.�»�\n");
    printf("5.��ֵ\n");
    printf("6.�˷�\n");
    printf("7.��ѯͳ��\n");
    printf("8.ע����\n");
    printf("0.�˳�\n");

    int input;
    printf("�����룺\n");
    while (1) {
        scanf("%d", &input);
        switch (input) {
            case 1: {
                addCard();
                break;
            }
            case 2: {
                findCard();
                break;
            }
            case 3: {
                login();
                break;
            }
            case 4: {
                logout();
                break;
            }
            case 5: {
                deposit();
                break;
            }
            case 6: {
                refund();
                break;
            }
            case 7: {
                count();
                break;
            }
            case 8: {
                cancel();
                break;
            }
            case 0: {
                Exit();
                break;
            }
            default:;
        }

        printf("\n��ѡ��˵����ţ�0-8����\n");
    }

}