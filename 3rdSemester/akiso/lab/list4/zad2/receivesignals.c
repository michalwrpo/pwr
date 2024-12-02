#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void USRhandler(int sig) {
    printf("SIGUSR1 received\n");
}

void INThanlder(int sig) {
    printf("killed\n");
    exit(0);
}

int main() {
    signal(SIGUSR1, USRhandler);
    signal(SIGINT, INThanlder);


    while (1) {}

    return 0;
}