#include <iostream>
#include <fstream>
#include <random>

void insertionSort(unsigned int *arr, unsigned int size, unsigned int *comp, unsigned int *ins) {
    for (unsigned int i = 1; i < size; i++)
    {
        unsigned int key = arr[i];
        unsigned int j = i;

        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
            (*comp)++;
            (*ins)++;
        }
        (*comp)++;
        if (arr[j] != key)
        {
            arr[j] = key;
            (*ins)++;
        }
        
    }
    

}

int main() 
{
    std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister
    unsigned long seed = std::random_device{}();
    mt.seed(seed); // we don't want to keep using the same seed every time

    std::ofstream results;
    results.open("2.txt", std::ofstream::out | std::ofstream::trunc);

    time_t start, end;
    time(&start);

    unsigned int increase = 100;
    unsigned int samples = 100;
    unsigned int repetitions = 50;

    unsigned int n = 0;
    
    for (unsigned int j = 0; j < samples; j++)
    {
        std::cout << j << std::endl;
        n += increase;

        for (unsigned int k = 0; k < repetitions; k++)
        {
            unsigned int comparations = 0;
            unsigned int insertions = 0;

            unsigned int array[n];

            for (unsigned int i = 0; i < n; i++)
            {
                array[i] = 0;
            }

            for (unsigned int i = 1; i < n + 1; i++)
            {
                unsigned int rnd = mt() % n;
                while (array[rnd] != 0)
                {
                    rnd++;
                    rnd %= n;
                }
                array[rnd] = i;
            }
            
            insertionSort(array, n, &comparations, &insertions);

            results << n << " " << k << " " << comparations << " " << insertions << "\n";
        }
        
    }
    
    time(&end);
    double duration = double(end - start);
    std::cout << "Time taken by program is : " << duration << " sec " << std::endl; 


    results.close();

    return 0;
}