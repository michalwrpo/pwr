#include <iostream>
#include <fstream>
#include <random>

int main() 
{
    std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister
    unsigned long seed = std::random_device{}();
    mt.seed(seed); // we don't want to keep using the same seed every time

    std::ofstream resultsa;
    resultsa.open("3a.txt", std::ofstream::out | std::ofstream::trunc);

    std::ofstream resultsb;
    resultsb.open("3b.txt", std::ofstream::out | std::ofstream::trunc);

    time_t start, end;
    time(&start);

    unsigned int increase = 1000;
    unsigned int samples = 100;
    unsigned int repetitions = 50;

    unsigned int n = 0;
    
    for (unsigned int j = 0; j < samples; j++)
    {
        std::cout << j << std::endl;
        n += increase;

        for (unsigned int k = 0; k < repetitions; k++)
        {
            unsigned int t = 0;

            unsigned int left = n;

            while (left > 0)
            {
                for (int i = 0; i < left; i++)
                {
                    if (mt() % 2 == 1) // p = 0.5
                    {
                        left--;   
                    }   
                }
                t++;
            }    

            resultsa << n << " " << k << " " << t << "\n";

            t = 0;
            left = n;

            while (left > 0)
            {
                for (int i = 0; i < left; i++)
                {
                    if (mt() % 10 == 1) // p = 0.1
                    {
                        left--;   
                    }   
                }
                t++;
            }    

            resultsb << n << " " << k << " " << t << "\n";

        }
        
    }
    
    time(&end);
    double duration = double(end - start);
    std::cout << "Time taken by program is : " << duration << " sec " << std::endl; 

    resultsa.close();
    resultsb.close();

    return 0;
}