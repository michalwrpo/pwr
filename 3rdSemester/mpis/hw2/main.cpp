#include <iostream>
#include <fstream>
#include <random>

int main() 
{
    std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister
    unsigned long seed = std::random_device{}();
    mt.seed(seed); // we don't want to keep using the same seed every time

    std::ofstream results;
    results.open("results.txt", std::ofstream::out | std::ofstream::trunc);

    time_t start, end;
    time(&start);

    const unsigned int repetitions = 50; 
    const unsigned int increaste = 1000;
    const unsigned int samplesCount = 100;

    unsigned long urns = 0;

    for (unsigned int i = 0; i < samplesCount; i++)
    {
        urns += increaste;

        for (int k = 0; k < repetitions; k++)
        {
            unsigned long empty = urns;
            unsigned long lessThanTwo = urns;
            unsigned long ballsArray[urns];

            for (long i = 0; i < urns; i++)
            {
                ballsArray[i] = 0;
            }

            unsigned long long counter = 0;

            unsigned long long firstRepeat = 0, nEmpty, allOne = 0, allTwo; 
            
            while (lessThanTwo > 0)
            {
                counter++;

                unsigned long urn = mt() % urns;
                switch (ballsArray[urn]++)
                {
                case 0:
                    empty--;
                    break;
                case 1:
                    if (firstRepeat == 0)
                    {
                        firstRepeat = counter;
                    }
                    
                    lessThanTwo--;
                    break;
                }

                if (counter == urns)
                {
                    nEmpty = empty;
                }
                
                if (allOne == 0 && empty == 0) {
                    allOne = counter;
                }
            }

            allTwo = counter;

            results << urns << " " << k << " " << firstRepeat << " " << nEmpty << " " << allOne << " " << allTwo << "\n";
        }    
    }

    time(&end);
    double duration = double(end - start);
    std::cout << "Time taken by program is : " << duration << " sec " << std::endl; 

    results.close();

    return 0;
}
