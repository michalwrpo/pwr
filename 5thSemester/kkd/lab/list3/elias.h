#ifndef ELIAS_H
#define ELIAS_H

void gamma_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename);
void gamma_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength);

void delta_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename);
void delta_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength);

void omega_encode(unsigned int* sequence, unsigned int sequenceLength, char* outputFilename);
void omega_decode(char* inputFilename, unsigned int** sequence, unsigned int* sequenceLength);

#endif