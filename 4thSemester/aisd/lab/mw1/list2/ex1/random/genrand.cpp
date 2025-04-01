#include <stdlib.h>
#include <iostream>
#include <random>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <len>" << std::endl;
        return -1;
    }
    
    long n = atoi(argv[1]);
    std::cout << n << " ";

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, 2 * n - 1);

    for (long i = 0; i < n; i++) {
        std::cout << dist(mt) << " ";
    }

    std::cout << std::endl;

    return 0;
}