#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <chrono>

bool compare(long* comparisons, long value1, long value2) {
    (*comparisons)++;
    return (value1 < value2);
}

bool compareEqual(long* comparisons, long value1, long value2) {
    (*comparisons)++;
    return (value1 == value2);
}

long binarySearch(long* arr, long low, long high, long value, long* comparisons) {
    if (high - low < 1) {
        if (compareEqual(comparisons, arr[low], value)) {
            return low;
        }
        return -1;
    }

    long mid = (low + high + 1) / 2;
    if (compare(comparisons, value, arr[mid])) {
        return binarySearch(arr, low, mid - 1, value, comparisons);
    } else {
        return binarySearch(arr, mid, high, value, comparisons);
    }
    
}

int main(int argc, char** argv) {    
    long len, value, input, i = 0, comp = 0, ans;

    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <searched value>" << std::endl;
        return -1;
    }    

    value = atoi(argv[1]);

    std::cin >> len;
    long arr[len];
    
    while (std::cin >> input) {        
        arr[i] = input; 
        i++;

        if (i == len) {
            break;
        }
    }

    if (i < len) {
        std::cerr << "Less arguments were given than the given length" << std::endl;
        return -1;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    ans = binarySearch(arr, 0, len - 1, value, &comp);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Comparisons: " << comp << " Time: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << " Answer: " << ans << std::endl;
    
    return 0;
}