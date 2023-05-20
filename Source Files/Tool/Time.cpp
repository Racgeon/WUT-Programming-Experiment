#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "../../Header Files/global.h"


char *NowDate();

char *nowDate = NowDate();

//将时间转化为字符串
char *timeToDateStr(tm* t){
    char *date = (char *) malloc(sizeof(char) * 11);
    char year[5], mon[3], day[3];
    _itoa(t->tm_year + 1900, year, 10);
    _itoa(t->tm_mon + 1, mon, 10);
    _itoa(t->tm_mday, day, 10);
    sprintf(date,"%s-%s-%s",year,mon,day);
    return date;
}

//获取现在时间
char *NowDate() {
    tm *T;
    time_t t;
    t = time(NULL);
    T = localtime(&t);
    return timeToDateStr(T);
}


double calculateCost(long duration){
    double sec=duration/1000.0;
    double hour=sec/3600.0;
    return hour*COST_PER_HOUR;
}