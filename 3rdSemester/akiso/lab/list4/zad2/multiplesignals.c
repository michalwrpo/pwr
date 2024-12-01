#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No argument passed, 1 needed\n");
    } else if (argc > 2) {
        printf("Too many arguments, 1 needen\n");
    } else {
        int pid = atoi(argv[1]);

        for (int i = 0; i < 2; i++) {
            kill(pid, 10);
        }

        kill(pid, 2);
    }
    
    return 0;
}