#include <iostream>
#include <vector>

#define ull unsigned long long

void swap(ull* swaps, ull* arr, ull index, ull value) {
    arr[index] = value;
    (*swaps)++;
}

bool compare(ull* comparisons, ull value1, ull value2) {
    (*comparisons)++;
    return (value1 > value2);
}

void QuickSort(ull* arr, ull len, ull* swaps, ull* comparisons) {
    bool print = (len < 40);
    if (print) {
        std::cout << "Array after insertions: " << std::endl;
    }

    ull i = 1, j, x;
    while (i < len) {
        j = i;
        x = arr[j];
        while (j > 0 && compare(comparisons, arr[j-1], x)) {
            swap(swaps, arr, j, arr[j-1]);
            j--;
        }
        swap(swaps, arr, j, x);
        i++;

        if (print) {
            for (ull i = 0; i < len; i++) {
                ull num = arr[i];
                if (num < 10) {
                    std::cout << "0" << num << " ";                
                } else {
                    std::cout << num << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

int main() {    
    ull len, input, i = 0, comp = 0, swaps = 0;
    std::cin >> len;
    ull arr[len];
    std::vector<ull> start;
    
    while (std::cin >> input) {
        if (i == len) {
            std::cerr << "More arguments were given than the given length" << std::endl;
            return -1;
        }
        
        arr[i] = input; 
        start.push_back(input);
        i++;
    }

    if (i < len) {
        std::cerr << "Less arguments were given than the given length" << std::endl;
        return -1;
    }

    if (len < 40) {
        std::cout << "Initial array:" << std::endl;

        for (ull i = 0; i < len; i++) {
            ull num = arr[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    QuickSort(arr, len, &comp, &swaps);

    if (len < 40) {
        std::cout << "Original array:" << std::endl;

        for (ull i = 0; i < len; i++) {
            ull num = start[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    if (len < 40) {
        std::cout << "Sorted array:" << std::endl;

        for (ull i = 0; i < len; i++) {
            ull num = arr[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Comparisons: " << comp << "\nSwaps: " << swaps << std::endl;

    // check if the sort worked
    for (ull i = 0; i < len; i++) {
        for (std::vector<ull>::iterator it = start.begin(); it != start.end();) {
            if (arr[i] == *it) {
                start.erase(it);
                break;
            } else {
                it++;
            }
        }

        if (i != 0) {
            if (arr[i] < arr[i-1]) {
                std::cerr << "Array not sorted properly; elements out of order." << std::endl;
                return -2;
            }
        }
    }
    
    if (start.size() != 0) {
        std::cerr << "Array not sorted properly; lost some elements." << std::endl;
        return -2;
    }
    
    return 0;
}