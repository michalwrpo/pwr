#include "types.h"
#include "stat.h"
#include "user.h"

void rainbowHello()
{
    char escapesequence[3];
    escapesequence[0] = 0x1b;
    escapesequence[2] = '\0';
    char *helloWorld = "Hello, World!\n";

    for (int i = 0; i < 256; i++)
    {
        escapesequence[1] = i;

        write(1, escapesequence, 3);
        write(1, helloWorld, 14);
    }

    escapesequence[1] = 7;
    write(1, escapesequence, 3);
}

int main() 
{
    rainbowHello();
    exit();
}