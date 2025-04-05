#include <iostream>
#include <vector>

void swap(long* swaps, long* arr, long index, long value) {
    arr[index] = value;
    (*swaps)++;
}

bool compare(long* comparisons, long value1, long value2) {
    (*comparisons)++;
    return (value1 <= value2);
}

void ArrayCopy(long* arr1, long* arr2, long len) {
    for (long i = 0; i < len; i++) {
        arr2[i] = arr1[i];
    }
}

void Merge(long* arr1, long* arr2, long start, long middle, long end, long* swaps, long* comparisons) {
    long i = start, j = middle;

    for (long k = start; k < end; k++) {
        if (i < middle && (j >= end || compare(comparisons, arr1[i], arr1[j]))) {
            swap(swaps, arr2, k, arr1[i]);
            i++;
        } else {
            swap(swaps, arr2, k, arr1[j]);
            j++;
        }
    }
}

void Split(long* arr1, long* arr2, long start, long end, long* swaps, long* comparisons, bool print, int depth) {
    if (end - start < 2) {
        return;
    }
    
    long middle = (start + end) / 2;
    long i = middle + 1;
    while (i < end) {
        if (compare(comparisons, arr2[i - 1], arr2[i])) {
            i++;
        } else {
            break;
        }
    }

    if (i == end) {

        i = middle;

        while (i > start) {
            if (compare(comparisons, arr2[i-1], arr2[i])) {
                i--;
            } else {
                break;
            }
        }
        if (i == start) {
            return;
        } 
        
        Split(arr2, arr1, start, i, swaps, comparisons, print, depth + 1);
    } else {
        Split(arr2, arr1, start, i, swaps, comparisons, print, depth + 1);
        Split(arr2, arr1, i, end, swaps, comparisons, print, depth + 1);

    }
    
    Merge(arr1, arr2, start, i, end, swaps, comparisons);

    if (print) {
        std::cout << depth << ". ";
        for (long i = 0; i < start; i++) {
            std::cout << "-- ";
        }
        for (long i = start; i < end; i++) {
            long num = arr2[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }    

}

void MySort(long* arr, long* result, long len, long* swaps, long* comparisons, bool print, int depth) {
    ArrayCopy(arr, result, len);
    Split(arr, result, 0, len, swaps, comparisons, print, depth);
}

int main() {    
    long len, input, i = 0, comp = 0, swaps = 0;
    std::cin >> len;
    long arr[len];
    std::vector<long> start;
    
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

    bool print = (len < 40);

    if (print) {
        std::cout << "Initial array:" << std::endl;

        for (long i = 0; i < len; i++) {
            long num = arr[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    if (print) 
        std::cout << "Array after merges: " << std::endl;

    long result[len];

    MySort(arr, result, len, &swaps, &comp, print, 1);

    if (print) {
        std::cout << std::endl;
    }
    

    if (print) {
        std::cout << "Original array:" << std::endl;

        for (long i = 0; i < len; i++) {
            long num = start[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }


    if (print) {
        std::cout << "Sorted array:" << std::endl;

        for (long i = 0; i < len; i++) {
            long num = result[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Comparisons: " << comp << " Swaps: " << swaps << std::endl;

    // check if the sort worked
    if (print) {
        for (long i = 0; i < len; i++) {
            for (std::vector<long>::iterator it = start.begin(); it != start.end();) {
                if (result[i] == *it) {
                    start.erase(it);
                    break;
                } else {
                    it++;
                }
            }
    
            if (i != 0) {
                if (result[i] < result[i-1]) {
                    std::cerr << "Array not sorted properly; elements out of order." << std::endl;
                    return -2;
                }
            }
        }
        
        if (start.size() != 0) {
            std::cerr << "Array not sorted properly; lost some elements." << std::endl;
            return -2;
        }
    }
    
    
    return 0;
}