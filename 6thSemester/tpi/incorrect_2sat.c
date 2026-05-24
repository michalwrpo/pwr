#include <stdio.h>
#include <stdlib.h>

typedef struct list list;

struct list {
    size_t first;
    size_t second;
    list* next;
};

list* makeList(size_t arr[][2], size_t len) {
    list* start = NULL;
    list* prev = NULL;

    for (size_t i = 0; i < len; i++) {
        list* cur = malloc(sizeof(list));
        cur->first = (arr[i][0] < arr[i][1]) ? arr[i][0] : arr[i][1];
        cur->second = (arr[i][0] < arr[i][1]) ? arr[i][1] : arr[i][0];
        
        if (prev == NULL) start = cur;
        else prev->next = cur;
        
        prev = cur;
    }

    prev->next = NULL;
    
    return start;
}

void deleteList(list* l) {
    if (l == NULL) return;
    list* next;

    while(l != NULL) {
        next = l->next;
        free(l);
        l = next;
    }
}

void removeElement(list** cur, list* prev, list** start, size_t* occurrences, size_t* values) {
    size_t first = (*cur)->first;
    size_t second = (*cur)->second;
    occurrences[first]--;
    occurrences[second]--;
    if (first > 1 && occurrences[first] == 0) {
        values[first] = 0;
        values[first ^ 1] = 1; 
    } 

    if (second > 1 && occurrences[second] == 0) {
        values[second] = 0;
        values[second ^ 1] = 1;
    }

    if (prev == NULL) *start = (*cur)->next;
    else prev->next = (*cur)->next;

    list* temp = (*cur);
    (*cur) = (*cur)->next;
    free(temp);
}

/**
 * @brief Checks whether a formula in 2SAT form is satisfiable 
 * 
 * # WARNING! DOES NOT WORK CORRECTLY
 * 
 * @param formula array of pairs (represented as 2-dimensional array) representing the formula.
 * 0 represents false, 1 true, and higher numbers different variables. Even numbers represent variables and odd their negations
 * @param length length of the `formula` array.
 * @param variable_count number of variables used in the formula, e.g. for formula `[[2, 4], [3, 5]]` it should be 2. 
 */
bool check2SAT(size_t formula[][2], size_t length, size_t variable_count) {
    list* list_start = makeList(formula, length);
    size_t val_count = 2 * variable_count + 2; // normal, negated, and true/false
    size_t* occurrences = calloc(val_count, sizeof(size_t));
    size_t* values = malloc(sizeof(size_t) * val_count);

    for (size_t i = 0; i < val_count; i++) values[i] = i;

    {
        list* l = list_start;
        while (l != NULL) {
            occurrences[l->first]++;
            occurrences[l->second]++;
            l = l->next;
        }
    }

    bool changed = true;

    while(changed) {
        changed = false;
        list* prev = NULL;
        list* cur = list_start;

        while(cur != NULL) {
            cur->first = values[cur->first];
            cur->second = values[cur->second];

            if (cur->first == 0 && cur->second == 0)  {
                deleteList(list_start);
                return false;
            }

            if (cur->first == 1 || cur->second == 1) {
                removeElement(&cur, prev, &list_start, occurrences, values);
                changed = true;
            } else if (cur->first == 0 || cur->first == cur->second) {
                // always first <= second, but both cannot be false due to the first check
                values[cur->second] = 1; // has to be true
                values[cur->second ^ 1] = 0;
                removeElement(&cur, prev, &list_start, occurrences, values);
                changed = true;
            } else if (cur->first / 2 == cur->second / 2) {
                // can't be equal due to the case above
                removeElement(&cur, prev, &list_start, occurrences, values);
                changed = true;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }

        if (!changed) {
            size_t element = 0;
            for (size_t i = 2; i < val_count; i += 2) {
                if (occurrences[i] > 0 && occurrences[i + 1] > 0) {
                    element = i;
                    break;
                }
            }

            if (element == 0) break;

            cur = list_start;
            prev = NULL;

            size_t v1 = 0;
            size_t v2 = 0;

            while (cur != NULL) {
                bool remove = true;
                if (v1 == 0 && cur->first == element) v1 = cur->second;
                else if (v1 == 0 && cur->second == element) v1 = cur->first;
                else if (v2 == 0 && cur->first == element + 1) v2 = cur->second;
                else if (v2 == 0 && cur->second == element + 1) v2 = cur->first;
                else remove = false;

                if (remove) {
                    removeElement(&cur, prev, &list_start, occurrences, values);
                    if (v1 > 0 && v2 > 0) break;
                }
                else {
                    prev = cur;
                    cur = cur->next;
                }
            }

            list* new_element = malloc(sizeof(list));
            new_element->first = (v1 < v2) ? v1 : v2;
            new_element->second = (v1 < v2) ? v2 : v1;
            new_element->next = list_start;
            list_start = new_element;
            changed = true;
        }
    }

    return true;
}

int main() {
    size_t formula[4][2] = {{2, 4}, {3, 5}, {2, 5}, {3, 4}};
    bool result = check2SAT(formula, 4, 2);
    printf("%d\n", result);
    return 0;
}