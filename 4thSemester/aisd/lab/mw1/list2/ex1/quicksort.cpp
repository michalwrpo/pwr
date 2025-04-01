#include <iostream>
#include <vector>

void swap(long* swaps, long* arr, long index1, long index2) {
    long temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
    (*swaps)++;
}

bool compare(long* comparisons, long value1, long value2) {
    (*comparisons)++;
    return (value1 < value2);
}

long partition(long* arr, long low, long high, long* swaps, long* comparisons, int depth, bool print) {
    long pivot = arr[high];

    long i = low;

    for (long j = low; j < high; j++) {
        if (compare(comparisons, arr[j], pivot)) {
            swap(swaps, arr, i, j);
            i++;
        }
    }

    swap(swaps, arr, i, high);

    if (print) {
        std::cout << depth << ". ";
        for (long i = 0; i < low; i++) {
            std::cout << "-- ";
        }
        for (long i = low; i < high + 1; i++) {
            long num = arr[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;
    }    

    return i;
}

void QuickSort(long* arr, long low, long high, long* swaps, long* comparisons, bool print, int depth) {
    if (low >= high || low < 0) 
        return;
    
    long p = partition(arr, low, high, swaps, comparisons, depth, print);

    QuickSort(arr, low, p - 1, swaps, comparisons, print, depth + 1);
    QuickSort(arr, p + 1, high, swaps, comparisons, print, depth + 1);
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

    if (len < 40) {
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

    bool print = (len < 40);
    if (print) 
        std::cout << "Array after partitions: " << std::endl;

    QuickSort(arr, 0, len - 1, &swaps, &comp, print, 1);

    std::cout << std::endl;

    if (len < 40) {
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

    if (len < 40) {
        std::cout << "Sorted array:" << std::endl;

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

    std::cout << "Comparisons: " << comp << "\nSwaps: " << swaps << std::endl;

    // check if the sort worked
    for (long i = 0; i < len; i++) {
        for (std::vector<long>::iterator it = start.begin(); it != start.end();) {
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