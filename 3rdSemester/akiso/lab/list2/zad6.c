#include <stdio.h>

int main(void) {
    for (int i = 0; i < 256; i++)
    {
        printf("\x1b[38;5;%dmHello, World!\n", i);
    }
}