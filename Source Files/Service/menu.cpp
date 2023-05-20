/*此文件用来定义menu函数进行菜单操作*/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "../../Header Files/service.h"
#include "../../Header Files/CardList.h"
#include "../../Header Files/IO.h"

CardList L=createList();
CardList allAliveUsers=createList();

void menu() {
    L=loadCard(L,CARD_DATA_FILENAME);
    printf("欢迎进入计费管理系统\n\n");
    printf("----------菜单----------\n");
    printf("1.添加卡\n");
    printf("2.查询卡\n");
    printf("3.上机\n");
    printf("4.下机\n");
    printf("5.充值\n");
    printf("6.退费\n");
    printf("7.查询统计\n");
    printf("8.注销卡\n");
    printf("0.退出\n");

    int input;
    printf("请输入：\n");
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

        printf("\n请选择菜单项编号（0-8）：\n");
    }

}