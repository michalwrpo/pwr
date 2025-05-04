#include <stdlib.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <len> <spacing>" << std::endl;
        return -1;
    }
    
    long n = atoi(argv[1]);
    long spacing = atoi(argv[2]);
    std::cout << n << " ";


    for (long i = 0; i < n; i++) {
        std::cout << spacing * i << " ";
    }

    std::cout << std::endl;

    return 0;
}