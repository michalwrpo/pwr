#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Checks whether a formula in 2SAT form is satisfiable
 * 
 * @param formula array of pairs (represented as 2-dimensional array) representing the formula.
 * Even numbers represent variables and odd their negations
 * @param length length of the `formula` array.
 * @param variable_count number of variables used in the formula, e.g. for formula `[[0, 2], [1, 3]]` it should be 2. 
 */
bool check2SAT(size_t formula[][2], size_t length, size_t variable_count) {
    size_t value_count = 2 * variable_count;
    bool (*implication)[value_count] = calloc(sizeof(int[value_count][value_count]), sizeof(int));

    for (size_t i = 0; i < value_count; i++) implication[i][i] = true;

    for (size_t i = 0; i < length; i++) {
        size_t first = formula[i][0];
        size_t second = formula[i][1];
        implication[first ^ 1][second] = true;
        implication[second ^ 1][first] = true;
    }
    
    size_t* stack = malloc(sizeof(int) * value_count);
    int top = -1;

    for (size_t i = 0; i < value_count; i++) {
        for (size_t j = 0; j < value_count; j++) {
            if (implication[i][j]) stack[++top] = j; 
        }

        while (top >= 0) {
            size_t element = stack[top--];

            for (size_t j = 0; j < value_count; j++) {
                if (implication[element][j] && !implication[i][j]) {
                    implication[i][j] = true;
                    stack[++top] = j;
                }
            }
        }
    }
    
    for (size_t i = 0; i < value_count; i += 2) {
        if (implication[i][i+1] && implication[i+1][i]) {
            return false;
        }
    }

    return true;
}

int main() {
    // Result = false
    // size_t formula[4][2] = {{0, 2}, {1, 3}, {0, 3}, {1, 2}};
    // bool result = check2SAT(formula, 4, 2);
    // Result = true
    size_t formula[3][2] = {{0, 2}, {1, 3}, {0, 3}};
    bool result = check2SAT(formula, 3, 2);

    printf("%d\n", result);
    return 0;
}