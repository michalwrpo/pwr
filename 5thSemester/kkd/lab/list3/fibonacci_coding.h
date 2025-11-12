#ifndef FIBONACCI_CODING_H
#define FIBONACCI_CODING_H

void fibonacci_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename);
void fibonacci_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength);

#endif