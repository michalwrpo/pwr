// Simple program allowing to make basic operations on integers in xv6 
// Michał Waluś 2024

#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[]) 
{   
    if (argc != 4)
    {
        printf(2, "Usage: expr int operator int\n");
        exit();
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[3]);
    char *operation = argv[2];
    int ans;

    if (strcmp(operation, "+") == 0) {
        ans = num1 + num2;
    } else if (strcmp(operation, "-") == 0) {
        ans = num1 - num2;
    } else if (strcmp(operation, "*") == 0) {
        ans = num1 * num2;
    } else if (strcmp(operation, "/") == 0) {
        if (num2 == 0) {
            printf(2, "Division by zero");
            exit();
        }
        ans = num1 / num2;
    } else if (strcmp(operation, "%") == 0) {
        ans = num1 % num2;
    } else {
        printf(2, "Operator has to be one of +, -, *, /, %%\n");
        exit();
    }

    printf(1, "%d\n", ans);
    exit();
}
