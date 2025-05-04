#include <iostream>
#include <vector>
#include <chrono>

void insertionSort(long* arr, long start, long end) {
    long i = start + 1, j, x;
    while (i < end) {
        j = i;
        x = arr[j];
        while (j > start && arr[j-1] > x) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = x;
        i++;
    }
}

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

long Partition(long* arr, long low, long high, long pivotIndex, long* swaps, long* comparisons, int depth, bool print) {
    long pivot = arr[pivotIndex];
    swap(swaps, arr, pivotIndex, high);
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
        std::cout << "pivot=";
        if (pivot < 10) {
            std::cout << "0" << pivot << " | ";
        } else {
            std::cout << pivot << " | ";
        }

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

long Select(long* arr, long low, long high, long goal, long* swaps, long* comparisons) {
    if (low == high) {
        return low;
    }

    long len = high - low + 1;
    long fives = len/5;
    long rem = len - 5 * fives;

    for (long i = 0; i < len - rem; i += 5) {
        insertionSort(arr, low + i, low + i + 5);
    } 
    insertionSort(arr, high - rem + 1, high + 1);    
    
    // if len is divisible by 5 then rem = 0 and this is equal to fives, else rem != 0 and there is one more
    long parts = (len + 4) / 5; 
    
    for (long i = 0; i < fives; i++) {
        swap(swaps, arr, low + i, low + 5 * i + 2);
    }

    if (rem != 0) {
        swap(swaps, arr, low + fives, high - rem / 2);
    }    
    
    long M = Select(arr, low, low + parts - 1, (parts + 1) / 2, swaps, comparisons);

    long r = Partition(arr, low, high, M, swaps, comparisons, 100, false);
    long index = r - low + 1;

    if (goal == index) {        
        return r;
    } else if (goal < index) {
        return Select(arr, low, r - 1, goal, swaps, comparisons);
    } else {
        return Select(arr, r + 1, high, goal - index, swaps, comparisons);
    }
}

void QuickSort(long* arr, long low, long high, long* swaps, long* comparisons, bool print, int depth) {
    if (low >= high || low < 0) 
        return;
    
    long p = Select(arr, low, high, (high - low + 2) / 2, swaps, comparisons);
    p = Partition(arr, low, high, p, swaps, comparisons, depth, print);

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

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    QuickSort(arr, 0, len - 1, &swaps, &comp, print, 1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (print) {
        std::cout << std::endl;
    }
    

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

    std::cout << "Comparisons: " << comp << " Time: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << std::endl;

    // check if the sort worked
    if (print) {
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
    }
    
    
    return 0;
}