#include <signal.h>
#include <stdio.h>

int main() {
    kill(1, 9);
    printf("kill sent\n");

    for (int i = 1; i < 65; i++)
    {
        if (i != 1 || i != 2 || i != 9 ) {
            if (kill(1, i) == 0) {
                printf("sent %d\n", i);
            }
        }
    }

    return 0;
}