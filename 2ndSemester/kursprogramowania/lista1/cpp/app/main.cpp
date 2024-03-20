#include <iostream>

int main(const int argc, const char* const argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <arg1> <arg2> ..." << std::endl;
        return 1; 
    }
    
    return 0;
}