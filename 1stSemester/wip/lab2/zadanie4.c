// Zadanie 4, zadanie4.c Michał Waluś

#include <stdio.h>

int daysTillDate(int day, int month, int year) {
    int przestepne, days = day - 1;
    przestepne = (year / 4) - (year / 100) + (year / 400);
    printf("%d\n", przestepne);
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
    printf("%d\n", days);
    return days;
}

int main(void) {
    daysTillDate(1, 3, 96);
}
