#include <stdio.h>

int main(void) {
    for (int r = 0; r < 256; r++)
    {
        for (int g = 0; g < 256; g++)
        {
            for (int b = 0; b < 256; b++)
            {
                printf("\x1b[38;2;%d;%d;%dmHello, World!\x1b[12D", r, g, b);
            }            
            printf("\n");
        }
    }
}