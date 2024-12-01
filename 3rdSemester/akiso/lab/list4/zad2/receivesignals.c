#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

FILE *fptr;

void USRhandler(int sig) {
    fprintf(fptr, "SIGUSR1 received\n");
}

void INThanlder(int sig) {
    fprintf(fptr, "kill\n");
    fclose(fptr);
    exit(0);
}

int main() {
    fptr = fopen("output.txt", "w");

    signal(SIGUSR1, USRhandler);
    signal(SIGINT, INThanlder);


    while (1) {}

    return 0;
}