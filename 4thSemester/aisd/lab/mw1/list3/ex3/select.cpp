#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>

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

long Select(long* arr, long low, long high, long goal, int size, long* swaps, long* comparisons, bool print, int depth) {
    if (low == high) {
        return low;
    }

    long len = high - low + 1;
    long groups = len/size;
    long rem = len - size * groups;

    for (long i = 0; i < len - rem; i += size) {
        insertionSort(arr, low + i, low + i + size);
    } 
    insertionSort(arr, high - rem + 1, high + 1);    
    
    // if len is divisible by size then rem = 0 and this is equal to groups, else rem != 0 and there is one more
    long parts = (len + size - 1) / size; 
    
    for (long i = 0; i < groups; i++) {
        swap(swaps, arr, low + i, low + size * i + 2);
    }

    if (rem != 0) {
        swap(swaps, arr, low + groups, high - rem / 2);
    }    
    
    long M = Select(arr, low, low + parts - 1, (parts + 1) / 2, size, swaps, comparisons, false, 100 + depth);

    long r = Partition(arr, low, high, M, swaps, comparisons, depth, print);
    long index = r - low + 1;

    if (goal == index) {        
        return r;
    } else if (goal < index) {
        return Select(arr, low, r - 1, goal, size, swaps, comparisons, print, depth + 1);
    } else {
        return Select(arr, r + 1, high, goal - index, size, swaps, comparisons, print, depth + 1);
    }
}

int main(int argc, char** argv) {    
    long len, goal, input, i = 0, comp = 0, swaps = 0, ans;
    int size;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "<group size> <order statistic>" << std::endl;
        return -1;
    }    

    size = atoi(argv[1]);
    goal = atoi(argv[2]);

    std::cin >> len;
    
    long arr[len];
    std::vector<long> start;
    
    while (std::cin >> input) {        
        arr[i] = input; 
        start.push_back(input);
        i++;

        if (i == len) {
            break;
        }
    }

    if (size < 1) {
        std::cerr << "Group size should be a positive integer" << std::endl;
        return -1;
    }
    

    if (goal < 0) {
        std::cerr << "Order statistic should be a positive integer" << std::endl;
        return -1;
    }

    if (goal > len) {
        std::cerr << "Order statistic requested higher than the length of the array" << std::endl;
        return -1;
    }

    if (i < len) {
        std::cerr << "Less arguments were given than the given length" << std::endl;
        return -1;
    }

    bool print = (len < 30);

    if (print) {        
        std::cout << "Looking for " << goal;
    
        if (goal % 10 == 1 && goal % 100 != 11) {
            std::cout << "st";
        } else if (goal % 10 == 2 && goal % 100 != 12) {
            std::cout << "nd";
        } else if (goal % 10 == 3 && goal % 100 != 13) {
            std::cout << "rd";
        } else {
            std::cout << "th";
        }
        std::cout << " order statistic" << std::endl;
    
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
        std::cout << "Array after partitions: " << std::endl;

    ans = Select(arr, 0, len - 1, goal, size, &swaps, &comp, print, 1);

    if (print) {
        std::cout << std::endl;

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

        std::cout << "Array at the end:" << std::endl;

        for (long i = 0; i < len; i++) {
            long num = arr[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;

        std::sort(start.begin(), start.end());

        std::cout << "Sorted array:" << std::endl;

        for (long i = 0; i < len; i++) {
            long num = start[i];
            if (num < 10) {
                std::cout << "0" << num << " ";                
            } else {
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;

        std::cout << "Answer: " << arr[ans] << std::endl;
    }


    std::cout << "Comparisons: " << comp << " Swaps: " << swaps << std::endl;
    
    return 0;
}