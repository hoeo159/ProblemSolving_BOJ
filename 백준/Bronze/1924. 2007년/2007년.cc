#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    int x, y, i, day=0, week;
    scanf("%d %d", &x, &y);
    for(i=1; i<x; i++){
            if(i==1||i==3||i==5||i==7||i==8||i==10||i==12){
                day+=31;
            }
            else if(i==4||i==6||i==9||i==11){
                day+=30;
            }
            else day+=28;
    }
    day+=y;
    week=day%7;
    if(week==1) printf("MON");
    else if(week==2) printf("TUE");
    else if(week==3) printf("WED");
    else if(week==4) printf("THU");
    else if(week==5) printf("FRI");
    else if(week==6) printf("SAT");
    else printf("SUN");

}
