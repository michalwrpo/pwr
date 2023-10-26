// Zadanie 4, zadanie4.c Michał Waluś

#include <stdio.h>
#include <time.h>

int daysTillDate(int day, int month, int year) {
    int przestepne, days = day - 1;
    przestepne = (year / 4) - (year / 100) + (year / 400);
    switch (month) {
    case 2:
        days += 31;
        break;
    case 3:
        days += 31 + 28;
        break;
    case 4:
        days += 31 + 28 + 31;
        break;
    case 5:
        days += 31 + 28 + 31 + 30;
        break;
    case 6:
        days += 31 + 28 + 31 + 30 + 31;
        break;
    case 7:
        days += 31 + 28 + 31 + 30 + 31 + 30;
        break;
    case 8:
        days += 31 + 28 + 31 + 30 + 31 + 30 + 31;
        break;
    case 9:
        days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
        break;
    case 10:
        days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        break;
    case 11:
        days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
        break;
    case 12:
        days += 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
        break;
    }
    days += (year-1) * 365 + przestepne;
    if( ( (year % 4 == 0 && (year % 100 != 0)) || year % 400 == 0 ) && month < 3 ) {
        days -= 1;
    }
    return days;
}

int main(void) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int days;
    days = daysTillDate(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) - daysTillDate(05, 07, 2004);
    printf("Dni od 05.07.2004 do dnia dzisiejszego: %d\n", days);
    printf("Sekundy od 05.07.2004 do dnia dzisiejszego: %d\n", days*24*3600);
}
