#include <iostream>
#include <fstream>
#include <random>

int main() 
{
    std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister
    unsigned long seed = std::random_device{}();
    mt.seed(seed); // we don't want to keep using the same seed every time

    std::ofstream resultsa;
    resultsa.open("1a.txt", std::ofstream::out | std::ofstream::trunc);

    std::ofstream resultsb;
    resultsb.open("1b.txt", std::ofstream::out | std::ofstream::trunc);


    time_t start, end;
    time(&start);

    const unsigned int repetitions = 50; 
    const unsigned int increase = 10000;
    const unsigned int samplesCount = 100;

    unsigned int urns = 0;

    for (unsigned int i = 0; i < samplesCount; i++)
    {
        std::cout << i << std::endl;
        urns += increase;

        for (int k = 0; k < repetitions; k++) 
        {
            unsigned int maxBalls = 0;
            unsigned long ballsArray[urns];

            for (long j = 0; j < urns; j++)
            {
                ballsArray[j] = 0; // reset the array
            }

            for (unsigned int j = 0; j < urns; j++)
            {
                unsigned long urn = mt() % urns;
                ballsArray[urn]++; // throw a ball into a random urn
            }

            for (unsigned int j = 0; j < urns; j++)
            {
                if (ballsArray[j] > maxBalls) {
                    maxBalls = ballsArray[j]; // find maxiumum
                }
            }

            resultsa << urns << " " << k << " " << maxBalls << "\n";

            // b

            maxBalls = 0;

            for (long j = 0; j < urns; j++)
            {
                ballsArray[j] = 0; // reset the array
            }

            for (unsigned int j = 0; j < urns; j++)
            {
                unsigned long urn1 = mt() % urns;
                unsigned long urn2 = mt() % urns;
                // throw a ball into a random urn
                if (ballsArray[urn1] < ballsArray[urn2])
                {
                ballsArray[urn1]++; 
                } else 
                {
                    ballsArray[urn2]++;
                }
                
            }

            for (unsigned int j = 0; j < urns; j++)
            {
                if (ballsArray[j] > maxBalls) {
                    maxBalls = ballsArray[j]; // find maxiumum
                }
            }

            resultsb << urns << " " << k << " " << maxBalls << "\n";
        }    
    }

    time(&end);
    double duration = double(end - start);
    std::cout << "Time taken by program is : " << duration << " sec " << std::endl; 

    resultsa.close();
    resultsb.close();

    return 0;
}
