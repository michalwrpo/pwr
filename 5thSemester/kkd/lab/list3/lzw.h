#ifndef LZW_H
#define LZW_H

/* 
coding - which coding should be used to encode final list of integers from LZW:
0 - Elias' Omega coding 
1 - Elias' Delta coding 
2 - Elias' Gamma coding 
3 - Fibonacci coding 
*/
void lzw_encode(char* inputFilename, char* outputFilename, unsigned int coding);

/* 
coding - which coding does the encoded file use to encode list of integers from LZW:
0 - Elias' Omega coding 
1 - Elias' Delta coding 
2 - Elias' Gamma coding 
3 - Fibonacci coding 
*/
int lzw_decode(char* inputFilename, char* outputFilename, unsigned int coding);

#endif